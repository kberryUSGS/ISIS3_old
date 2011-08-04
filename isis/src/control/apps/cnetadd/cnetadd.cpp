#include "Isis.h"

#include <map>
#include <set>

#include "geos/geom/Coordinate.h"
#include "geos/geom/Envelope.h"
#include "geos/geom/Geometry.h"
#include "geos/geom/MultiPolygon.h"
#include "geos/geom/Point.h"

#include "Camera.h"
#include "CameraFactory.h"
#include "ControlNet.h"
#include "ControlNetValidMeasure.h"
#include "ControlMeasure.h"
#include "ControlPoint.h"
#include "CubeManager.h"
#include "FileList.h"
#include "Filename.h"
#include "iException.h"
#include "iTime.h"
#include "Latitude.h"
#include "Longitude.h"
#include "Pvl.h"
#include "SerialNumber.h"
#include "SerialNumberList.h"
#include "SurfacePoint.h"
#include "UserInterface.h"
#include "ImagePolygon.h"

using geos::geom::Coordinate;
using geos::geom::Envelope;
using geos::geom::Geometry;
using geos::geom::MultiPolygon;
using geos::geom::Point;

using namespace Isis;

void SetControlPointLatLon(SerialNumberList &snl, ControlNet &cnet);

std::map< std::string, SurfacePoint > p_surfacePoints;
std::map< int, std::set<std::string> > p_modifiedMeasures;


