#include "IsisDebug.h"

#include "CnetEditorWidget.h"

#include <iostream>

#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QByteArray>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QItemSelection>
#include <QMenu>
#include <QModelIndex>
#include <QScrollArea>
#include <QScrollBar>
#include <QSettings>
#include <QSplitter>
#include <QString>
#include <QStringList>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>

#include "ControlNet.h"
#include "ControlPoint.h"

#include "AbstractMeasureItem.h"
#include "AbstractPointItem.h"
#include "AbstractTreeItem.h"
#include "CnetMeasureTableModel.h"
#include "CnetPointTableModel.h"
#include "CnetTableView.h"
#include "CnetTableViewHeader.h"
#include "CnetTreeView.h"
#include "ConnectionModel.h"
#include "FilterWidget.h"
#include "MeasureTableDelegate.h"
#include "MeasureTableModel.h"
#include "PointTableDelegate.h"
#include "PointTableModel.h"
#include "PointModel.h"
#include "SerialModel.h"


using std::cerr;


namespace Isis
{

//**************************************************************
//**************************************************************
//**************************************************************

  const QString CnetEditorWidget::VERSION = "0.1";

//**************************************************************
//**************************************************************
//**************************************************************


  CnetEditorWidget::CnetEditorWidget(Isis::ControlNet * cNet,
      QString pathForSettings)
  {
    nullify();

    workingVersion = new QString;

    updatingSelection = false;

    controlNet = cNet;
//     connect(controlNet, SIGNAL(networkStructureModified()),
//         this, SLOT(rebuildModels()));

    settingsPath = new QString(pathForSettings);

    QBoxLayout * mainLayout = createMainLayout();
    setLayout(mainLayout);

    topSplitterDefault = new QByteArray(topSplitter->saveState());

    readSettings();

    upgradeVersion();
  }


  CnetEditorWidget::~CnetEditorWidget()
  {
    writeSettings();

    delete topSplitterDefault;
    topSplitterDefault = NULL;

    delete workingVersion;
    workingVersion = NULL;

    delete settingsPath;
    settingsPath = NULL;

    delete pointTreeView;
    pointTreeView = NULL;

    delete serialTreeView;
    serialTreeView = NULL;

    delete connectionTreeView;
    connectionTreeView = NULL;

    delete pointFilterWidget;
    pointFilterWidget = NULL;

    delete serialFilterWidget;
    serialFilterWidget = NULL;

    delete connectionFilterWidget;
    connectionFilterWidget = NULL;
  }


  void CnetEditorWidget::nullify()
  {
    pointTreeView = NULL;
    serialTreeView = NULL;
    connectionTreeView = NULL;

    pointModel = NULL;
    serialModel = NULL;
    connectionModel = NULL;

    pointTableModel = NULL;
    measureTableModel = NULL;

    pointTableView = NULL;
    measureTableView = NULL;

    topSplitter = NULL;
    mainSplitter = NULL;

    filterArea = NULL;

    pointFilterWidget = NULL;
    serialFilterWidget = NULL;
    connectionFilterWidget = NULL;

    controlNet = NULL;
    settingsPath = NULL;
    topSplitterDefault = NULL;
    workingVersion = NULL;
  }


  void CnetEditorWidget::setDriverView(int driverView)
  {
    View view = (View) driverView;
    pointModel->setDrivable(view == PointView);
    serialModel->setDrivable(view == SerialView);
    connectionModel->setDrivable(view == ConnectionView);

//     pointTreeView->selectionModel()->clear();
//     pointTreeView->collapseAll();

//     serialTreeView->selectionModel()->clear();
//     serialTreeView->collapseAll();
//
//     connectionTreeView->selectionModel()->clear();
//     connectionTreeView->collapseAll();
  }


  void CnetEditorWidget::activatePointView()
  {
    setDriverView(0);
  }


  void CnetEditorWidget::activateSerialView()
  {
    setDriverView(1);
  }


  void CnetEditorWidget::activateConnectionView()
  {
    setDriverView(2);
  }


