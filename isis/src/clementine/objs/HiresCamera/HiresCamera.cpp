#include "HiresCamera.h"
#include "CameraDetectorMap.h"
#include "CameraFocalPlaneMap.h"
#include "CameraDistortionMap.h"
#include "CameraGroundMap.h"
#include "CameraSkyMap.h"
#include "iString.h"

using namespace std;
using namespace Isis;
namespace Clementine {
  HiresCamera::HiresCamera (Pvl &lab) : FramingCamera(lab) {

    // Get the camera characteristics
    iString filter = (string)(lab.FindGroup("BandBin", Pvl::Traverse))["FilterName"];
    filter = filter.UpCase();

    SetFocalLength ();
    SetPixelPitch ();

    // Get the start time in et
    PvlGroup inst = lab.FindGroup ("Instrument",Pvl::Traverse);
    string stime = inst["StartTime"];

    double time; 
    str2et_c(stime.c_str(),&time);



    // Do not correct time for center of the exposure duration. This is because
    // the kernels were built to accept the start times of the images. 
    // time += ((double)inst["ExposureDuration"] / 1000.0) / 2.0; // Add half
    // exposure duration in milliseconds

    // Setup detector map
    new CameraDetectorMap(this);

    // Setup focal plane map
    CameraFocalPlaneMap *focalMap = new CameraFocalPlaneMap(this,NaifIkCode());

    focalMap->SetDetectorOrigin (
                   Spice::GetDouble("INS" + (iString)(int)NaifIkCode() +
                                    "_BORESIGHT_SAMPLE"), 
                   Spice::GetDouble("INS" + (iString)(int)NaifIkCode() +
                                    "_BORESIGHT_LINE"));

    // Setup distortion map 
    new CameraDistortionMap(this);

    // Setup the ground and sky map
    new CameraGroundMap(this);
    new CameraSkyMap(this);

    SetEphemerisTime(time);
    LoadCache();
  }
}

extern "C" Camera *HiresCameraPlugin(Pvl &lab) {
  return new Clementine::HiresCamera(lab);
}
