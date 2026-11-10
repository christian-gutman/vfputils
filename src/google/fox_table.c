#include "fox_table.h"

static FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},

    // ------------------------------------------------------------------
    // Google (vfp_google_request.c)
    // ------------------------------------------------------------------

    {"WGoogleGeoPos", (FPFI)Fox_WGoogleGeoPos, 8, "CCCCCC??"},
};

FoxTable _FoxTable = {(FoxTable *)0, sizeof(myFoxInfo) / sizeof(FoxInfo), myFoxInfo};