  void CnetEditorWidget::rebuildModels(QList<AbstractTreeItem *> itemsToDelete)
  {
    pointModel->stopWorking();
    serialModel->stopWorking();
    connectionModel->stopWorking();

    foreach (AbstractTreeItem * item, itemsToDelete) {
//       cerr << "CnetEditorWidget::rebuildModels deleting "
//            << item->getPointer() << " (type is pt? "
//            << (item->getPointerType() == AbstractTreeItem::Point)
//            << ")\n";
      item->deleteSource();
    }
    
    pointModel->rebuildItems();
    serialModel->rebuildItems();
    connectionModel->rebuildItems();
  }


  int CnetEditorWidget::getDriverView() const
  {
    View driverView;
    if (pointModel->isDrivable())
    {
      driverView = PointView;
      ASSERT(!serialModel->isDrivable());
      ASSERT(!connectionModel->isDrivable());
    }
    else
    {
      if (serialModel->isDrivable())
      {
        driverView = SerialView;
        ASSERT(!pointModel->isDrivable());
        ASSERT(!connectionModel->isDrivable());
      }
      else
      {
        driverView = ConnectionView;
        ASSERT(connectionModel->isDrivable());
        ASSERT(!pointModel->isDrivable());
        ASSERT(!serialModel->isDrivable());
      }
    }
    return (int) driverView;
  }


  QBoxLayout * CnetEditorWidget::createMainLayout()
  {
    createPointTreeView();
    createSerialTreeView();
    createConnectionTreeView();

    connect(pointTreeView, SIGNAL(activated()),
        serialTreeView, SLOT(deactivate()));
    connect(pointTreeView, SIGNAL(activated()),
        connectionTreeView, SLOT(deactivate()));

    connect(serialTreeView, SIGNAL(activated()),
        pointTreeView, SLOT(deactivate()));
    connect(serialTreeView, SIGNAL(activated()),
        connectionTreeView, SLOT(deactivate()));

    connect(connectionTreeView, SIGNAL(activated()),
        pointTreeView, SLOT(deactivate()));
    connect(connectionTreeView, SIGNAL(activated()),
        serialTreeView, SLOT(deactivate()));

    createFilterArea();

    createPointTableView();
    QGroupBox * pointTableBox = new QGroupBox(tr("Control Point Table"));
    QHBoxLayout * pointTableLayout = new QHBoxLayout;
    pointTableLayout->addWidget(pointTableView);
    pointTableBox->setLayout(pointTableLayout);

    createMeasureTableView();
    QGroupBox * measureTableBox = new QGroupBox(tr("Control Measure Table"));
    QHBoxLayout * measureTableLayout = new QHBoxLayout;
    measureTableLayout->addWidget(measureTableView);
    measureTableBox->setLayout(measureTableLayout);

    topSplitter = new QSplitter(Qt::Horizontal);
//     topSplitter->setChildrenCollapsible(false);
//     topSplitter->addWidget(pointTreeView);
//     topSplitter->addWidget(serialTreeView);
//     topSplitter->addWidget(connectionTreeView);
//     topSplitter->addWidget(filterArea);

    mainSplitter = new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(topSplitter);
    mainSplitter->addWidget(pointTableBox);
    mainSplitter->addWidget(measureTableBox);

    QBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mainSplitter);

