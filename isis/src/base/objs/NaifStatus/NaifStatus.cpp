/**
 * @file
 * $Revision: 1.2 $
 * $Date: 2009/12/28 20:18:06 $
 *
 *   Unless noted otherwise, the portions of Isis written by the USGS are public
 *   domain. See individual third-party library and package descriptions for
 *   intellectual property information,user agreements, and related information.
 *
 *   Although Isis has been used by the USGS, no warranty, expressed or implied,
 *   is made by the USGS as to the accuracy and functioning of such software
 *   and related material nor shall the fact of distribution constitute any such
 *   warranty, and no responsibility is assumed by the USGS in connection
 *   therewith.
 *
 *   For additional information, launch
 *   $ISISROOT/doc//documents/Disclaimers/Disclaimers.html in a browser or see
 *   the Privacy &amp; Disclaimers page on the Isis website,
 *   http://isis.astrogeology.usgs.gov, and the USGS privacy and disclaimers on
 *   http://www.usgs.gov/privacy.html.
 */
#include "NaifStatus.h"

#include <iostream>

#include <SpiceUsr.h>

#include "IException.h"
#include "IString.h"
#include "Pvl.h"
#include "PvlToPvlTranslationManager.h"

namespace Isis {
  bool NaifStatus::initialized = false;

  /**
   * This method looks for any naif errors that might have occurred. It
   * then compares the error to a list of known naif errors and converts
   * the error into an iException.
   *
   * @param resetNaif True if the NAIF error status should be reset (naif calls valid)
   */
  void NaifStatus::CheckErrors(bool resetNaif) {
    if(!initialized) {
      SpiceChar returnAct[32] = "RETURN";
      SpiceChar printAct[32] = "NONE";
      erract_c("SET", sizeof(returnAct), returnAct);   // Reset action to return
      errprt_c("SET", sizeof(printAct), printAct);     // ... and print nothing
      initialized = true;
    }

    // Do nothing if NAIF didn't fail
    //getmsg_c("", 0, NULL);
    if(!failed_c()) return;

    // This method has been documented with the information provided
    //   from the NAIF documentation at:
    //    naif/cspice61/packages/cspice/doc/html/req/error.html


    // This message is a character string containing a very terse, usually
    // abbreviated, description of the problem. The message is a character
    // string of length not more than 25 characters. It always has the form:
    // SPICE(...)
    // Short error messages used in CSPICE are CONSTANT, since they are
    // intended to be used in code. That is, they don't contain any data which
    // varies with the specific instance of the error they indicate.
    // Because of the brief format of the short error messages, it is practical
    // to use them in a test to determine which type of error has occurred.
    const int SHORT_DESC_LEN = 26;
    SpiceChar naifShort[SHORT_DESC_LEN];
    getmsg_c("SHORT", SHORT_DESC_LEN, naifShort);

    // This message may be up to 1840 characters long. The CSPICE error handling
    // mechanism makes no use of its contents. Its purpose is to provide human-readable
    // information about errors. Long error messages generated by CSPICE routines often
    // contain data relevant to the specific error they describe.
    const int LONG_DESC_LEN = 1841;
    SpiceChar naifLong[LONG_DESC_LEN];
    getmsg_c("LONG", LONG_DESC_LEN, naifLong);

    // Search for known naif errors...
    QString errMsg;

    Pvl error;
    PvlGroup errorDescription("ErrorDescription");
    errorDescription.addKeyword(PvlKeyword("ShortMessage", naifShort));
    errorDescription.addKeyword(PvlKeyword("LongMessage", naifLong));
    error.addGroup(errorDescription);

    PvlToPvlTranslationManager trans(error, "$base/translations/NaifErrors.trn");

    try {
      errMsg = trans.Translate("ShortMessage");
    }
    catch(IException &) {
      errMsg = "An unknown NAIF error has been encountered.";
    }

    try {
      errMsg += " " + trans.Translate("LongMessage");
    }
    catch(IException &) {
    }

    // Now process the error
    if(resetNaif) {
      reset_c();
    }

    errMsg += " The short explanation ";
    errMsg += "provided by NAIF is [" + QString(naifShort) + "]. ";
    errMsg += "The Naif error is [" + QString(naifLong) + "]";

    throw IException(IException::Unknown, errMsg, _FILEINFO_);
  }
}
