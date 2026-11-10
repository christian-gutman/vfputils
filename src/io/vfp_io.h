#ifndef VFP_IO_H
#define VFP_IO_H

#include "vfp_lib.h"
#include "vfp_types.h"

#include "core_io.h"

//void CORE_CALL Fox_ReadFileBytes(ParamBlk *parm); 
//void CORE_CALL Fox_WriteFileBytes(ParamBlk *parm);

// VFP: = WriteLog(cPath, cMessage)
void CORE_CALL Fox_WriteTextLogWithDate(ParamBlk *parm);

// VFP: = WriteIniStr(cPathIni, cSection, cKey, cValue)
void CORE_CALL Fox_WriteIniString(ParamBlk *parm);

// VFP: cValue = ReadIniStr(cPathIni, cSection, cKey, cDefault)
void CORE_CALL Fox_ReadIniString(ParamBlk *parm);

// VFP: = WriteIniInt(cPathIni, cSection, cKey, nValue)
void CORE_CALL Fox_WriteIniInt(ParamBlk *parm);

// VFP: nValue = ReadIniInt(cPathIni, cSection, cKey, nDefault)
void CORE_CALL Fox_ReadIniInt(ParamBlk *parm);

// VFP: = DeleteIniKey(cPathIni, cSection, cKey)
void CORE_CALL Fox_DeleteIniKey(ParamBlk *parm);

// VFP: = DeleteIniSection(cPathIni, cSection)
void CORE_CALL Fox_DeleteIniSection(ParamBlk *parm);

void CORE_CALL Fox_FreeBufferC(ParamBlk *parm);
 
// VFP: cRutaCompleta = GETAPPDATAPATH(cAppName, cFileName)
void CORE_CALL Fox_GetPathInAppData(ParamBlk *parm);

// VFP: cRuta = GETEXEPATH(cFileName)
void CORE_CALL Fox_GetPathInExeFolder(ParamBlk *parm);

// VFP: cRuta = GETLIBPATH(cFileName)
void CORE_CALL Fox_GetPathInLibraryFolder(ParamBlk *parm);

#endif // VFP_IO_H