/**
 * @file
 * $Revision: 1.4 $
 * $Date: 2008/08/15 22:03:32 $
 *
 *   Unless noted otherwise, the portions of Isis written by the USGS are
 *   public domain. See individual third-party library and package descriptions
 *   for intellectual property information, user agreements, and related
 *   information.
 *
 *   Although Isis has been used by the USGS, no warranty, expressed or
 *   implied, is made by the USGS as to the accuracy and functioning of such
 *   software and related material nor shall the fact of distribution
 *   constitute any such warranty, and no responsibility is assumed by the
 *   USGS in connection therewith.
 *
 *   For additional information, launch
 *   $ISISROOT/doc//documents/Disclaimers/Disclaimers.html
 *   in a browser or see the Privacy &amp; Disclaimers page on the Isis website,
 *   http://isis.astrogeology.usgs.gov, and the USGS privacy and disclaimers on
 *   http://www.usgs.gov/privacy.html.
 */
#include "Histogram.h"

#include <string>
#include <iostream>

#include "Brick.h"
#include "Message.h"
#include "LineManager.h"

using namespace std;
namespace Isis {

  /**
   * Constructs a histogram object. Only data between the minimum and maximum
   * will be binned, and the bin range will be from the minimum to the maximum.
   *
   * @param minimum Minimum value for binning the data into the histogram.
   * @param maximum Maximum value for binning the data into the histogram.
   * @param nbins The number of bins to use
   */
  Histogram::Histogram(double minimum, double maximum, int nbins) {
    SetValidRange(minimum, maximum);
    SetBinRange(minimum, maximum);
    SetBins(nbins);
  }


  /**
   * Constructs a histogram object using a cube. This constructor computes
   *   the minimum, maximum for the binning range and number of bins
   *   automatically. All statistics will still be collected, though data at
   *   either end of the histogram will be put into one bin in order to attempt to
   *   achieve better histogram statistics.
   *
   * TODO: progress needs to be a bool.
   *
   * @param cube  The cube to used to determine min/max and bins
   * @param statsBand  The band number the histogram will be collected from
   * @param progress  The Progress object to be used to output the percent
   *                  processed information
   * @param startSample  The sample to start reading cube data from
   * @param startLine  The line to start reading cube data from
   * @param endSample  The sample to stop reading cube data at (Null for nsamps)
   * @param endLine  The line to stop reading cube data at (Null for nlines)
   * @param bins The number of histogram bins to create (0 for automatic)
   * @param addCubeData True to fill the histogram with data in addition to
   *                    initializing the binning ranges.
   */
  Histogram::Histogram(Cube &cube, int statsBand, Progress *progress,
      double startSample, double startLine,
      double endSample, double endLine,
      int bins, bool addCubeData) {
    InitializeFromCube(cube, statsBand, progress, bins, startSample, startLine,
                       endSample, endLine);

    if (addCubeData) {
      Brick cubeDataBrick(endSample - startSample + 1,
                          1, 1, cube.getPixelType());

      // if band == 0, then we're gathering data for all bands.
      int startBand = statsBand;
      int endBand = statsBand;

      if (statsBand == 0) {
        startBand = 1;
        endBand = cube.getBandCount();
      }

      if (progress != NULL) {
        progress->SetText("Gathering histogram");
        progress->SetMaximumSteps(
          (endLine - startLine + 1) * (endBand - startBand + 1));
        progress->CheckStatus();
      }

      for (int band = startBand; band <= endBand; band++) {
        for (int line = startLine; line <= endLine; line++) {
          cubeDataBrick.SetBasePosition(startSample, line, band);
          cube.read(cubeDataBrick);
          AddData(cubeDataBrick.DoubleBuffer(), cubeDataBrick.size());
          if (progress != NULL) {
            progress->CheckStatus();
          }
        }
      }
    }
  }


