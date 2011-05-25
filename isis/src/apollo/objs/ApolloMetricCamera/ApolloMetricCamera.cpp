/**
 * @file
 *
 *   Unless noted otherwise, the portions of Isis written by the USGS are public
 *   domain. See individual third-party library and package descriptions for 
 *   intellectual property information,user agreements, and related information.
 *
 *   Although Isis has been used by the USGS, no warranty, expressed or implied,
 *   is made by the USGS as to the accuracy and functioning of such software 
 *   and related material nor shall the fact of distribution constitute any such 
 *   warranty, and no responsibility is assumed by the USGS in connection 
 *   therewith.
 *
 *   For additional information, launch
 *   $ISISROOT/doc//documents/Disclaimers/Disclaimers.html in a browser or see 
 *   the Privacy &amp; Disclaimers page on the Isis website,
 *   http://isis.astrogeology.usgs.gov, and the USGS privacy and disclaimers on
 *   http://www.usgs.gov/privacy.html.
 */
#include "ApolloMetricCamera.h"

#include "ApolloMetricDistortionMap.h"

#include "CameraDetectorMap.h"
#include "CameraFocalPlaneMap.h"
#include "CameraGroundMap.h"
#include "CameraSkyMap.h"
#include "Filename.h"
#include "iException.h"
#include "iString.h"
#include "iTime.h"
#include "NaifStatus.h"
#include "ReseauDistortionMap.h"

using namespace std;
namespace Isis {
  /**
   * Constructs an Apollo Metric Camera object using the image labels.
   *
   * @param lab Pvl label from an Apollo Metric image.
   *
   * @internal 
   *   @history 2011-01-14 Travis Addair - Added new CK/SPK accessor methods.
   *   @history 2011-05-03 Jeannie Walldren - Added documentation.
   */
  ApolloMetricCamera::ApolloMetricCamera(Pvl &lab) : FramingCamera(lab) {
    NaifStatus::CheckErrors();

    // Get the camera characteristics
    SetFocalLength();
    SetPixelPitch();

    // Setup detector map
    new CameraDetectorMap(this);

    // Setup focal plane map
    CameraFocalPlaneMap *focalMap = new CameraFocalPlaneMap(this, NaifIkCode());
    focalMap->SetDetectorOrigin(ParentSamples() / 2.0, ParentLines() / 2.0);

    iString ppKey("INS" + iString((int)NaifIkCode()) + "_PP");
    iString odkKey("INS" + iString((int)NaifIkCode()) + "_OD_K");
    iString decenterKey("INS" + iString((int)NaifIkCode()) + "_DECENTER");

    new ApolloMetricDistortionMap(this, GetDouble(ppKey, 0),
                                  GetDouble(ppKey, 1), GetDouble(odkKey, 0), GetDouble(odkKey, 1),
                                  GetDouble(odkKey, 2), GetDouble(decenterKey, 0),
                                  GetDouble(decenterKey, 1), GetDouble(decenterKey, 2));

    // Setup the ground and sky map
    new CameraGroundMap(this);
    new CameraSkyMap(this);

    const PvlGroup &inst = lab.FindGroup("Instrument", Pvl::Traverse);

    // The Spacecraft Name should be either Apollo 15, 16, or 17.  The name
    // itself could be formatted any number of ways, but the number contained
    // in the name should be unique between the missions
    string spacecraft = inst.FindKeyword("SpacecraftName")[0];
    if (spacecraft.find("15") != string::npos) {
      p_ckFrameId = -915240;
      p_ckReferenceId = 1400015;
      p_spkTargetId = -915;
    }
    else if (spacecraft.find("16") != string::npos) {
      p_ckFrameId = -916240;
      p_ckReferenceId = 1400016;
      p_spkTargetId = -916;
    }
    else if (spacecraft.find("17") != string::npos) {
      p_ckFrameId = -917240;
      p_ckReferenceId = 1400017;
      p_spkTargetId = -917;
    }
    else {
      string msg = "File does not appear to be an Apollo image";
      throw iException::Message(iException::User, msg, _FILEINFO_);
    }

    // Create a cache and grab spice info since it does not change for
    // a framing camera (fixed spacecraft position and pointing)
    // Convert the start time to et
    SetTime((string)inst["StartTime"]);
    LoadCache();
    NaifStatus::CheckErrors();
  }

  /**
   * Returns the shutter open and close times. The user should pass in the
   * exposure duration in seconds and the StartTime keyword value, converted to
   * ephemeris time. The StartTime keyword value from the labels represents the
   * shutter center time of the observation. To find the shutter open and close
   * times, half of the exposure duration is subtracted from and added to the
   * input time parameter, respectively.  This method overrides the
   * FramingCamera class method.
   * @b Note: Apollo did not provide exposure duration in the support data.
   *
   * @param exposureDuration Exposure duration, in seconds.
   * @param time The StartTime keyword value from the labels, converted to
   *             ephemeris time.
   *
   * @return @b pair < @b iTime, @b iTime > The first value is the shutter
   *         open time and the second is the shutter close time.
   *
   * @author 2011-05-03 Jeannie Walldren
   * @internal
   *   @history 2011-05-03 Jeannie Walldren - Original version.
   */
  pair<iTime, iTime> ApolloMetricCamera::ShutterOpenCloseTimes(double time,
                                                               double exposureDuration) {
    pair<iTime, iTime> shuttertimes;
    // To get shutter start (open) time, subtract half exposure duration
    shuttertimes.first = time - (exposureDuration / 2.0);
    // To get shutter end (close) time, add half exposure duration
    shuttertimes.second = time + (exposureDuration / 2.0);
    return shuttertimes;
  }
} // End Apollo namespace

/**
 * This is the function that is called in order to instantiate an
 * ApolloMetricCamera object. 
 *
 * @param lab Cube labels
 *
 * @return Camera* ApolloMetricCamera 
 * @internal 
 *   @history 2011-05-03 Jeannie Walldren - Added documentation. Removed Apollo
 *            namespace.
 */
extern "C" Isis::Camera *ApolloMetricCameraPlugin(Isis::Pvl &lab) {
  return new Isis::ApolloMetricCamera(lab);
}