void IsisMain() {

  UserInterface &ui = Application::GetUserInterface();

  FileList addList(ui.GetFilename("ADDLIST"));

  bool log = false;
  Filename logFile;
  if (ui.WasEntered("LOG")) {
    log = true;
    logFile = ui.GetFilename("LOG");
  }
  Pvl results;
  results.SetName("cnetadd_Results");
  PvlKeyword added("FilesAdded");
  PvlKeyword omitted("FilesOmitted");
  PvlKeyword pointsModified("PointsModified");

  bool checkMeasureValidity = ui.WasEntered("DEFFILE");
  ControlNetValidMeasure validator;
  if (checkMeasureValidity) {
    Pvl deffile(ui.GetFilename("DEFFILE"));
    validator = ControlNetValidMeasure(deffile);
  }

  SerialNumberList *fromSerials = ui.WasEntered("FROMLIST") ?
    new SerialNumberList(ui.GetFilename("FROMLIST")) : new SerialNumberList();

  ControlNet inNet = ControlNet(ui.GetFilename("CNET"));
  inNet.SetUserName(Application::UserName());
  inNet.SetModifiedDate(iTime::CurrentLocalTime()); //This should be done in ControlNet's Write fn

  std::string retrievalOpt = ui.GetString("RETRIEVAL");
  PvlKeyword duplicates("DupSerialNumbers");
  if (retrievalOpt == "REFERENCE") {
    FileList list1(ui.GetFilename("FROMLIST"));
    SerialNumberList addSerials(ui.GetFilename("ADDLIST"));

    //Check for duplicate files in the lists by serial number
    for (int i = 0; i < addSerials.Size(); i++) {

      // Check for duplicate SNs accross the lists
      if (fromSerials->HasSerialNumber(addSerials.SerialNumber(i))) {
        duplicates.AddValue(addSerials.Filename(i));
      }

      // Check for duplicate SNs within the addlist
      for (int j = i + 1; j < addSerials.Size(); j++) {
        if (addSerials.SerialNumber(i) == addSerials.SerialNumber(j)) {
          std::string msg = "Add list files [" + addSerials.Filename(i) + "] and [";
          msg += addSerials.Filename(j) + "] share the same serial number.";
          throw iException::Message(iException::User, msg, _FILEINFO_);
        }
      }
    }

    // Get the lat/long coords from the existing reference measure
    SetControlPointLatLon(*fromSerials, inNet);
  }
  else {
    for (int cp = 0; cp < inNet.GetNumPoints(); cp++) {
      // Get the surface point from the current control point
      ControlPoint *point = inNet.GetPoint(cp);
      SurfacePoint surfacePoint = point->GetBestSurfacePoint();

      if (!surfacePoint.Valid()) {
        std::string msg = "Unable to retreive lat/lon from Control Point [";
        msg += point->GetId() + "]. RETREIVAL=POINT cannot be used unless ";
        msg += "all Control Points have Latitude/Longitude keywords.";
        throw iException::Message(iException::User, msg, _FILEINFO_);
      }

      p_surfacePoints[point->GetId()] = surfacePoint;
    }
  }

  Filename outNetFile(ui.GetFilename("ONET"));

  Progress progress;
  progress.SetText("Adding Images");
  progress.SetMaximumSteps(addList.size());
  progress.CheckStatus();

  // loop through all the images
  bool usePolygon = ui.GetBoolean("POLYGON");
  std::vector<int> modPoints;

  QList<Coordinate> geomPoints;
  if (usePolygon) {
    for (int cp = 0; cp < inNet.GetNumPoints(); cp++) {
      ControlPoint *point = inNet.GetPoint(cp);
      SurfacePoint surfacePoint = p_surfacePoints[point->GetId()];

      Longitude lon = surfacePoint.GetLongitude();
      Latitude lat = surfacePoint.GetLatitude();

      Coordinate coord(lon.GetDegrees(), lat.GetDegrees());
      geomPoints.append(coord);
    }
  }

  for (unsigned int img = 0; img < addList.size(); img++) {
    bool imageAdded = false;
    Cube cube;
    cube.open(addList[img]);
    Pvl *cubepvl = cube.getLabel();
    std::string sn = SerialNumber::Compose(*cubepvl);
    Camera *cam = cube.getCamera();

    ImagePolygon poly;
    if (usePolygon) {
      try {
        cube.read(poly);
      }
      catch (iException &e) {
        std::string msg = "Footprintinit must be run prior to running cnetadd";
        msg += " with POLYGON=TRUE for cube [" + cube.getFilename() + "]";
        throw iException::Message(iException::User, msg, _FILEINFO_);
      }
    }

    // Loop through all the control points
    for (int cp = 0; cp < inNet.GetNumPoints(); cp++) {
      ControlPoint *point = inNet.GetPoint(cp);

      // If the point is locked and Apriori source is "AverageOfMeasures"
      // then do not add the measures.
      if (point->IsEditLocked() &&
          point->GetAprioriSurfacePointSource() == ControlPoint::SurfacePointSource::AverageOfMeasures) {
        continue;
      }

      if (point->HasSerialNumber(sn)) continue;

      bool containsPoint = false;
      if (usePolygon) {
        MultiPolygon *polys = poly.Polys();
        for (unsigned int i = 0; i < polys->getNumGeometries() && !containsPoint; i++) {
          const Geometry *geometry = polys->getGeometryN(i);
          const Envelope *boundingBox = geometry->getEnvelopeInternal();
          containsPoint = boundingBox->contains(geomPoints[cp]);
        }

        if (!containsPoint) continue;
      }

      SurfacePoint surfacePoint = p_surfacePoints[point->GetId()];;
      if (cam->SetGround(surfacePoint)) {

        // Make sure the samp & line are inside the image
        if (cam->InCube()) {
          ControlMeasure *newCm = new ControlMeasure();
          newCm->SetCoordinate(cam->Sample(), cam->Line(), ControlMeasure::Candidate);
          newCm->SetAprioriSample(cam->Sample());
          newCm->SetAprioriLine(cam->Line());
          newCm->SetCubeSerialNumber(sn);
          newCm->SetDateTime();
          newCm->SetChooserName("Application cnetadd");

          // Check the measure for DEFFILE validity
          if (checkMeasureValidity) {
            if (!validator.ValidEmissionAngle(cam->EmissionAngle())) {
              //TODO: log that it was Emission Angle that failed the check
              newCm->SetIgnored(true);
            }
            else if (!validator.ValidIncidenceAngle(cam->IncidenceAngle())) {
              //TODO: log that it was Incidence Angle that failed the check
              newCm->SetIgnored(true);
            }
            else if (!validator.ValidResolution(cam->Resolution())) {
              //TODO: log that it was Resolution that failed the check
              newCm->SetIgnored(true);
            }
            else if (!validator.PixelsFromEdge((int)cam->Sample(), (int)cam->Line(), &cube)) {
              //TODO: log that it was Pixels from Edge that failed the check
              newCm->SetIgnored(true);
            }
            else {
              Portal portal(1, 1, cube.getPixelType());
              portal.SetPosition(cam->Sample(), cam->Line(), 1);
              cube.read(portal);
              if (!validator.ValidDnValue(portal[0])) {
                //TODO: log that it was DN that failed the check
                newCm->SetIgnored(true);
              }
            }
          }

          point->Add(newCm); // Point takes ownership

          // Record the modified Point and Measure
          p_modifiedMeasures[cp].insert(newCm->GetCubeSerialNumber());
          newCm = NULL; // Do not delete because the point has ownership

          if (retrievalOpt == "POINT" && inNet.GetPoint(cp)->GetNumMeasures() == 1) {
            point->SetIgnored(false);
          }

          if (log) {
            // If we can't find this control point in the list of control points
            // that have already been modified, then add it to the list
            bool doesntContainPoint = true;
            for (unsigned int i = 0; i < modPoints.size() && doesntContainPoint; i++) {
              if (modPoints[i] == cp) doesntContainPoint = false;
            }
            if (doesntContainPoint) {
              modPoints.push_back(cp);
            }

            imageAdded = true;
          }
        }
      }
    }

    cubepvl = NULL;
    cam = NULL;

    if (log) {
      if (imageAdded) added.AddValue(Filename(addList[img]).Basename());
      else omitted.AddValue(Filename(addList[img]).Basename());
    }

    progress.CheckStatus();
  }

  if (log) {

    // Shell sort the list of modified control points
    int increments[] = { 1391376, 463792, 198768, 86961, 33936, 13776, 4592, 1968,
                         861, 336, 112, 48, 21, 7, 3, 1
                       };
    for (unsigned int k = 0; k < 16; k++) {
      int inc = increments[k];
      for (unsigned int i = inc; i < modPoints.size(); i++) {
        int temp = modPoints[i];
        int j = i;
        while (j >= inc && modPoints[j - inc] > temp) {
          modPoints[j] = modPoints[j - inc];
          j -= inc;
        }
        modPoints[j] = temp;
      }
    }

    // Add the list of modified points to the output log file
    for (unsigned int i = 0; i < modPoints.size(); i++) {
      pointsModified += inNet.GetPoint(modPoints[i])->GetId();
    }

    results.AddKeyword(added);
    results.AddKeyword(omitted);
    results.AddKeyword(pointsModified);
    if (duplicates.Size() > 0) {
      results.AddKeyword(duplicates);
    }

    results.Write(logFile.Expanded());
  }

  // List the modified points
  if (ui.WasEntered("MODIFIEDPOINTS")) {
    Filename pointList(ui.GetFilename("MODIFIEDPOINTS"));

    // Set up the output file for writing
    std::ofstream out_stream;
    out_stream.open(pointList.Expanded().c_str(), std::ios::out);
    out_stream.seekp(0, std::ios::beg);   //Start writing from beginning of file

    for (std::map< int, std::set<std::string> >::iterator it = p_modifiedMeasures.begin();
        it != p_modifiedMeasures.end(); it ++) {
      out_stream << inNet.GetPoint(it->first)->GetId() << std::endl;
    }

    out_stream.close();
  }

  // Modify the inNet to only have modified points/measures
  if (ui.GetString("EXTRACT") == "MODIFIED") {
    for (int cp = inNet.GetNumPoints() - 1; cp >= 0; cp --) {
      std::map< int, std::set<std::string> >::iterator it = p_modifiedMeasures.find(cp);
      // If the point was not modified, delete
      if (it == p_modifiedMeasures.end()) {
        inNet.DeletePoint(cp);
      }
      // Else, remove the unwanted measures from the modified point
      else {
        ControlPoint *controlpt = inNet.GetPoint(cp);

        for (int cm = controlpt->GetNumMeasures() - 1; cm >= 0; cm --) {
          ControlMeasure *controlms = controlpt->GetMeasure(cm);

          if (controlpt->GetRefMeasure() != controlms &&
              it->second.find(controlms->GetCubeSerialNumber()) == it->second.end()) {
            controlpt->Delete(cm);
          }
        }
      }
    }
  }

  // Generate the TOLIST if wanted
  if (ui.WasEntered("TOLIST")) {
    SerialNumberList toList;

    SerialNumberList addSerials(ui.GetFilename("ADDLIST"));

    const QList<QString> snList = inNet.GetCubeSerials();
    for (int i = 0; i < snList.size(); i++) {
      iString sn = snList[i];

      if (addSerials.HasSerialNumber(sn))
        toList.Add(addSerials.Filename(sn));
      else if (fromSerials->HasSerialNumber(sn))
        toList.Add(fromSerials->Filename(sn));
    }

    iString name(ui.GetFilename("TOLIST"));
    std::fstream out_stream;
    out_stream.open(name.c_str(), std::ios::out);
    out_stream.seekp(0, std::ios::beg); //Start writing from beginning of file

    for (int f = 0; f < (int)toList.Size(); f++)
      out_stream << toList.Filename(f) << std::endl;

    out_stream.close();
  }

  inNet.Write(outNetFile.Expanded());

  delete fromSerials;
}


