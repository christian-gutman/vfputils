#ifndef VFP_JSON_H
#define VFP_JSON_H

// ============================================================================
// vfp_json.h
// Wrappers Fox_Json* que exponen core_json.h a Visual FoxPro. Sin lógica de
// parseo/navegación propia -- toda vive en core_json.c. Acá solo se traducen
// parámetros VFP (ParamBlk) hacia/desde los tipos de core_json.h.
//
// Requiere:
//   - vfp_types.h  (Value, ParamBlk, SafeGetString, SafeRetVal*, etc.)
//   - core_json.h  (JsonGetString, JsonGetDouble, DataVariant, etc.)
// ============================================================================


 
#include "vfp_lib.h"
#include "vfp_types.h"
#include "core_encoding.h"
#include "core_string.h"
#include "core_json.h"


#ifdef __cplusplus
extern "C"
{
#endif

    // =JsonGetString(cJson, cPath)
    void CORE_CALL Fox_JsonGetString(ParamBlk *parm);

    // =JsonGetDouble(cJson, cPath)
    void CORE_CALL Fox_JsonGetDouble(ParamBlk *parm);

    // =JsonGetInt64(cJson, cPath)   -> devuelto como Character (preserva precisión)
    void CORE_CALL Fox_JsonGetInt64(ParamBlk *parm);

    // =JsonGetInt(cJson, cPath)
    void CORE_CALL Fox_JsonGetInt(ParamBlk *parm);

    // =JsonGetBool(cJson, cPath)
    void CORE_CALL Fox_JsonGetBool(ParamBlk *parm);

    // =JsonHasValue(cJson, cPath)
    void CORE_CALL Fox_JsonHasValue(ParamBlk *parm);

    // =JsonArrayCount(cJson, cPath)
    void CORE_CALL Fox_JsonArrayCount(ParamBlk *parm);

    // =JsonGetType(cJson, cPath)  -> "string"|"number"|"object"|"array"|"bool"|"null"|"missing"
    void CORE_CALL Fox_JsonGetType(ParamBlk *parm);

    // =JsonExtractSubNode(cJson, cPath)  -> sub-árbol serializado como texto JSON
    void CORE_CALL Fox_JsonExtractSubNode(ParamBlk *parm);

    // =JsonGetAny(cJson, cPath)  -> tipo VFP-nativo más apropiado (C/N/I/L)
    void CORE_CALL Fox_JsonGetAny(ParamBlk *parm);

#ifdef __cplusplus
}
#endif

#endif // VFP_JSON_H
