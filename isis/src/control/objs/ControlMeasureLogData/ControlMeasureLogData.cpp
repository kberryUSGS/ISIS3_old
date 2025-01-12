#include "ControlMeasureLogData.h"

#include <QVariant>

#include "ControlNetFileV0001.pb.h"
#include "ControlNetFileV0002.pb.h"
#include "PvlKeyword.h"
#include "SpecialPixel.h"

namespace Isis {
  /**
   * This creates an empty, invalid (IsValid() will return false), instance.
   */
  ControlMeasureLogData::ControlMeasureLogData() {
    Init();
  }


  /**
   * This creates an instance with the given type and value for that type.
   *
   * @param dataType What the value is describing (the field)
   * @param value The numerical value of this field
   */
  ControlMeasureLogData::ControlMeasureLogData(NumericLogDataType dataType,
                                               double value) {
    p_dataType = dataType;
    p_numericalValue = value;
  }


  /**
   * This creates an instance with the given type but no value yet. IsValid()
   *   will return false until a value is set.
   *
   * @param dataType What the instance is describing (the field)
   */
  ControlMeasureLogData::ControlMeasureLogData(NumericLogDataType dataType) {
    Init();
    p_dataType = dataType;
  }


  /**
   * This creates an instance while attempting to interpret keywordRep.
   *
   * On failure, the IsValid() test will return false.
   *
   * @param keywordRep The PvlKeyword representing log data
   */
  ControlMeasureLogData::ControlMeasureLogData(PvlKeyword keywordRep) {
    Init();

    QString name = keywordRep.name();
    p_dataType = NameToDataType(name);
    if (p_dataType != InvalidNumericLogDataType)
      p_numericalValue = toDouble(keywordRep[0]);
  }


  /**
   * This creates an instance based on the protocol buffer. This assumes the
   *   protocol buffer is correct and does no extra validation.
   *
   * @param protoBuf The protocol buffer version of a log data
   */
  ControlMeasureLogData::ControlMeasureLogData(
      const ControlNetLogDataProtoV0001_Point_Measure_DataEntry &protoBuf) {
    p_dataType = (NumericLogDataType)protoBuf.datatype();
    p_numericalValue = protoBuf.datavalue();
  }


  /**
   * This creates an instance based on the protocol buffer. This assumes the
   *   protocol buffer is correct and does no extra validation.
   *
   * @param protoBuf The protocol buffer version of a log data
   */
  ControlMeasureLogData::ControlMeasureLogData(
      const ControlPointFileEntryV0002_Measure_MeasureLogData &protoBuf) {
    if(protoBuf.has_doubledatatype()) {
      p_dataType = (NumericLogDataType)protoBuf.doubledatatype();
      p_numericalValue = protoBuf.doubledatavalue();
    }
  }


  /**
   * Copy constructor.
   *
   * @param other The instance to copy into this one.
   */
  ControlMeasureLogData::ControlMeasureLogData(const ControlMeasureLogData&
      other) {
    p_dataType = other.p_dataType;
    p_numericalValue = other.p_numericalValue;
  }


  /**
   * Destructor. This frees allocated memory by the instance of this class.
   */
  ControlMeasureLogData::~ControlMeasureLogData() {
  }


  /**
   * This is a helper method for the constructor that initializes the data to
   *   a default, invalid state.
   */
  void ControlMeasureLogData::Init() {
    p_dataType = InvalidNumericLogDataType;
    p_numericalValue = Null;
  }


  /**
   * This updates the value associated with a NumericLogDataType.
   *
   * @param value The new value for this log data
   */
  void ControlMeasureLogData::SetNumericalValue(double value) {
    p_numericalValue = value;
  }


  /**
   * This changes the type of this log data. This will reset the value of the
   *   log data also.
   *
   * @param newDataType The data type this log data should represent
   */
  void ControlMeasureLogData::SetDataType(NumericLogDataType newDataType) {
    Init();
    p_dataType = newDataType;
  }


