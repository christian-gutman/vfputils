#include "vfp_json.h"  

void CORE_CALL Fox_JsonGetString(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    char *result = JsonGetString(json, path); // siempre alocado, nunca NULL
    SafeRetValString(result);

    free(result);
    if (json) free(json);
    if (path) free(path);
}

void CORE_CALL Fox_JsonGetDouble(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    double result = JsonGetDouble(json, path);
    SafeRetValDouble(result);

    if (json) free(json);
    if (path) free(path);
}

void CORE_CALL Fox_JsonGetInt64(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    char *result = JsonGetInt64(json, path); // puede ser NULL si malloc falló
    SafeRetValString(result ? result : "0");

    if (result) free(result);
    if (json) free(json);
    if (path) free(path);
}

void CORE_CALL Fox_JsonGetInt(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    long result = JsonGetInt(json, path);
    SafeRetValInt(result);

    if (json) free(json);
    if (path) free(path);
}

void CORE_CALL Fox_JsonGetBool(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    int result = JsonGetBool(json, path);
    SafeRetValLogical(result);

    if (json) free(json);
    if (path) free(path);
}

void CORE_CALL Fox_JsonHasValue(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    int result = JsonHasValue(json, path);
    SafeRetValLogical(result);

    if (json) free(json);
    if (path) free(path);
}

void CORE_CALL Fox_JsonArrayCount(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    int result = JsonArrayCount(json, path);
    SafeRetValInt(result);

    if (json) free(json);
    if (path) free(path);
}

void CORE_CALL Fox_JsonGetType(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    const char *result = JsonGetType(json, path); // literal estático, NO liberar
    SafeRetValString(result);

    if (json) free(json);
    if (path) free(path);
}

void CORE_CALL Fox_JsonExtractSubNode(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    char *result = JsonExtractSubNode(json, path); // siempre alocado
    SafeRetValString(result);

    free(result);
    if (json) free(json);
    if (path) free(path);
}

// JsonGetAny -> traduce DataVariant al tipo VFP-nativo más apropiado.
void CORE_CALL Fox_JsonGetAny(ParamBlk *parm)
{
    char *json = SafeGetString(&(parm->p[0].val));
    char *path = SafeGetString(&(parm->p[1].val));

    DataVariant v = JsonGetAny(json, path);

    switch (v.type)
    {
        case DATA_TYPE_CHARACTER: SafeRetValString(v.value.cVal); break;
        case DATA_TYPE_INTEGER:   SafeRetValInt(v.value.iVal);    break;
        case DATA_TYPE_DOUBLE:    SafeRetValDouble(v.value.dVal); break;
        case DATA_TYPE_LOGICAL:   SafeRetValLogical(v.value.lVal);break;
        default:                  SafeRetValString("");           break;
    }
 
    JsonVariantFree(&v); // libera v.value.cVal solo si corresponde
    if (json) free(json);
    if (path) free(path);
}