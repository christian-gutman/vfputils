#include "fox_table.h"

static FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},

    {"ENCODEURICOMPONENT", (FPFI)Fox_EncodeURIComponent, 1, "C"},
    {"DECODEURICOMPONENT", (FPFI)Fox_DecodeURIComponent, 1, "C"},
    {"HTMLENTITIES",(FPFI) Fox_HtmlEntities, 1, "C"},

    {"UTF8TOANSI", (FPFI)Fox_Utf8ToAnsi, 1, "C"},
    {"ANSITOUTF8", (FPFI)Fox_AnsiToUtf8, 1, "C"},

};

FoxTable _FoxTable = {(FoxTable *)0, sizeof(myFoxInfo) / sizeof(FoxInfo), myFoxInfo};
