#ifndef MeasureTableModel_H
#define MeasureTableModel_H

#include <QAbstractTableModel>

template< class T > class QList;

class QModelIndex;
class QString;

namespace Isis
{
  class ControlMeasure;

  class MeasureTableModel : public QAbstractTableModel
  {
      Q_OBJECT

    public:
      // If a column is added or removed then make sure you also update
      // the COLS constant that immediately follows this enum.
      enum Column
      {
        PointId = 0,
        CubeSerialNumber = 1,
        Sample = 2,
        Line = 3,
        EditLock = 4,
        Ignored = 5,
        Type = 6,
        Eccentricity = 7,
        GoodnessOfFit = 8,
        MinPixelZScore = 9,
        MaxPixelZScore = 10,
        PixelShift = 11,
        APrioriSample = 12,
        APrioriLine = 13,
        Diameter = 14,
        JigsawRejected = 15,
        ResidualSample = 16,
        ResidualLine = 17,
        ResidualMagnitude = 18
      };
      static const int COLS = 19;


    public:
      explicit MeasureTableModel(QObject * parent = 0);
      virtual ~MeasureTableModel();

      static QString getColName(Column);

      void setMeasures(QList< ControlMeasure * > newMeasures);
      ControlMeasure * getMeasure(int row) const;

      int rowCount(const QModelIndex & parent) const;
      int columnCount(const QModelIndex & parent) const;
      QVariant data(const QModelIndex & index, int role) const;
      QVariant headerData(int section, Qt::Orientation orientation,
          int role) const;
      Qt::ItemFlags flags(const QModelIndex & index) const;
      bool setData(const QModelIndex & index,
          const QVariant & value, int role = Qt::EditRole);
//       bool insertRows(int position, int rows,
//           const QModelIndex & index = QModelIndex());
//       bool removeRows(int position, int rows,
//           const QModelIndex & index = QModelIndex());


    private:
      MeasureTableModel(const MeasureTableModel &);
      const MeasureTableModel & operator=(MeasureTableModel);


    private:
      bool validateRowColumn(int row, int column,
          bool checkMeasure = true) const;
      double catchNULL(QString) const;
      QString catchNULL(double) const;


    private:
      QList< ControlMeasure * > * measures;
  };
}

#endif