    return mainLayout;
  }


  void CnetEditorWidget::createPointTreeView()
  {
    pointTreeView = new CnetTreeView();
    pointTreeView->setTitle("Point View");
    pointModel = new PointModel(controlNet, pointTreeView, qApp);
    pointTreeView->setModel(pointModel);
    connect(pointTreeView, SIGNAL(activated()),
        this, SLOT(activatePointView()));
//    connect(pointTreeView, SIGNAL(selectionChanged()),
//        this, SLOT(pointTreeViewSelectionChanged()));
  }


  void CnetEditorWidget::createSerialTreeView()
  {
    serialTreeView = new CnetTreeView();
    serialTreeView->setTitle("Cube View");
    serialModel = new SerialModel(controlNet, serialTreeView, qApp);
    serialTreeView->setModel(serialModel);
    connect(serialTreeView, SIGNAL(activated()),
        this, SLOT(activateSerialView()));
    connect(serialTreeView, SIGNAL(selectionChanged()),
        this, SLOT(serialTreeViewSelectionChanged()));
  }


  void CnetEditorWidget::createConnectionTreeView()
  {
    connectionTreeView = new CnetTreeView();
    connectionTreeView->setTitle("Cube Connection View");
    connectionModel = new ConnectionModel(controlNet, connectionTreeView, qApp);
    connectionTreeView->setModel(connectionModel);
    connect(connectionTreeView, SIGNAL(activated()),
        this, SLOT(activateConnectionView()));
    connect(connectionTreeView, SIGNAL(selectionChanged()),
        this, SLOT(connectionTreeViewSelectionChanged()));
  }


  void CnetEditorWidget::createFilterArea()
  {
    ASSERT(pointModel);
    ASSERT(serialModel);
    ASSERT(connectionModel);

    FilterWidget * pointFilter = new FilterWidget("Points and Measures");
    if (pointModel)
    {
      pointModel->setFilter(pointFilter);
    }

    QHBoxLayout * pointFilterLayout = new QHBoxLayout;
    pointFilterLayout->addWidget(pointFilter);
    QWidget * pointArea = new QWidget;
    pointArea->setLayout(pointFilterLayout);
    QScrollArea * pointFilterScrollArea = new QScrollArea;
    pointFilterScrollArea->setWidget(pointArea);
    pointFilterScrollArea->setWidgetResizable(true);
    pointFilterWidget = pointFilterScrollArea;

    FilterWidget * serialFilter = new FilterWidget("Images and Points");
    if (serialModel)
    {
      serialModel->setFilter(serialFilter);
    }

    QHBoxLayout * serialFilterLayout = new QHBoxLayout;
    serialFilterLayout->addWidget(serialFilter);
    QWidget * serialArea = new QWidget;
    serialArea->setLayout(serialFilterLayout);
    QScrollArea * serialFilterScrollArea = new QScrollArea;
    serialFilterScrollArea->setWidget(serialArea);
    serialFilterScrollArea->setWidgetResizable(true);
    serialFilterWidget = serialFilterScrollArea;

    FilterWidget * connectionFilter = new FilterWidget("Connections");
    if (connectionModel)
    {
      connectionModel->setFilter(connectionFilter);
    }

    QHBoxLayout * connectionFilterLayout = new QHBoxLayout;
    connectionFilterLayout->addWidget(connectionFilter);
    QWidget * connectionArea = new QWidget;
    connectionArea->setLayout(connectionFilterLayout);
    QScrollArea * connectionFilterScrollArea = new QScrollArea;
    connectionFilterScrollArea->setWidget(connectionArea);
    connectionFilterScrollArea->setWidgetResizable(true);
    connectionFilterWidget = connectionFilterScrollArea;
  }


  void CnetEditorWidget::createPointTableView()
  {
    pointTableView = new CnetTableView;
    pointTableModel = new CnetPointTableModel(pointModel);
    pointTableView->setModel(pointTableModel);
    connect(pointTableView, SIGNAL(modelDataChanged()),
            this, SIGNAL(cnetModified()));
    connect(pointTreeView, SIGNAL(selectionChanged()),
            pointTableView, SLOT(onModelSelectionChanged()));
    connect(pointTableView, SIGNAL(selectionChanged()),
            pointTreeView, SLOT(onModelSelectionChanged()));
    connect(pointTableView, SIGNAL(rebuildModels(QList<AbstractTreeItem *>)),
            this, SLOT(rebuildModels(QList<AbstractTreeItem *>)));

    for (int i = 0; i < AbstractPointItem::COLS; i++)
    {
      QAction * act = new QAction(
        AbstractPointItem::getColumnName((AbstractPointItem::Column) i), this);
      act->setCheckable(true);
      connect(act, SIGNAL(toggled(bool)), this, SLOT(pointColToggled()));
      pointTableView->getHorizontalHeader()->addAction(act);
    }

    pointTableView->getHorizontalHeader()->setContextMenuPolicy(
      Qt::ActionsContextMenu);
  }


  void CnetEditorWidget::createMeasureTableView()
  {
    measureTableView = new CnetTableView();
    measureTableModel = new CnetMeasureTableModel(pointModel);
    measureTableView->setModel(measureTableModel);
    connect(measureTableView, SIGNAL(modelDataChanged()),
            this, SIGNAL(cnetModified()));
    connect(pointTreeView, SIGNAL(selectionChanged()),
        measureTableView, SLOT(onModelSelectionChanged()));
    connect(measureTableView, SIGNAL(selectionChanged()),
        pointTreeView, SLOT(onModelSelectionChanged()));
    connect(measureTableView, SIGNAL(rebuildModels(QList<AbstractTreeItem *>)),
            this, SLOT(rebuildModels(QList<AbstractTreeItem *>)));

    for (int i = 0; i < AbstractMeasureItem::COLS; i++)
    {
      QAction * act = new QAction(AbstractMeasureItem::getColumnName(
          (AbstractMeasureItem::Column) i), this);
      act->setCheckable(true);
      connect(act, SIGNAL(toggled(bool)), this, SLOT(measureColToggled()));
      measureTableView->getHorizontalHeader()->addAction(act);
    }

    measureTableView->getHorizontalHeader()->setContextMenuPolicy(
      Qt::ActionsContextMenu);
  }


