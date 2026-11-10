#ifndef VFP_ENCODING_H
#define VFP_ENCODING_H

#include "vfp_lib.h"
#include "vfp_types.h"
#include "core_encoding.h" 

#ifdef __cplusplus
extern "C"
{
#endif

    void CORE_CALL Fox_StrToUtf8(ParamBlk *parm);
    void CORE_CALL Fox_StrToAnsi(ParamBlk *parm);
    
#ifdef __cplusplus
}
#endif

#endif // VFP_ENCODING_H