  void Histogram::InitializeFromCube(Cube &cube, int statsBand,
      Progress *progress, int nbins, double startSample, double startLine,
      double endSample, double endLine) {
    // Make sure band is valid, 0 is valid (means all bands)
    if ((statsBand < 0) || (statsBand > cube.getBandCount())) {
      string msg = "Cannot gather histogram for band [" + iString(statsBand) +
          "]";
      throw iException::Message(iException::Programmer, msg, _FILEINFO_);
    }

    // We need to find the min/max DN value for our histogram bins to be the
    //   correct size.
    double minDnValue = Null;
    double maxDnValue = Null;

    if (cube.getPixelType() == UnsignedByte) {
      // If we can discretely store every data point, then we can use the
      //   possible extent of the data range as our min/max dn values.
      if (nbins == 0) {
        minDnValue = 0.0 * cube.getMultiplier() + cube.getBase();
        maxDnValue = 255.0 * cube.getMultiplier() + cube.getBase();
        nbins = 256;
      }
    }
    else if (cube.getPixelType() == SignedWord) {
      if (nbins == 0) {
        minDnValue = -32768.0 * cube.getMultiplier() + cube.getBase();
        maxDnValue = 32767.0 * cube.getMultiplier() + cube.getBase();
        nbins = 65536;
      }
    }
    else if (cube.getPixelType() == Real) {
      // We can't account for all the possibilities of a double inside of any
      //   data range, so don't guess min/max DN values.
      if (nbins == 0) {
        nbins = 65536;
      }
    }
    else {
      iString msg = "Unsupported pixel type";
      throw iException::Message(iException::Programmer, msg, _FILEINFO_);
    }

    if (startSample == Null)
      startSample = 1.0;

    if (endSample == Null)
      endSample = cube.getSampleCount();

    if (startLine == Null)
      startLine = 1.0;

    if (endLine == Null)
      endLine = cube.getLineCount();

    // If we still need our min/max DN values, find them.
    if (minDnValue == Null || maxDnValue == Null) {

      Brick cubeDataBrick(endSample - startSample + 1,
                          1, 1, cube.getPixelType());
      Statistics stats;

      // if band == 0, then we're gathering stats for all bands. I'm really
      //   not sure that this is correct, a good idea or called from anywhere...
      //   but I don't have time to track down the use case.
      int startBand = statsBand;
      int endBand = statsBand;

      if (statsBand == 0) {
        startBand = 1;
        endBand = cube.getBandCount();
      }

      if (progress != NULL) {
        progress->SetText("Computing min/max for histogram");
        progress->SetMaximumSteps(
          (endLine - startLine + 1) * (endBand - startBand + 1));
        progress->CheckStatus();
      }

      for (int band = startBand; band <= endBand; band++) {
        for (int line = startLine; line <= endLine; line++) {
          cubeDataBrick.SetBasePosition(startSample, line, band);
          cube.read(cubeDataBrick);
          stats.AddData(cubeDataBrick.DoubleBuffer(), cubeDataBrick.size());
          if (progress != NULL) {
            progress->CheckStatus();
          }
        }
      }

      if (stats.ValidPixels() == 0) {
        minDnValue = 0.0;
        maxDnValue = 1.0;
      }
      else {
        minDnValue = stats.Minimum();
        maxDnValue = stats.Maximum();
      }
    }

    // Set the bins and range
    SetBinRange(minDnValue, maxDnValue);
    SetBins(nbins);
  }


  //! Destructs a histogram object.
  Histogram::~Histogram() {
  }

  void Histogram::SetBinRange(double binStart, double binEnd) {
    if (binEnd < binStart) {
      string msg = "The binning range start [" + iString(binStart) +
                   " must be less than the end [" + iString(binEnd) + ".";
      throw iException::Message(iException::Programmer, msg, _FILEINFO_);
    }

    p_binRangeStart = binStart;
    p_binRangeEnd = binEnd;
  }


  //! Resets histogram counters to zero.
  void Histogram::Reset() {
    Statistics::Reset();
    for (int i = 0; i < (int)p_bins.size(); i++) {
      p_bins[i] = 0;
    }
  }


  //! Change the number of bins in the histogram and reset counters
  void Histogram::SetBins(const int nbins) {
    p_bins.resize(nbins);
    Histogram::Reset();
  }

  /**
   * Add an array of doubles to the histogram counters. This method can be
   * invoked multiple times. For example, once for each line in a cube, before
   * obtaining statistics and histogram information.
   *
   * @param data Pointer to array of double to add.
   * @param count Number of doubles to process.
   */
  void Histogram::AddData(const double *data,
                          const unsigned int count) {
    Statistics::AddData(data, count);

    int nbins = p_bins.size();
    int index;
    for (unsigned int i = 0; i < count; i++) {
      if (IsValidPixel(data[i]) && InRange(data[i])) {
        if (BinRangeStart() == BinRangeEnd()) {
          index = 0;
        }
        else {
          index = (int) floor((double)(nbins - 1) / (BinRangeEnd() - BinRangeStart()) *
                              (data[i] - BinRangeStart()) + 0.5);
        }
        if (index < 0) index = 0;
        if (index >= nbins) index = nbins - 1;
        p_bins[index] += 1;
      }
    }
  }

  /**
   * Remove an array of doubles from the histogram counters. Note that this
   * invalidates the absolute minimum and maximum. They will no longer be
   * useable.
   * @see Stats
   *
   * @param data Pointer to array of doubles to remove.
   * @param count number of doubles to process.
   */
  void Histogram::RemoveData(const double *data,
                             const unsigned int count) {
    Statistics::RemoveData(data, count);

    int nbins = p_bins.size();
    int index;
    for (unsigned int i = 0; i < count; i++) {
      if (IsValidPixel(data[i])) {
        if (BinRangeStart() == BinRangeEnd()) {
          index = 0;
        }
        else {
          index = (int) floor((double)(nbins - 1) / (BinRangeEnd() - BinRangeStart()) *
                              (data[i] - BinRangeStart()) + 0.5);
        }
        if (index < 0) index = 0;
        if (index >= nbins) index = nbins - 1;
        p_bins[index] -= 1;
      }
    }
  }