//  void CnetEditorWidget::pointTreeViewSelectionChanged()
//  {
//    QList< ControlPoint * > points;
//    QList< ControlMeasure * > measures;
//    QStringList cubeSerialNumbers;
//
//    QList< AbstractTreeItem * > selectedItems = pointModel->getSelectedItems();
//
//    for (int i = 0; i < selectedItems.size(); i++)
//    {
//      AbstractTreeItem * currentItem = selectedItems.at(i);
//      AbstractTreeItem::InternalPointerType type =
//        currentItem->getPointerType();
//
//      if (type == AbstractTreeItem::Point)
//      {
//        ControlPoint * point =
//          (*controlNet)[currentItem->getData()];
//        points << point;
//
//        // Grab all of the point's measures.
//        for (int i = 0; i < currentItem->childCount(); i++)
//          if (currentItem->childAt(i)->isVisible())
//            measures <<
//                (*point)[currentItem->childAt(i)->getData()];
//      }
//      else if (type == AbstractTreeItem::Measure)
//      {
//        QString pointId = currentItem->parent()->getData();
//        QString serial = currentItem->getData();
//
//        measures << controlNet->GetPoint(pointId)->GetMeasure(serial);
//        cubeSerialNumbers << serial;
//      }
//      else
//      {
//        ASSERT(0);
//      }
//    }
//
//    // populate editor tables
////    editPointModel->setPoints(points);
//    measureTableModel->setMeasures(measures);
//
//    if (pointModel->isDrivable())
//    {
//      focusView(serialTreeView, cubeSerialNumbers);
//      focusView(connectionTreeView, cubeSerialNumbers);
//    }
//
//    updatingSelection = false;
//  }


  void CnetEditorWidget::serialTreeViewSelectionChanged()
  {
//     if (updatingSelection)
//       return;
//     updatingSelection = true;
//
//     updateTreeItemsWithNewSelection(newSelected, newDeselected);
//
//     QList< ControlPoint * > points;
//     QList< ControlMeasure * > measures;
//     QStringList pointIds;
//     QStringList cubeSerialNumbers;
//     QList< QModelIndex > indexes =
//         serialTreeView->selectionModel()->selectedIndexes();
//     for (int i = 0; i < indexes.size(); i++)
//     {
//       AbstractTreeItem * item = static_cast< AbstractTreeItem * >(
//           indexes[i].internalPointer());
//       AbstractTreeItem::InternalPointerType type = item->pointerType();
//
//       if (type == AbstractTreeItem::CubeGraphNode)
//       {
//         cubeSerialNumbers << item->data().toString();
//       }
//       else
//       {
//         if (type == AbstractTreeItem::Point)
//         {
//           QString pointId = item->data().toString();
//           pointIds << pointId;
//
//           ControlPoint * point = controlNet->GetPoint(pointId);
//           points << point;
//           measures << point->GetMeasure(item->parent()->data().toString());
//         }
//         else
//         {
//           ASSERT(0);
//         }
//       }
//     }
//
//     editPointModel->setPoints(points);
//     measureTableModel->setMeasures(measures);
//
//     if (serialModel->isDrivable())
//     {
// //       focusView(pointTreeView, pointIds);
//       focusView(connectionTreeView, cubeSerialNumbers);
//     }
//
//     updatingSelection = false;
  }



  void CnetEditorWidget::connectionTreeViewSelectionChanged()
  {
//     if (updatingSelection)
//       return;
//     updatingSelection = true;
//
//     updateTreeItemsWithNewSelection(newSelected, newDeselected);
//
//     QList< ControlPoint * > points;
//     QList< ControlMeasure * > measures;
//     QStringList pointIds;
//     QStringList cubeSerialNumbers;
//     QList< QModelIndex > indexes =
//       connectionTreeView->selectionModel()->selectedIndexes();
//     for (int i = 0; i < indexes.size(); i++)
//     {
//       AbstractTreeItem * item = static_cast< AbstractTreeItem * >(
//           indexes[i].internalPointer());
//       AbstractTreeItem::InternalPointerType type = item->pointerType();
//
//       if (type == AbstractTreeItem::CubeGraphNode)
//       {
//         cubeSerialNumbers << item->data().toString();
//       }
//       else
//       {
//         if (type == AbstractTreeItem::Point)
//         {
//           QString pointId = item->data().toString();
//           pointIds << pointId;
//
//           ControlPoint * point = controlNet->GetPoint(pointId);
//           points << point;
// //           measures << point->GetMeasure(item->parent()->data().toString()) <<
// //               point->GetMeasure(item->parent()->parent()->data().toString());
//         }
//         else
//         {
//           ASSERT(0);
//         }
//       }
//     }
//
//     editPointModel->setPoints(points);
//     measureTableModel->setMeasures(measures);
//
//     if (connectionModel->isDrivable())
//     {
// //       focusView(pointTreeView, pointIds);
//       focusView(serialTreeView, cubeSerialNumbers);
//     }
//
//     updatingSelection = false;
  }


  void CnetEditorWidget::rebuildModels()
  {
    rebuildModels(QList< AbstractTreeItem * >());
    
    
    
    
    
//     QTime timer;
//     timer.start();
//     cerr << "CnetEditorWidget::rebuildModels called\n";
//     ASSERT(pointModel);
//     ASSERT(serialModel);
//     ASSERT(connectionModel);
// 
//     updatingSelection = true;
// 
// //     cerr << "CnetEditorWidget::rebuildModels one\n";
// //     pointModel->saveViewState();
//     pointModel->rebuildItems();
// //     pointModel->loadViewState();
// 
// //     cerr << "CnetEditorWidget::rebuildModels two\n";
// //     serialModel->saveViewState();
//     serialModel->rebuildItems();
// //     serialModel->loadViewState();
// 
// //     cerr << "CnetEditorWidget::rebuildModels three\n";
// //     connectionModel->saveViewState();
//     connectionModel->rebuildItems();
// //     connectionModel->loadViewState();
// 
//     updatingSelection = false;
//     cerr << "CnetEditorWidget::rebuildModels done\n";
//     cerr << "rebuildModels elapsed time: " << timer.elapsed() << "\n";
  }


