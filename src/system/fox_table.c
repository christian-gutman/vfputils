#include "vfp_system.h"
 
FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},
     {"SOLASTERROR", (FPFI)Fox_SoLastError, 2, "RR"}
};

FoxTable _FoxTable = {
    (FoxTable *)0,
    sizeof(myFoxInfo) / sizeof(FoxInfo),
    myFoxInfo}; 