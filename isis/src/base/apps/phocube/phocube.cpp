#include "Isis.h"

#include "Angle.h"
#include "Camera.h"
#include "ProcessByBrick.h"
#include "ProcessByLine.h"
#include "SpecialPixel.h"
#include "iException.h"


using namespace std;
using namespace Isis;

// Global variables
Camera *cam;
int nbands;

bool phase; 
bool emission;
bool incidence;
bool localEmission;
bool localIncidence;
bool latitude;
bool longitude;
bool pixelResolution;
bool lineResolution;
bool sampleResolution;
bool detectorResolution;
bool northAzimuth;
bool sunAzimuth;
bool spacecraftAzimuth;
bool offnadirAngle;
bool subSpacecraftGroundAzimuth;
bool subSolarGroundAzimuth;

void phocube(Buffer &out);

void IsisMain() {
  // Get the camera information
  Process p1;
  Cube *icube = p1.SetInputCube("FROM", OneBand);
  cam = icube->getCamera();

  // We will be processing by brick.
  ProcessByBrick p;

  // Find out which bands are to be created
  UserInterface &ui = Application::GetUserInterface();

  nbands = 0;
  if((phase = ui.GetBoolean("PHASE"))) nbands++;
  if((emission = ui.GetBoolean("EMISSION"))) nbands++;
  if((incidence = ui.GetBoolean("INCIDENCE"))) nbands++;
  if((localEmission = ui.GetBoolean("LOCALEMISSION"))) nbands++;
  if((localIncidence = ui.GetBoolean("LOCALINCIDENCE"))) nbands++;
  if((latitude = ui.GetBoolean("LATITUDE"))) nbands++;
  if((longitude = ui.GetBoolean("LONGITUDE"))) nbands++;
  if((pixelResolution = ui.GetBoolean("PIXELRESOLUTION"))) nbands++;
  if((lineResolution = ui.GetBoolean("LINERESOLUTION"))) nbands++;
  if((sampleResolution = ui.GetBoolean("SAMPLERESOLUTION"))) nbands++;
  if((detectorResolution = ui.GetBoolean("DETECTORRESOLUTION"))) nbands++;
  if((northAzimuth = ui.GetBoolean("NORTHAZIMUTH"))) nbands++;
  if((sunAzimuth = ui.GetBoolean("SUNAZIMUTH"))) nbands++;
  if((spacecraftAzimuth = ui.GetBoolean("SPACECRAFTAZIMUTH"))) nbands++;
  if((offnadirAngle = ui.GetBoolean("OFFNADIRANGLE"))) nbands++;
  if((subSpacecraftGroundAzimuth = ui.GetBoolean("SUBSPACECRAFTGROUNDAZIMUTH"))) nbands++;
  if((subSolarGroundAzimuth = ui.GetBoolean("SUBSOLARGROUNDAZIMUTH"))) nbands++;

  if(nbands < 1) {
    string message = "At least one photometry parameter must be entered"
                     "[PHASE, EMISSION, INCIDENCE, LATITUDE, LONGITUDE]";
    throw iException::Message(iException::User, message, _FILEINFO_);
  }

  // Create a bandbin group for the output label
  PvlKeyword name("Name");
  if(phase) name += "Phase Angle";
  if(emission) name += "Emission Angle";
  if(incidence) name += "Incidence Angle";
  if(localEmission) name += "Local Emission Angle";
  if(localIncidence) name += "Local Incidence Angle";
  if(latitude) name += "Latitude";
  if(longitude) name += "Longitude";
  if(pixelResolution) name += "Pixel Resolution";
  if(lineResolution) name += "Line Resolution";
  if(sampleResolution) name += "Sample Resolution";
  if(detectorResolution) name += "Detector Resolution";
  if(northAzimuth) name += "North Azimuth";
  if(sunAzimuth) name += "Sun Azimuth";
  if(spacecraftAzimuth) name += "Spacecraft Azimuth";
  if(offnadirAngle) name += "OffNadir Angle";
  if(subSpacecraftGroundAzimuth) name += "Sub Spacecraft Ground Azimuth";
  if(subSolarGroundAzimuth) name += "Sub Solar Ground Azimuth";
  PvlGroup bandBin("BandBin");
  bandBin += name;

  // Create the output cube.  Note we add the input cube to expedite propagation
  // of input cube elements (label, blobs, etc...).  It *must* be cleared
  // prior to systematic processing.
  (void) p.SetInputCube("FROM", OneBand);
  Cube *ocube = p.SetOutputCube("TO", icube->getSampleCount(), icube->getLineCount(), nbands);
  p.SetBrickSize(64, 64, nbands);
  p.ClearInputCubes();     // Toss the input file as stated above

  // Start the processing
  p.StartProcess(phocube);

  // Add the bandbin group to the output label.  If a BandBin group already
  // exists, remove all existing keywords and add the keywords for this app.
  // Otherwise, just put the group in.
  PvlObject &cobj = ocube->getLabel()->FindObject("IsisCube");
  if(cobj.HasGroup("BandBin")) {
    PvlGroup &bb = cobj.FindGroup("BandBin");
    bb.Clear();
    PvlContainer::PvlKeywordIterator k = bandBin.Begin();
    while(k != bandBin.End()) {
      bb += *k;
      ++k;
    }
  }
  else {
    ocube->putGroup(bandBin);
  }

  p.EndProcess();
}


