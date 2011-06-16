#include "Isis.h"
#include "ProcessBySpectra.h"
#include "UserInterface.h"
#include "QuickFilter.h"

using namespace std;
using namespace Isis;

// Which pixel types to filter
int bands;
double low ;
double high;

// Prototype
void Filter(Buffer &in, Buffer &out);

void IsisMain() {
  // Set up ProcessBySpectra
  ProcessBySpectra p;

  // Obtain input cube, get bands dimension from input cube and user input number bands
  Cube *icube = p.SetInputCube("FROM");
  int maxBands = (2 * icube->getBandCount()) - 1;
  UserInterface &ui = Application::GetUserInterface();
  bands = ui.GetInteger("BANDS");

  // Check for cases of too many bands
  if(bands > maxBands) {
    iString msg = "Parameter bands [" + iString(bands) + "] exceeds maximum allowable size "
                  + "of [" + iString(maxBands) + "] for cube [" + icube->getFilename() + "]";
    throw iException::Message(iException::User, msg, _FILEINFO_);
  }

  // Set the Boxcar Parameters
  low = -DBL_MAX;
  high = DBL_MAX;

  if(ui.WasEntered("LOW")) {
    low = ui.GetDouble("LOW");
  }
  if(ui.WasEntered("HIGH")) {
    high = ui.GetDouble("HIGH");
  }

  // Obtain output cube
  p.SetOutputCube("TO");

  // Start the filter method
  p.StartProcess(Filter);
  p.EndProcess();

}

/**
 * Function to loop through the bands, and determine the
 * average value of the pixels around each valid pixel, writing that
 * average to the output at the pixel index
 */
void Filter(Buffer &in, Buffer &out) {
  Isis::QuickFilter filter(in.size(), bands, 1);
  filter.SetMinMax(low, high);
  filter.AddLine(in.DoubleBuffer());

  for(int i = 0; i < in.size(); i ++) {
    out[i] = filter.Average(i);
  }
}