/**
 * Calculates the lat/lon of the ControlNet.
 *
 * @param incubes The filename of the list of cubes in the ControlNet
 * @param cnet    The filename of the ControlNet
 */
void SetControlPointLatLon(SerialNumberList &snl, ControlNet &cnet) {
  CubeManager manager;
  manager.SetNumOpenCubes(50);   //Should keep memory usage to around 1GB

  Progress progress;
  progress.SetText("Calculating Lat/Lon");
  progress.SetMaximumSteps(cnet.GetNumPoints());
  progress.CheckStatus();

  for (int cp = 0; cp < cnet.GetNumPoints(); cp++) {
    ControlPoint *point = cnet.GetPoint(cp);
    ControlMeasure *cm = point->GetRefMeasure();

    Cube *cube = manager.OpenCube(snl.Filename(cm->GetCubeSerialNumber()));
    try {
      cube->getCamera()->SetImage(cm->GetSample(), cm->GetLine());
      p_surfacePoints[point->GetId()] = cube->getCamera()->GetSurfacePoint();
    }
    catch (iException &e) {
      std::string msg = "Unable to create camera for cube file [";
      msg += snl.Filename(cm->GetCubeSerialNumber()) + "]";
      throw iException::Message(iException::System, msg, _FILEINFO_);
    }
    cube = NULL; //Do not delete, manager still has ownership

    progress.CheckStatus();
  }

  manager.CleanCubes();
}

