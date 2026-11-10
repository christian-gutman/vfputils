#include "vfp_json.h"

static FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},

    // ------------------------------------------------------------------
    // JSON (vfp_json.c) - familia principal: reciben (cJson, cPath)
    // ------------------------------------------------------------------

    {"JSONGETSTRING", (FPFI)Fox_JsonGetString, 2, "CC"},           // ? JSONGETSTRING(lcJson, "nombre")          && "Juan Pérez"
    {"JSONGETDOUBLE", (FPFI)Fox_JsonGetDouble, 2, "CC"},           // ? JSONGETDOUBLE(lcJson, "precio")          && 199.99
    {"JSONGETINT", (FPFI)Fox_JsonGetInt, 2, "CC"},                 // ? JSONGETINT(lcJson, "cantidad")           && 3
    {"JSONGETINT64", (FPFI)Fox_JsonGetInt64, 2, "CC"},             // ? JSONGETINT64(lcJson, "id")               && "12345678901234"
    {"JSONGETBOOL", (FPFI)Fox_JsonGetBool, 2, "CC"},               // ? JSONGETBOOL(lcJson, "activo")            && .T.
    {"JSONHASVALUE", (FPFI)Fox_JsonHasValue, 2, "CC"},             // ? JSONHASVALUE(lcJson, "envio.ciudad")     && .T.
    {"JSONARRAYCOUNT", (FPFI)Fox_JsonArrayCount, 2, "CC"},         // ? JSONARRAYCOUNT(lcJson, "tags")           && 2
    {"JSONGETTYPE", (FPFI)Fox_JsonGetType, 2, "CC"},               // ? JSONGETTYPE(lcJson, "tags")              && "array"
    {"JSONEXTRACTSUBNODE", (FPFI)Fox_JsonExtractSubNode, 2, "CC"}, // lcSub = JSONEXTRACTSUBNODE(lcJson, "envio")
    {"JSONGETANY", (FPFI)Fox_JsonGetAny, 2, "CC"},                 // uVal = JSONGETANY(lcJson, "precio")  && VARTYPE(uVal) = "N"

};

FoxTable _FoxTable = {(FoxTable *)0, sizeof(myFoxInfo) / sizeof(FoxInfo), myFoxInfo};
