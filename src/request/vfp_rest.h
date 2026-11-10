#ifndef VFP_REST_H
#define VFP_REST_H
 

#include "vfp_request.h" 

#ifdef __cplusplus
extern "C"
{
#endif
    void CORE_CALL Fox_WRestRequest(ParamBlk *parm);

    void CORE_CALL Fox_WRestPut(ParamBlk *parm);
    void CORE_CALL Fox_WRestPatch(ParamBlk *parm);
    void CORE_CALL Fox_WRestPost(ParamBlk *parm);
    void CORE_CALL Fox_WRestDelete(ParamBlk *parm);

    void CORE_CALL Fox_WRestGet(ParamBlk *parm);

    void CORE_CALL Fox_WRestFormPost(ParamBlk *parm);
    void CORE_CALL Fox_WRestFormPut(ParamBlk *parm);
    void CORE_CALL Fox_WRestFormPatch(ParamBlk *parm);

    void CORE_CALL Fox_WRestMultipartPost(ParamBlk *parm);

   

#ifdef __cplusplus
}
#endif

#endif // VFP_REST_H