void phocube(Buffer &out) {

  for(int i = 0; i < 64; i++) {
    for(int j = 0; j < 64; j++) {
      int index = i * 64 + j;
      double samp = out.Sample(index);
      double line = out.Line(index);
      cam->SetImage(samp, line);

      if(cam->HasSurfaceIntersection()) {
        if(phase) {
          out[index] = cam->PhaseAngle();
          index += 64 * 64;
        }
        if(emission) {
          out[index] = cam->EmissionAngle();
          index += 64 * 64;
        }
        if(incidence) {
          out[index] = cam->IncidenceAngle();
          index += 64 * 64;
        }
        if(localEmission || localIncidence) {
          Angle phase;
          Angle incidence;
          Angle emission;
          bool success;
          cam->LocalPhotometricAngles(phase, incidence, emission, success);

          if (localEmission) {
            out[index] = emission.GetDegrees();
            index += 64 * 64;
          }

          if (localIncidence) {
            out[index] = incidence.GetDegrees();
            index += 64 * 64;
          }
        }
        if(latitude) {
          out[index] = cam->UniversalLatitude();
          index += 64 * 64;
        }
        if(longitude) {
          out[index] = cam->UniversalLongitude();
          index += 64 * 64;
        }
        if(pixelResolution) {
          out[index] = cam->PixelResolution();
          index += 64 * 64;
        }
        if(lineResolution) {
          out[index] = cam->LineResolution();
          index += 64 * 64;
        }
        if(sampleResolution) {
          out[index] = cam->SampleResolution();
          index += 64 * 64;
        }
        if(detectorResolution) {
          out[index] = cam->SampleResolution();
          index += 64 * 64;
        }
        if(northAzimuth) {
          out[index] = cam->NorthAzimuth();
          index += 64 * 64;
        }
        if(sunAzimuth) {
          out[index] = cam->SunAzimuth();
          index += 64 * 64;
        }
        if(spacecraftAzimuth) {
          out[index] = cam->SpacecraftAzimuth();
          index += 64 * 64;
        }
        if(offnadirAngle) {
          out[index] = cam->OffNadirAngle();
          index += 64 * 64;
        }
        if(subSpacecraftGroundAzimuth) {
          double ssplat, ssplon;
          ssplat = ssplon = 0.0;
          cam->SubSpacecraftPoint(ssplat, ssplon);
          out[index] = cam->GroundAzimuth(cam->UniversalLatitude(),
              cam->UniversalLongitude(), ssplat, ssplon);
          index += 64 * 64;
        }
        if(subSolarGroundAzimuth) {
          double sslat, sslon;
          sslat = sslon = 0.0;
          cam->SubSolarPoint(sslat,sslon);
          out[index] = cam->GroundAzimuth(cam->UniversalLatitude(),
              cam->UniversalLongitude(), sslat, sslon);
          index += 64 * 64;
        }
      }
      // Trim outerspace
      else {
        for(int b = 0; b < nbands; b++) {
          out[index] = Isis::NULL8;
          index += 64 * 64;
        }
      }
    }
  }
}
