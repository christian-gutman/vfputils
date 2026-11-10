#ifndef VFP_HTML_H
#define VFP_HTML_H

 
#include "vfp_lib.h"
#include "vfp_types.h"

#include "core_html.h"
 

#ifdef __cplusplus
extern "C"
{
#endif

    void CORE_CALL Fox_EncodeURIComponent(ParamBlk *parm);
    void CORE_CALL Fox_DecodeURIComponent(ParamBlk *parm);
    void CORE_CALL Fox_HtmlEntities(ParamBlk *parm);
    void CORE_CALL Fox_Utf8ToAnsi(ParamBlk *parm);
    void CORE_CALL Fox_AnsiToUtf8(ParamBlk *parm);


#ifdef __cplusplus
}
#endif

#endif // VFP_HTML_H