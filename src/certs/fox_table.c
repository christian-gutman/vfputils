#include "vfp_certs.h"

 
FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},

    // ------------------------------------------------------------------
    // Certs (vfp_certs.c)
    // ------------------------------------------------------------------

    {"CertGetExpiry", (FPFI)Fox_CertGetExpiry, 2, "CC"}, //  lcExpiry = CertGetExpiry(lcCertFile, lcPassword)
    {"CertSignMsg",   (FPFI)Fox_CertSignMsg,   3, "CCC"}, //  lcSignedB64 = CertSignMsg(lcXmlTRA, lcCertFile, lcPassword)
 
};

FoxTable _FoxTable = {
    (FoxTable *)0,
    sizeof(myFoxInfo) / sizeof(FoxInfo),
    myFoxInfo}; 