  /**
   * Returns the median.
   *
   * @returns The median
   */
  double Histogram::Median() const {
    return Percent(50.0);
  }

  /**
   * Returns the mode.
   *
   * @returns The mode
   */
  double Histogram::Mode() const {
    int mode = 0;
    for (int i = 0; i < (int)p_bins.size(); i++) {
      if (p_bins[i] > p_bins[mode]) mode = i;
    }

    if (p_bins[mode] < 1) return NULL8;

    return BinMiddle(mode);
  }


  /**
   * Computes and returns the value at X percent of the histogram.  For example,
   * Percent(50.0) is equivalent to the computing the median. While Percent(0.5)
   * and Percent(99.5) would obtain a minimum and maximum for the data that
   * could be used for a good contrast stretch.
   *
   * @param percent X percent of the histogram to compute.
   *
   * @returns The value at X percent of the histogram.
   */
  double Histogram::Percent(double percent) const {
    if ((percent < 0.0) || (percent > 100.0)) {
      string m = "Argument percent outside of the range 0 to 100 in";
      m += " [Histogram::Percent]";
      throw iException::Message(iException::Programmer, m, _FILEINFO_);
    }

    if (ValidPixels() < 1) return NULL8;

    BigInt currentPixels = 0;
    double currentPercent;

    for (int i = 0; i < (int)p_bins.size(); i++) {
      currentPixels += p_bins[i];
      currentPercent = (double) currentPixels / (double) ValidPixels() * 100.0;
      if (currentPercent >= percent) {
        return BinMiddle(i);
      }
    }

    return BinMiddle((int)p_bins.size() - 1);
  }


  /**
   * Computes and returns the skew. If there are no valid pixels then NULL8 is
   * returned. Recognize that because of the binning which occurs, in order to
   * generate the histogram, the skew may not be precise but will be very close.
   *
   * @return The skew.
   */
  double Histogram::Skew() const {
    if (ValidPixels() < 1) return NULL8;
    double sdev = StandardDeviation();
    if (sdev == 0.0) return 0.0;
    return 3.0 * (Average() - Median()) / sdev;
  }


  /**
   * Returns the count at a bin position in the histogram.
   *
   * @param index Index of the desired bin 0 to Bins()-1.
   *
   * @return The count at a bin position in the histogram.
   */
  BigInt Histogram::BinCount(const int index) const {
    if ((index < 0) || (index >= (int)p_bins.size())) {
      string message = Message::ArraySubscriptNotInRange(index);
      throw iException::Message(iException::Programmer, message, _FILEINFO_);
    }

    return p_bins[index];
  }


  /**
   * Returns the left edge and right edge values of a bin. That is the range of
   * data the bin covers.
   *
   * @throws iException The programmer has passed in an index outside of 0
   * to Bins()-1.
   *
   * @param index Index of the desired bin 0 to Bins()-1.
   * @param low The value at the left edge of the requested bin.
   * @param high The value at the right edge of the requested bin.
   */
  void Histogram::BinRange(const int index,
                           double &low, double &high) const {
    if ((index < 0) || (index >= (int)p_bins.size())) {
      string message = Message::ArraySubscriptNotInRange(index);
      throw iException::Message(iException::Programmer, message, _FILEINFO_);
    }

    double binSize = (BinRangeEnd() - BinRangeStart()) / (double)(p_bins.size() - 1);
    low = BinRangeStart() - binSize / 2.0 + binSize * (double) index;
    high = low + binSize;
  }


  /**
   * Returns the value represented by a bin. This is not the count, but the
   * actual data value at the middle of the bin.
   *
   * @param index Index of the desired bin 0 to Bins()-1.
   *
   * @returns The middle value of the bin.
   */
  double Histogram::BinMiddle(const int index) const {
    if ((index < 0) || (index >= (int)p_bins.size())) {
      string message = Message::ArraySubscriptNotInRange(index);
      throw iException::Message(iException::Programmer, message, _FILEINFO_);
    }

    double low, high;
    BinRange(index, low, high);
    return (low + high) / 2.0;
  }


  /**
   * Returns the size of an individual bin. Essentially, the difference of the
   * high and low edge values (BinRange) of a bin.  This value is constant for
   * all bins.
   *
   * @return The size of the individual bin.
   */
  double Histogram::BinSize() const {
    double low, high;
    BinRange(0, low, high);
    return high - low;
  }


  /**
   * Returns the number of bins in the histogram.
   *
   * @return The number of bins in the histogram.
   */
  int Histogram::Bins() const {
    return (int)p_bins.size();
  }


  /**
   * Returns the highest bin count.
   *
   * @return The highest bin count.
   */
  BigInt Histogram::MaxBinCount() const {

    BigInt maxBinCount = 0;
    for (int i = 0; i < (int)p_bins.size(); i++) {
      if (p_bins[i] > maxBinCount) maxBinCount = p_bins[i];
    }

    return maxBinCount;
  }
}
