#include "fox_table.h"

FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},
    // ------------------------------------------------------------------
    // WExec (vfp_request.c)
    // ------------------------------------------------------------------
    {"WConnect", (FPFI)Fox_WConnect, 4, "CCIC"},
    {"WDisconnect", (FPFI)Fox_WDisconnect, 1, "?"},
    {"WRequest", (FPFI)Fox_WRequest, 15, "CCC????????????"},
    {"WCloseRequest", (FPFI)Fox_WCloseRequest, 1, "?"},
    // ------------------------------------------------------------------
    // WExec (vfp_req_file.c)
    // ------------------------------------------------------------------
    {"WDownloadToFile", (FPFI)Fox_WDownloadToFile, 11, "C,C,C,I,L,L,C,C,C,C,R"},
    {"WRequestToFile", (FPFI)Fox_WRequestToFile, 13, "C,C,C,I,L,L,C,C,C,C,C,C,R"},
    {"WDownload", (FPFI)Fox_WDownload, 10, "C,C,I,L,L,C,C,C,C,R"},

      // ------------------------------------------------------------------
    // WExec (vfp_rest.c)
    // ------------------------------------------------------------------

    {"WRestRequest", (FPFI)Fox_WRestRequest, 10, "C,C,C,C,C,C,C,C,R,R"},
    {"WRestGet", (FPFI)Fox_WRestGet, 5, "C,C,C,R,R"},
    {"WRestPost", (FPFI)Fox_WRestPost, 6, "C,C,C,C,R,R"},
    {"WRestPut", (FPFI)Fox_WRestPut, 6, "C,C,C,C,R,R"},
    {"WRestPatch", (FPFI)Fox_WRestPatch, 6, "C,C,C,C,R,R"},
    {"WRestDelete", (FPFI)Fox_WRestDelete, 5, "C,C,C,R,R"},

    // Formularios Web Tradicionales
    {"WRestFormPost", (FPFI)Fox_WRestFormPost, 6, "C,C,C,C,R,R"},
    {"WRestFormPut", (FPFI)Fox_WRestFormPut, 6, "C,C,C,C,R,R"},
    {"WRestFormPatch", (FPFI)Fox_WRestFormPatch, 6, "C,C,C,C,R,R"},

    // Nuevo Multipart Genérico de Archivos
    {"WRestMultipartPost", (FPFI)Fox_WRestMultipartPost, 7, "C,C,C,C,C,R,R"},

};

FoxTable _FoxTable = {
    (FoxTable *)0,
    sizeof(myFoxInfo) / sizeof(FoxInfo),
    myFoxInfo};