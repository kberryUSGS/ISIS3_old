#ifndef MainWindow_h
#define MainWindow_h
#include <QMainWindow>
#include <QtGui>
#include <QSettings>
#include "FileName.h"

namespace Isis {
  /**
  * @brief Base class for the Qisis main windows
  *
  * @ingroup Visualization Tools
  *
  * @author ????-??-?? Stacy Alley
  *
  * @internal
  *   @history 2012-04-05 Steven Lambright - Improved saving and restoring state
  *                         by making the closeEvent() and hideEvent() actually
  *                         override the parent's methods and removing the
  *                         eventFilter. References #593.
  */
  class MainWindow : public QMainWindow {
      Q_OBJECT
    public:
      MainWindow(QString title, QWidget *parent = 0, Qt::WFlags flags = 0);
      virtual ~MainWindow();

      static QString settingsFileName(QString objectTitle);

    protected:
      virtual void closeEvent(QCloseEvent *event);
      virtual void readSettings(QSize defaultSize = QSize());
      QString settingsFileName() const;

    private:
      virtual void writeSettings() const;

  };
};

#endif

