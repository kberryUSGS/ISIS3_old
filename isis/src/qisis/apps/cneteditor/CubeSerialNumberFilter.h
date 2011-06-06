#ifndef CubeSerialNumberFilter_H
#define CubeSerialNumberFilter_H

#include "AbstractStringFilter.h"


class QString;


namespace Isis
{
  class AbstractFilterSelector;
  class ControlCubeGraphNode;
  class ControlMeasure;
  class ControlPoint;

  class CubeSerialNumberFilter : public AbstractStringFilter
  {
      Q_OBJECT

    public:
      CubeSerialNumberFilter(AbstractFilter::FilterEffectivenessFlag,
          AbstractFilterSelector *, int minimumForSuccess = -1);
      virtual ~CubeSerialNumberFilter();
      
      bool evaluate(const ControlCubeGraphNode *) const;
      bool evaluate(const ControlPoint *) const;
      bool evaluate(const ControlMeasure *) const;


      QString getImageDescription() const;
      QString getPointDescription() const;
      QString getMeasureDescription() const;
  };
}

#endif
