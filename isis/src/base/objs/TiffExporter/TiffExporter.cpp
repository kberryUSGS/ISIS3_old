#include "TiffExporter.h"

#include <QDebug>

#include "Buffer.h"
#include "FileName.h"
#include "IException.h"

using namespace Isis;


namespace Isis {
  /**
   * Construct the TIFF exporter.
   */
  TiffExporter::TiffExporter() : StreamExporter() {
    m_image = NULL;
    m_raster = NULL;

    setExtension("tif");
  }


  /**
   * Destruct the exporter.
   */
  TiffExporter::~TiffExporter() {
    if (m_image) {
      TIFFClose(m_image);
      m_image = NULL;
    }

    delete [] m_raster;
    m_raster = NULL;
  }


  /**
   * Creates the buffer to store a chunk of streamed line data with one or more
   * bands.
   */
  void TiffExporter::createBuffer() {
    PixelType type = getPixelType();
    int mult = (type == Isis::UnsignedByte) ? 1 : 2;
    int size = samples() * bands() * mult;

    try {
      m_raster = new unsigned char[size];
    }
    catch (...) {
      throw IException(IException::Unknown,
          "Could not allocate enough memory", _FILEINFO_);
    }
  }


  /**
   * Open the output file for writing, initialize its fields, then let the base
   * ImageExporter handle the generic black-box writing routine.
   *
   * @param outputName The filename of the output cube
   * @param quality The quality of the output, not used for TIFF
   */
  void TiffExporter::write(FileName outputName, int quality) {
    // Open the output image
    m_image = TIFFOpen(outputName.expanded().c_str(), "w");

    if (m_image == NULL) {
      throw IException(IException::Programmer,
          "Could not open output image", _FILEINFO_);
    }

    TIFFSetField(m_image, TIFFTAG_IMAGEWIDTH, samples());
    TIFFSetField(m_image, TIFFTAG_IMAGELENGTH, lines());
    TIFFSetField(m_image, TIFFTAG_ROWSPERSTRIP, 1);
    TIFFSetField(m_image, TIFFTAG_COMPRESSION, COMPRESSION_DEFLATE);
    TIFFSetField(m_image, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

    TIFFSetField(m_image, TIFFTAG_PHOTOMETRIC,
        bands() == 1 ? PHOTOMETRIC_MINISBLACK : PHOTOMETRIC_RGB);

    PixelType type = getPixelType();
    int bps = (type == Isis::UnsignedByte) ? 8 : 16;
    TIFFSetField(m_image, TIFFTAG_BITSPERSAMPLE, bps);

    TIFFSetField(m_image, TIFFTAG_SAMPLESPERPIXEL, bands());

    ImageExporter::write(outputName, quality);
  }


  /**
   * Set the DN value at the given sample and band, resolved to a single index,
   * of the line buffer.
   *
   * @param s The sample component of the index into the buffer
   * @param b The band component of the index into the buffer
   * @param dn The value to set at the given index
   */
  void TiffExporter::setBuffer(int s, int b, int dn) const {
    PixelType type = getPixelType();
    int index = s * bands() + b;
    
    switch (type) {
      case UnsignedByte:
        m_raster[index] = (unsigned char) dn;
        break;
      case SignedWord:
        ((short int *) m_raster)[index] = (short int) dn;
        break;
      case UnsignedWord:
        ((short unsigned int *) m_raster)[index] = (short unsigned int) dn;
        break;
      default:
        throw IException(IException::Programmer,
            "Invalid pixel type for data [" + IString(type) + "]",
            _FILEINFO_);
    }
  }


  /**
   * Writes a line of buffered data to the output image on disk.
   *
   * @param l The line of the output image
   */
  void TiffExporter::writeLine(int l) const {
    if (!TIFFWriteScanline(m_image, m_raster, l)) {
      throw IException(IException::Programmer,
          "Could not write image", _FILEINFO_);
    }
  }


  /**
   * Returns true if the format is "tiff".
   *
   * @param format Lowercase format abbreviation
   *
   * @return True if "tiff", false otherwise
   */
  bool TiffExporter::canWriteFormat(IString format) {
    return format == "tiff";
  }
};

