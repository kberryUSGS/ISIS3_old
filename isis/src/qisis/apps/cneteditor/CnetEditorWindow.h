#ifndef CnetEditorWindow_H
#define CnetEditorWindow_H

#include <QMainWindow>

class QAction;
class QButtonGroup;
class QCloseEvent;
class QFont;
class QMenu;
class QString;
class QToolBar;


namespace Isis
{
  class ConcurrentControlNetReader;
  class ControlNet;
  class CnetEditorWidget;
  class ProgressBar;

  class CnetEditorWindow : public QMainWindow
  {
      Q_OBJECT
      
    public:
      enum FileState
      {
        HasFile,
        NoFile,
        FileLoading
      };
      

    public:
      CnetEditorWindow();
      virtual ~CnetEditorWindow();


    protected:
      void closeEvent(QCloseEvent * event);


    private:
      CnetEditorWindow(const CnetEditorWindow &);
      const CnetEditorWindow & operator=(CnetEditorWindow);


    private:
      void nullify();
      void createActions();
      void createMenus();
      void createToolBars();
      void createStatusBar();
      void readSettings();
      void writeSettings();
      bool okToContinue();
      void load(QString filename);
      void setFileState(FileState state, QString filename);
      void setDirty(bool);


    private slots:
      void setDirty();
      void setSaveAsPvl(int);
      void open();
      void save();
      void saveAs();
      void closeNetwork();
      void networkLoaded(ControlNet *);


    private: // widgets
      QAction * openAct;
      QAction * saveAct;
      QAction * saveAsAct;
      QAction * aboutAct;
      QAction * closeAct;
      QAction * quitAct;

      QMenu * fileMenu;
      QMenu * helpMenu;

      QToolBar * mainToolBar;
      
      ProgressBar * loadingProgressBar;


    private: // data
      ControlNet * cnet;
      ConcurrentControlNetReader * cnetReader;
      CnetEditorWidget * editorWidget;
      QString * curFile;
      QFont * labelFont;
      bool dirty;
      bool saveAsPvl;
      
      
    private: // constants
      static const int defaultWindowWidth = 1100;
      static const int defaultWindowHeight = 700;
  };
}

#endif
