#ifndef ChooserNameFilter_H
#define ChooserNameFilter_H

#include "AbstractFilter.h"


class QLineEdit;
class QString;


namespace Isis
{
  class ControlPoint;

  class ChooserNameFilter : public AbstractFilter
  {
      Q_OBJECT

    public:
      ChooserNameFilter(int minimumForImageSuccess = -1);
      virtual ~ChooserNameFilter();
      
      bool canFilterImages() const;
      bool canFilterPoints() const;
      bool canFilterMeasures() const;
      
      bool evaluate(const ControlPoint *) const;
      bool evaluate(const ControlMeasure *) const;
      bool evaluate(const ControlCubeGraphNode *) const;
      
      QString getImageDescription() const;
      QString getPointDescription() const;
      

    protected:
      void nullify();
      void createWidget();
      
      
    private slots:
      void updateLineEditText(QString);


    private:
      QLineEdit * lineEdit;
      QString * lineEditText;
  };
}

#endif