//   void CnetEditorWidget::scrollFilterAreaToBottom()
//   {
//     QTimer::singleShot(100, this, SLOT(doScroll()));
//   }


//   void CnetEditorWidget::doScroll()
//   {
//     ASSERT(filterArea);
//
//     if (filterArea)
//     {
//       QScrollBar * vsb = filterArea->verticalScrollBar();
//       vsb->setValue(vsb->maximum());
//     }
//   }


  void CnetEditorWidget::pointColToggled()
  {
    QList< QAction * > actions =
      pointTableView->getHorizontalHeader()->actions();

    for (int i = 0; i < actions.size(); i++)
    {
      pointTableView->setColumnVisible(actions[i]->text(),
          actions[i]->isChecked());
    }
  }


  void CnetEditorWidget::measureColToggled()
  {
    QList< QAction * > actions =
      measureTableView->getHorizontalHeader()->actions();
    for (int i = 0; i < actions.size(); i++)
      measureTableView->setColumnVisible(actions[i]->text(),
          actions[i]->isChecked());
  }


  void CnetEditorWidget::focusView(CnetTreeView * treeView, QStringList labels)
  {
//     QAbstractItemModel * model = view->model();
//     for (int i = 0; i < model->rowCount(); i++)
//     {
//       QModelIndex index = model->index(i, 0, QModelIndex());
//       AbstractTreeItem * item = static_cast< AbstractTreeItem * >(
//           index.internalPointer());
//
//       bool hit = labels.contains(
//           model->data(index, Qt::DisplayRole).toString());
//       bool shouldExpand = hit && labels.size() == 1;
//
//       item->setSelected(hit);
//       view->selectionModel()->select(index, hit ? QItemSelectionModel::Select :
//           QItemSelectionModel::Deselect);
//
//       item->setExpanded(shouldExpand);
//       view->setExpanded(index, shouldExpand);
//
//       if (hit)
//         view->scrollTo(index, QAbstractItemView::PositionAtCenter);
//     }
  }


  void CnetEditorWidget::upgradeVersion()
  {
    if (*workingVersion == "")
    {
      topSplitter->restoreState(*topSplitterDefault);
      *workingVersion = "0.1";
    }

    if (*workingVersion != VERSION)
      upgradeVersion();
  }


  void CnetEditorWidget::readSettings()
  {
    ASSERT(topSplitter);
    ASSERT(workingVersion);
    ASSERT(settingsPath);
    ASSERT(measureTableView);

    QSettings settings(*settingsPath, QSettings::NativeFormat);
    *workingVersion = settings.value("version", "").toString();
    setDriverView(settings.value("driverView", PointView).toInt());

    topSplitter->restoreState(settings.value("topSplitter").toByteArray());
    mainSplitter->restoreState(settings.value("mainSplitter").toByteArray());

    QList< QAction * > actions =
      measureTableView->getHorizontalHeader()->actions();
    for (int i = 0; i < actions.size(); i++)
    {
      actions[i]->setChecked(settings.value("measure table column: " +
          MeasureTableModel::getColName((MeasureTableModel::Column) i),
          true).toBool());
    }

    actions = pointTableView->getHorizontalHeader()->actions();
    for (int i = 0; i < actions.size(); i++)
    {
      actions[i]->setChecked(settings.value("point table column: " +
          AbstractPointItem::getColumnName((AbstractPointItem::Column) i),
          true).toBool());
    }
  }


  void CnetEditorWidget::writeSettings()
  {
    ASSERT(topSplitter);
    ASSERT(mainSplitter);
    ASSERT(settingsPath);
    ASSERT(measureTableView);

    QSettings settings(*settingsPath, QSettings::NativeFormat);
    settings.setValue("version", VERSION);
    settings.setValue("topSplitter", topSplitter->saveState());
    settings.setValue("mainSplitter", mainSplitter->saveState());
    settings.setValue("driverView", getDriverView());

    QList< QAction * > actions =
      measureTableView->getHorizontalHeader()->actions();
    for (int i = 0; i < actions.size(); i++)
    {
      settings.setValue("measure table column: " +
          MeasureTableModel::getColName((MeasureTableModel::Column) i),
          actions[i]->isChecked());
    }

//     actions = pointTableView->getHorizontalHeader()->actions();
//     for (int i = 0; i < actions.size(); i++) {
//       settings.setValue("point table column: " +
//           AbstractPointItem::getColName((AbstractPointItem::Column) i),
//           actions[i]->isChecked());
//     }
  }

  QWidget * CnetEditorWidget::getPointTreeView()
  {
    return pointTreeView;
  }


  QWidget * CnetEditorWidget::getSerialTreeView()
  {
    return serialTreeView;
  }


  QWidget * CnetEditorWidget::getConnectionTreeView()
  {
    return connectionTreeView;
  }


  QWidget * CnetEditorWidget::getPointFilterWidget()
  {
    return pointFilterWidget;
  }


  QWidget * CnetEditorWidget::getSerialFilterWidget()
  {
    return serialFilterWidget;
  }


  QWidget * CnetEditorWidget::getConnectionFilterWidget()
  {
    return connectionFilterWidget;
  }
}
