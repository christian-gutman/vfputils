#include "fox_table.h"

static FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},
 
    // ------------------------------------------------------------------
    // ENCODING - encoding utils (vfp_encodig.c)
    // ------------------------------------------------------------------

    {"STRTOUTF8", (FPFI)Fox_StrToUtf8, 1, "C"},                    // ? STRTOUTF8("Café")
    {"STRTOANSI", (FPFI)Fox_StrToAnsi, 1, "C"},                    // ? STRTOANSI(lcTextoUtf8)
};

FoxTable _FoxTable = {(FoxTable *)0, sizeof(myFoxInfo) / sizeof(FoxInfo), myFoxInfo};
