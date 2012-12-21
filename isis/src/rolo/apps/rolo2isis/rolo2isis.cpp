#include "Isis.h"
#include "ProcessImportPds.h"
#include "UserInterface.h"
#include "FileName.h"
#include "Pvl.h"
#include "PvlTranslationManager.h"

using namespace std;
using namespace Isis;

void IsisMain() {
  UserInterface &ui = Application::GetUserInterface();
  QString labelFile = ui.GetFileName("FROM");

  ProcessImportPds p;
  Pvl label;
  p.SetPdsFile(labelFile, "", label);
  Cube *ocube = p.SetOutputCube("TO");
  p.StartProcess();

  PvlGroup &dataDir = Preference::Preferences().FindGroup("DataDirectory");
  QString transDir = (QString) dataDir["Rolo"];

  FileName transFile;
  Pvl inputLabel(labelFile);
  Pvl outputLabel;
  PvlTranslationManager *translator;

  // translate Mapping group
  transFile = transDir + "/" + "translations/roloMapping.trn";
  translator = new PvlTranslationManager(inputLabel, transFile.expanded());
  translator->Auto(outputLabel);
  delete translator;
  translator = NULL;

  // translate Instrument group
  transFile = transDir + "/" + "translations/roloInstrument.trn";
  translator = new PvlTranslationManager(inputLabel, transFile.expanded());
  translator->Auto(outputLabel);
  delete translator;
  translator = NULL;

  // translate BandBin group
  transFile = transDir + "/" + "translations/roloBandBin.trn";
  translator = new PvlTranslationManager(inputLabel, transFile.expanded());
  translator->Auto(outputLabel);
  outputLabel.FindGroup("BandBin").FindKeyword("OriginalBand").SetUnits(
    translator->Translate("BandBinUnit"));
  outputLabel.FindGroup("BandBin").FindKeyword("Center").SetUnits(translator->
      Translate("BandBinUnit"));
  outputLabel.FindGroup("BandBin").FindKeyword("Width").SetUnits(translator->
      Translate("BandBinUnit"));
  outputLabel.FindGroup("BandBin").FindKeyword("Exposure").SetUnits(translator->
      Translate("ExposureUnit"));
  delete translator;
  translator = NULL;

  // translate Archive group
  transFile = transDir + "/" + "translations/roloArchive.trn";
  translator = new PvlTranslationManager(inputLabel, transFile.expanded());
  translator->Auto(outputLabel);
  delete translator;
  translator = NULL;

  // add outputLabel to cube
  if(outputLabel.HasGroup("Mapping") &&
      (outputLabel.FindGroup("Mapping").Keywords() > 0)) {
    ocube->putGroup(outputLabel.FindGroup("Mapping"));
  }
  if(outputLabel.HasGroup("Instrument") &&
      (outputLabel.FindGroup("Instrument").Keywords() > 0)) {
    ocube->putGroup(outputLabel.FindGroup("Instrument"));
  }
  if(outputLabel.HasGroup("BandBin") &&
      (outputLabel.FindGroup("BandBin").Keywords() > 0)) {
    ocube->putGroup(outputLabel.FindGroup("BandBin"));
  }
  if(outputLabel.HasGroup("Archive") &&
      (outputLabel.FindGroup("Archive").Keywords() > 0)) {
    ocube->putGroup(outputLabel.FindGroup("Archive"));
  }

  p.EndProcess();

  return;
}