  /**
   * Get the value associated with this log data. Returns Null is IsValid() if
   * false.
   *
   * @returns A numerical representation of the current DataType
   */
  double ControlMeasureLogData::GetNumericalValue() const {
    return p_numericalValue;
  }


  /**
   * Get the data type associated with this log data. The return value is
   *   InvalidNumericLogDataType is no value has been set..
   *
   * @returns A numerical representation of the current DataType
   */
  ControlMeasureLogData::NumericLogDataType
      ControlMeasureLogData::GetDataType() const {
    return p_dataType;
  }


  /**
   * Get the data type associated with this log data. The return value is
   *   an invalid variant type if the value is not set.
   */
  QVariant ControlMeasureLogData::GetValue() const {
    return QVariant(p_numericalValue);
  }


  /**
   * This tests if the log data is complete and valid.
   *
   * @return True if type and value are known, false otherwise
   */
  bool ControlMeasureLogData::IsValid() const {
    return (p_numericalValue != Null) &&
           (p_dataType != InvalidNumericLogDataType);
  }


  /**
   * This converts the log data to a PvlKeyword. These should be understandable
   * by the constructor.
   *
   * @return A PVL representation of this log data
   */
  PvlKeyword ControlMeasureLogData::ToKeyword() const {
    if(IsValid())
      return PvlKeyword(DataTypeToName(p_dataType), toString(p_numericalValue));
    else
      return PvlKeyword();
  }


  /**
   * This converts the log data to a protocol buffer object. This should be
   *   understandable by the constructor that takes a protocol buffer object.
   *
   * @return A protocol buffer representation of this log data
   */
  ControlPointFileEntryV0002_Measure_MeasureLogData
      ControlMeasureLogData::ToProtocolBuffer() const {
    if(!IsValid()) {
      IString msg = "Cannot write an invalid log data entry to binary format";
      throw IException(IException::Programmer, msg, _FILEINFO_);
    }

    ControlPointFileEntryV0002_Measure_MeasureLogData protoBufDataEntry;

    protoBufDataEntry.set_doubledatatype(p_dataType);
    protoBufDataEntry.set_doubledatavalue(p_numericalValue);

    return protoBufDataEntry;
  }


  /**
   * This converts a string to a log data type and is useful for converting Pvl
   * keywords to Numeric Log Data Type.
   *
   * @param name The string to convert to data type
   * @return The data type converted from a string
   */
  ControlMeasureLogData::NumericLogDataType ControlMeasureLogData::NameToDataType(
      QString name) const {
    for (int i = InvalidNumericLogDataType + 1;
         i < MaximumNumericLogDataType; i++) {
      try {
        QString thisTypeName = DataTypeToName((NumericLogDataType) i);

        if (name == thisTypeName) {
          return (NumericLogDataType) i;
        }
      }
      catch (IException &) {
      }
    }

    return InvalidNumericLogDataType;
  }


  /**
   * This converts the log data type to a string and is used internally for
   * convertions to and from Pvl. This is also useful for GUI programs that
   * need to display log information.
   *
   * @param type The data type to convert to a string
   */
  QString ControlMeasureLogData::DataTypeToName(NumericLogDataType type) const {
    switch(type) {
      case InvalidNumericLogDataType: {
          IString msg = "Cannot convert an invalid data type to a string";
          throw IException(IException::Programmer, msg, _FILEINFO_);
        }

      case Obsolete_Eccentricity:
        return "Obsolete_Eccentricity";

      case GoodnessOfFit:
        return "GoodnessOfFit";

      case MinimumPixelZScore:
        return "MinimumPixelZScore";

      case MaximumPixelZScore:
        return "MaximumPixelZScore";

      case PixelShift:
        return "PixelShift";

      case WholePixelCorrelation:
        return "WholePixelCorrelation";

      case SubPixelCorrelation:
        return "SubPixelCorrelation";

      case Obsolete_AverageResidual:
        return "Obsolete_AverageResidual";
    }

    QString msg = "Unknown data type [" + toString(type) + "]";
    throw IException(IException::Programmer, msg, _FILEINFO_);
  }
}
