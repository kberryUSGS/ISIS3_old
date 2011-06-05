#include "IsisDebug.h"

#include "FilterWidget.h"

#include <iostream>

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include <QVBoxLayout>

#include "FilterGroup.h"

using std::cerr;

namespace Isis
{
  FilterWidget::FilterWidget(QString type)
  {
    nullify();
    
    filterGroups = new QList< FilterGroup * >;

    QString whatsThis = "Filters are organized into groups.  Filters within a "
        "group will be combined using either AND or OR logic.  Furthermore, "
        "multiple groups are supported, and the logic used to combine the "
        "various groups is also configurable.  To illustrate what this allows "
        "consider an example.  Let A, B, and C be (filters).  By creating two "
        "groups, one with A and B in it and the other with C in it, it is "
        "possible to build the expression \"(A and B) or C\".";
    
    filterType = type;
    QString title = "Filter " + type;
    QLabel * titleLabel = new QLabel(title);
    titleLabel->setFont(QFont("SansSerif", 15, QFont::DemiBold));
    
    QHBoxLayout * titleLayout = new QHBoxLayout;
    titleLayout->addStretch();
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    
    QLabel * logicTypeLabel = new QLabel(
        "Combine groups using logic type: ");
    QFont logicTypeLabelFont("SansSerif", 12);
    logicTypeLabel->setFont(logicTypeLabelFont);

    QFont logicTypeFont("SansSerif", 12, QFont::Bold);
    QRadioButton * andButton = new QRadioButton("AND");
    andButton->setFont(logicTypeFont);
    QRadioButton * orButton = new QRadioButton("OR");
    orButton->setFont(logicTypeFont);
    QButtonGroup * buttonGroup = new QButtonGroup;
    buttonGroup->addButton(andButton, 0);
    buttonGroup->addButton(orButton, 1);
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this,
        SLOT(changeGroupCombinationLogic(int)));
    
    // FIXME: this should be controlled by QSettings
    orButton->click();

    QHBoxLayout * buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(logicTypeLabel);
    buttonLayout->addWidget(andButton);
    buttonLayout->addWidget(orButton);
    buttonLayout->addStretch();
    logicWidget = new QWidget;
    logicWidget->setLayout(buttonLayout);
    
    addGroupButton = new QPushButton;
    addGroupButton->setIcon(QIcon(":add"));
    addGroupButton->setToolTip("Add Filter Group");
    addGroupButton->setWhatsThis(whatsThis);
    connect(addGroupButton, SIGNAL(clicked()), this, SLOT(addGroup()));
    QHBoxLayout * addGroupLayout = new QHBoxLayout;
    addGroupLayout->addWidget(addGroupButton);
    addGroupLayout->addStretch();
    
    QLabel * titleDummy = new QLabel;
    titleDummy->setFont(QFont("SansSerif", 6)); // FIXME
    
    imageDummy = new QLabel;
    imageDummy->setFont(QFont("SansSerif", 6)); // FIXME
    
    pointDummy = new QLabel;
    pointDummy->setFont(QFont("SansSerif", 6)); // FIXME
    
    measureDummy = new QLabel;
    measureDummy->setFont(QFont("SansSerif", 6)); // FIXME
    
    imageDescription = new QLabel;
    imageDescription->setWordWrap(true);
    imageDescription->setFont(QFont("SansSerif", 10)); // FIXME
    
    pointDescription = new QLabel;
    pointDescription->setWordWrap(true);
    pointDescription->setFont(QFont("SansSerif", 10)); // FIXME
    
    measureDescription = new QLabel;
    measureDescription->setWordWrap(true);
    measureDescription->setFont(QFont("SansSerif", 10)); // FIXME
    
    QVBoxLayout * descriptionLayout = new QVBoxLayout;
    QMargins margins = descriptionLayout->contentsMargins();
    margins.setTop(0);
    margins.setBottom(0);
    descriptionLayout->setContentsMargins(margins);
    descriptionLayout->addWidget(titleDummy);
    descriptionLayout->addWidget(imageDescription);
    descriptionLayout->addWidget(imageDummy);
    descriptionLayout->addWidget(pointDescription);
    descriptionLayout->addWidget(pointDummy);
    descriptionLayout->addWidget(measureDescription);
    descriptionLayout->addWidget(measureDummy);
    
