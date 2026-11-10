#include "vfp_io.h"
 
FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},
    
    {"WRITELOG", (FPFI)Fox_WriteTextLogWithDate, 2, "C,C"},

    {"WRITEINISTR", (FPFI)Fox_WriteIniString, 4, "C,C,C,C"},
    {"WRITEINIINT", (FPFI)Fox_WriteIniInt, 4, "C,C,C,I"},

    {"READINISTR", (FPFI)Fox_ReadIniString, 4, "C,C,C,C"},
    {"READINIINT", (FPFI)Fox_ReadIniInt, 4, "C,C,C,I"},

    {"DELETEINIKEY", (FPFI)Fox_DeleteIniKey, 3, "C,C,C"},
    {"DELETEINISECTION", (FPFI)Fox_DeleteIniSection, 2, "C,C"},

    // {"READFILEBYTES",     (FPFI)Fox_ReadFileBytesC,       1, "C"},
    /// {"WRITEFILEBYTES",    (FPFI)Fox_WriteFileBytesC,      3, "C,C,I"},
    // {"FREEBUFFER",        (FPFI)Fox_FreeBufferC,          1, "I"},

    {"GETAPPDATAPATH", (FPFI)Fox_GetPathInAppData, 2, "C,C"},
    {"GETEXEPATH", (FPFI)Fox_GetPathInExeFolder, 1, "C"},
    {"GETLIBPATH", (FPFI)Fox_GetPathInLibraryFolder, 1, "C"},

};

FoxTable _FoxTable = {
    (FoxTable *)0,
    sizeof(myFoxInfo) / sizeof(FoxInfo),
    myFoxInfo}; 