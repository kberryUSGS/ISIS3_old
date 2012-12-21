#include "Isis.h"
#include "Cube.h"
#include "ProcessByLine.h"
#include "Pvl.h"
#include "SubArea.h"

#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;
using namespace Isis;

void IsisMain() {
  Isis::Preference::Preferences(true);
  UserInterface &ui = Application::GetUserInterface();
  ProcessByLine p1;
  Pvl inlabel;
  Cube cube;

  int sl, ss;
  int el, es;
  double linc, sinc;
  int inl, ins;
  int onl, ons;

  p1.SetInputCube("FROM1");
  QString from1 = ui.GetFileName("FROM1");
  Cube inomapcube;
  inomapcube.open(from1);
  inl = inomapcube.getLineCount();
  ins = inomapcube.getSampleCount();
  sl = 1;
  ss = 1;
  el = inl;
  es = ins;
  linc = 1.0;
  sinc = 1.0;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  Cube *onomapcube = p1.SetOutputCube("TO", ons, onl, 1);

  PvlGroup results("Results");
  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  SubArea s;
  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&inomapcube, onomapcube, results);

  cout << "Input unprojected cube label: " << endl << endl;
  inlabel = *inomapcube.getLabel();
  cout << inlabel.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(inlabel.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << inlabel.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(inlabel.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << inlabel.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(inlabel.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << inlabel.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  cout << "Testing no change in image area for unprojected cube..." << endl << endl;
  Isis::Application::Log(results);
  cout << endl;
  p1.EndProcess();

  cout << "Output cube label: " << endl << endl;
  QString file = ui.GetFileName("TO");
  Pvl label(file);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  cube.open(file);
  cube.close(true);

  results.Clear();

  ProcessByLine p2;
  p2.SetInputCube("FROM1");
  linc = 2.0;
  sinc = 2.0;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  onomapcube = p2.SetOutputCube("TO", ons, onl, 1);

  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&inomapcube, onomapcube, results);

  cout << "Testing full image area with linc=2, sinc=2 ";
  cout << "for unprojected cube..." << endl;

  Isis::Application::Log(results);
  cout << endl;
  p2.EndProcess();

  cout << "Output cube label: " << endl << endl;
  cube.open(file);
  label = *cube.getLabel();
  cube.close(true);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  results.Clear();

  ProcessByLine p3;
  p3.SetInputCube("FROM1");
  linc = 2.0;
  sinc = 3.0;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  onomapcube = p3.SetOutputCube("TO", ons, onl, 1);

  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&inomapcube, onomapcube, results);

  cout << "Testing full image area with linc=2, sinc=3 ";
  cout << "for unprojected cube..." << endl;

  Isis::Application::Log(results);
  cout << endl;
  p3.EndProcess();

  cout << "Output cube label: " << endl << endl;
  cube.open(file);
  label = *cube.getLabel();
  cube.close(true);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  results.Clear();

  ProcessByLine p4;
  p4.SetInputCube("FROM1");
  sl = 25;
  ss = 10;
  el = inl - 33;
  es = ins - 18;
  linc = .5;
  sinc = .5;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  onomapcube = p4.SetOutputCube("TO", ons, onl, 1);

  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&inomapcube, onomapcube, results);

  cout << "Testing sub image area with linc=.5, sinc=.5 ";
  cout << "for unprojected cube..." << endl;

  Isis::Application::Log(results);
  cout << endl;
  p4.EndProcess();

  cout << "Output cube label: " << endl << endl;
  cube.open(file);
  label = *cube.getLabel();
  cube.close(true);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  results.Clear();

  ProcessByLine p5;
  p5.SetInputCube("FROM1");
  linc = 1.0;
  sinc = 2.5;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  onomapcube = p5.SetOutputCube("TO", ons, onl, 1);

  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&inomapcube, onomapcube, results);

  cout << "Testing sub image area with linc=1.0, sinc=2.5 ";
  cout << "for unprojected cube..." << endl;

  Isis::Application::Log(results);
  cout << endl;
  p5.EndProcess();

  cout << "Output cube label: " << endl << endl;
  cube.open(file);
  label = *cube.getLabel();
  cube.close(true);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  inomapcube.close();

  results.Clear();

  ProcessByLine p6;
  p6.SetInputCube("FROM2");
  QString from2 = ui.GetFileName("FROM2");
  Cube imapcube;
  imapcube.open(from2);
  inl = imapcube.getLineCount();
  ins = imapcube.getSampleCount();
  sl = 1;
  ss = 1;
  el = inl;
  es = ins;
  linc = 1.0;
  sinc = 1.0;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  Cube *omapcube = p6.SetOutputCube("TO", ons, onl, 1);

  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&imapcube, omapcube, results);

  cout << "Input projected cube label: " << endl << endl;
  inlabel = *imapcube.getLabel();
  cout << inlabel.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(inlabel.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << inlabel.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(inlabel.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << inlabel.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(inlabel.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << inlabel.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  cout << "Testing no change in image area for projected cube..." << endl;
  Isis::Application::Log(results);
  cout << endl;
  p6.EndProcess();

  cout << "Output cube label: " << endl << endl;
  cube.open(file);
  label = *cube.getLabel();
  cube.close(true);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  results.Clear();

  ProcessByLine p7;
  p7.SetInputCube("FROM2");
  linc = 2.0;
  sinc = 2.0;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  omapcube = p7.SetOutputCube("TO", ons, onl, 1);

  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&imapcube, omapcube, results);

  cout << "Testing full image area with linc=2, sinc=2 ";
  cout << "for projected cube..." << endl;

  Isis::Application::Log(results);
  cout << endl;
  p7.EndProcess();

  cout << "Output cube label: " << endl << endl;
  cube.open(file);
  label = *cube.getLabel();
  cube.close(true);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  results.Clear();

  ProcessByLine p8;
  p8.SetInputCube("FROM2");
  linc = 2.0;
  sinc = 3.0;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  omapcube = p8.SetOutputCube("TO", ons, onl, 1);

  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&imapcube, omapcube, results);

  cout << "Testing full image area with linc=2, sinc=3 ";
  cout << "for projected cube..." << endl;

  Isis::Application::Log(results);
  cout << endl;
  p8.EndProcess();

  cout << "Output cube label: " << endl << endl;
  cube.open(file);
  label = *cube.getLabel();
  cube.close(true);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  results.Clear();

  ProcessByLine p9;
  p9.SetInputCube("FROM2");
  sl = 25;
  ss = 10;
  el = inl - 33;
  es = ins - 18;
  linc = .5;
  sinc = .5;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  omapcube = p9.SetOutputCube("TO", ons, onl, 1);

  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&imapcube, omapcube, results);

  cout << "Testing sub image area with linc=.5, sinc=.5 ";
  cout << "for projected cube..." << endl;

  Isis::Application::Log(results);
  cout << endl;
  p9.EndProcess();

  cout << "Output cube label: " << endl << endl;
  cube.open(file);
  label = *cube.getLabel();
  cube.close(true);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  results.Clear();

  ProcessByLine p10;
  p10.SetInputCube("FROM2");
  linc = 1.0;
  sinc = 2.5;
  onl = (int)ceil((double)(el - sl + 1) / linc);
  ons = (int)ceil((double)(es - ss + 1) / sinc);
  omapcube = p10.SetOutputCube("TO", ons, onl, 1);

  results += PvlKeyword("InputLines", toString(inl));
  results += PvlKeyword("InputSamples", toString(ins));
  results += PvlKeyword("StartingLine", toString(sl));
  results += PvlKeyword("StartingSample", toString(ss));
  results += PvlKeyword("EndingLine", toString(el));
  results += PvlKeyword("EndingSample", toString(es));
  results += PvlKeyword("LineIncrement", toString(linc));
  results += PvlKeyword("SampleIncrement", toString(sinc));
  results += PvlKeyword("OutputLines", toString(onl));
  results += PvlKeyword("OutputSamples", toString(ons));

  s.SetSubArea(inl, ins, sl, ss, el, es, linc, sinc);
  s.UpdateLabel(&imapcube, omapcube, results);

  cout << "Testing sub image area with linc=1.0, sinc=2.5 ";
  cout << "for projected cube..." << endl;

  Isis::Application::Log(results);
  cout << endl;
  p10.EndProcess();

  cout << "Output cube label: " << endl << endl;
  cube.open(file);
  label = *cube.getLabel();
  cube.close(true);
  cout << label.FindObject("IsisCube").FindObject("Core").FindGroup("Dimensions") << endl << endl;
  if(label.FindObject("IsisCube").HasGroup("Instrument")) {
    cout << label.FindObject("IsisCube").FindGroup("Instrument") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("Mapping")) {
    cout << label.FindObject("IsisCube").FindGroup("Mapping") << endl << endl;
  }
  if(label.FindObject("IsisCube").HasGroup("AlphaCube")) {
    cout << label.FindObject("IsisCube").FindGroup("AlphaCube") << endl << endl;
  }

  imapcube.close();

  results.Clear();
}