    connect(this, SIGNAL(filterChanged()),
        this, SLOT(updateDescription()));

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(descriptionLayout);
    mainLayout->addWidget(logicWidget);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(addGroupLayout);
    mainLayout->addStretch();
    
    setLayout(mainLayout);
    setWhatsThis(whatsThis);
    
    addGroup();
    updateDescription();
  }


  FilterWidget::~FilterWidget()
  {
    if (filterGroups)
    {
      delete filterGroups;
      filterGroups = NULL;
    }
  }
  
  
  bool FilterWidget::evaluate(const ControlCubeGraphNode * node) const
  {
    // if andFiltersTogether is true then we break out of the loop as soon
    // as any selectors evaluate to false.  If andFiltersTogether is false
    // then we are ORing them so we break out as soon as any selector
    // evaluates to true.  Whether we are looking for successes or failures
    // depends on whether we are ANDing or ORing the filters (selectors)
    // together!!!
    bool looking = true;
    for (int i = 0; looking && i < filterGroups->size(); i++)
    {
      if (filterGroups->at(i)->hasFilter(&AbstractFilter::canFilterImages))
        looking = !(filterGroups->at(i)->evaluate(node) ^
            andGroupsTogether);
    }
    
    // It is good that we are still looking for failures if we were ANDing
    // filters together, but it is bad if we were ORing them since in this
    // case we were looking for success (unless of course there were no
    // filters to look through).
    return !(looking ^ andGroupsTogether) || !hasFilter(&AbstractFilter::canFilterImages);
  }
  
  
  bool FilterWidget::evaluate(const ControlPoint * point) const
  {
    // if andFiltersTogether is true then we break out of the loop as soon
    // as any selectors evaluate to false.  If andFiltersTogether is false
    // then we are ORing them so we break out as soon as any selector
    // evaluates to true.  Whether we are looking for successes or failures
    // depends on whether we are ANDing or ORing the filters (selectors)
    // together!!!
    bool looking = true;
    for (int i = 0; looking && i < filterGroups->size(); i++)
    {
      if (filterGroups->at(i)->hasFilter(&AbstractFilter::canFilterPoints))
        looking = !(filterGroups->at(i)->evaluate(point) ^
            andGroupsTogether);
    }
    
    // It is good that we are still looking for failures if we were ANDing
    // filters together, but it is bad if we were ORing them since in this
    // case we were looking for success (unless of course there were no
    // filters to look through).
    return !(looking ^ andGroupsTogether) || !hasFilter(&AbstractFilter::canFilterPoints);
  }
  
  
  bool FilterWidget::evaluate(const ControlMeasure * measure) const
  {
    // if andFiltersTogether is true then we break out of the loop as soon
    // as any selectors evaluate to false.  If andFiltersTogether is false
    // then we are ORing them so we break out as soon as any selector
    // evaluates to true.  Whether we are looking for successes or failures
    // depends on whether we are ANDing or ORing the filters (selectors)
    // together!!!
    bool looking = true;
    for (int i = 0; looking && i < filterGroups->size(); i++)
    {
      if (filterGroups->at(i)->hasFilter(&AbstractFilter::canFilterMeasures))
        looking = !(filterGroups->at(i)->evaluate(measure) ^
            andGroupsTogether);
    }
    
    // It is good that we are still looking for failures if we were ANDing
    // filters together, but it is bad if we were ORing them since in this
    // case we were looking for success (unless of course there were no
    // filters to look through).
    return !(looking ^ andGroupsTogether) || !hasFilter(&AbstractFilter::canFilterMeasures);
  }
  
  
  bool FilterWidget::hasFilter(bool (AbstractFilter::*meth)() const) const
  {
    bool found = false;
    
    for (int i = 0; !found && i < filterGroups->size(); i++)
      found = filterGroups->at(i)->hasFilter(meth);
    
    return found;
  }
  
  
  void FilterWidget::nullify()
  {
    addGroupButton = NULL;
    imageDescription = NULL;
    pointDescription = NULL;
    measureDescription = NULL;
    mainLayout = NULL;
    filterGroups = NULL;
  }
  
  
  void FilterWidget::updateDescription()
  {
    updateDescription(imageDescription, &AbstractFilter::canFilterImages,
                      &AbstractFilter::getImageDescription, "images");
    updateDescription(pointDescription, &AbstractFilter::canFilterPoints,
                      &AbstractFilter::getPointDescription, "points");
    updateDescription(measureDescription, &AbstractFilter::canFilterMeasures,
                      &AbstractFilter::getMeasureDescription, "measures");
  }
  
  
  void FilterWidget::updateDescription(QLabel * label,
      bool (AbstractFilter::*hasFilterMeth)() const,
      QString (AbstractFilter::*descriptionMeth)() const,
      QString title)
  {
    ASSERT(label);
    
    if (label)
    {
      label->clear();

      QList< FilterGroup * > groups;
      for (int i = 0; i < filterGroups->size(); i++)
        if (filterGroups->at(i)->hasFilter(hasFilterMeth))
          groups.append(filterGroups->at(i));
           
      const int GROUP_SIZE = groups.size();
      
      if (GROUP_SIZE)
      {
        QString black = "<font color=black>";
        QString blue = "<font color=darkBlue>";
        QString red = "<font color=darkRed>";
        QString end = "</font>";

        QString text = "Showing " + red + title + end + black + " which " + end;
        
        QString groupLogic;
        if (andGroupsTogether)
          groupLogic += " AND ";
        else
          groupLogic += " OR ";
        
        QString leftParen = black + "<b>(</b>" + end;
        QString rightParen = black + "<b>)</b>" + end;
        
        for (int i = 0; i < GROUP_SIZE - 1; i++)
        {
          if (GROUP_SIZE > 1)
            text += leftParen;
          text += blue + groups[i]->getDescription(
              hasFilterMeth, descriptionMeth) + end;         
          if (GROUP_SIZE > 1)
            text += rightParen + black + "<b>" + groupLogic + "</b>" + end;
        }
          
        if (GROUP_SIZE > 1)
          text += leftParen;
        text += blue + groups[GROUP_SIZE - 1]->getDescription(
            hasFilterMeth, descriptionMeth) + end;
        if (GROUP_SIZE > 1)
          text += rightParen;
        
        text += black + "." + end;
        
        label->setText(text);
      }
    }
  }
  
  
  void FilterWidget::maybeScroll(FilterGroup * group)
  {
    ASSERT(filterGroups);
    ASSERT(filterGroups->size());
    
    if (filterGroups && filterGroups->size() &&
        filterGroups->at(filterGroups->size() - 1) == group)
      emit scrollToBottom();
  }


  void FilterWidget::addGroup()
  {
    FilterGroup * newGroup = new FilterGroup(filterType);
    connect(newGroup, SIGNAL(close(FilterGroup *)),
        this, SLOT(deleteGroup(FilterGroup *)));
    connect(newGroup, SIGNAL(filterChanged()), this, SIGNAL(filterChanged()));
    connect(newGroup, SIGNAL(sizeChanged(FilterGroup *)),
        this, SLOT(maybeScroll(FilterGroup *)));
    mainLayout->insertWidget(mainLayout->count() - 2, newGroup);
    filterGroups->append(newGroup);
    filterGroups->size() > 1 ? logicWidget->show() : logicWidget->hide();
    
    emit scrollToBottom();
    emit filterChanged();
  }


  void FilterWidget::deleteGroup(FilterGroup * filterGroup)
  {
    mainLayout->removeWidget(filterGroup);
    delete filterGroup;
    filterGroups->removeOne(filterGroup);
    filterGroups->size() > 1 ? logicWidget->show() : logicWidget->hide();
    emit filterChanged();
  }
  
  
  void FilterWidget::changeGroupCombinationLogic(int button)
  {
    andGroupsTogether = button == 0;
    emit filterChanged();
  }
}
