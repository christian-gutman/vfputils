#ifndef VFP_REQ_FILE_H
#define VFP_REQ_FILE_H

#include "core_req_file.h"

#include "vfp_request.h"

#ifdef __cplusplus
extern "C"
{
#endif

void CORE_CALL Fox_WDownloadToFile(ParamBlk *parm);
void CORE_CALL Fox_WRequestToFile(ParamBlk *parm);
void CORE_CALL Fox_WDownload(ParamBlk *parm);

#ifdef __cplusplus
}
#endif

#endif // VFP_REQ_FILE_H
