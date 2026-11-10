#include "vfp_certs.h"

 
FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},

    {"CertGetExpiry", (FPFI)Fox_CertGetExpiry, 2, "CC"},
    {"CertSignMsg",   (FPFI)Fox_CertSignMsg,   3, "CCC"}
 
};

FoxTable _FoxTable = {
    (FoxTable *)0,
    sizeof(myFoxInfo) / sizeof(FoxInfo),
    myFoxInfo}; 