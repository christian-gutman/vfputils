#include "vfp_encoding.h" 
 
// Exportada a FoxPro: =StrToUtf8(cText)
void CORE_CALL Fox_StrToUtf8(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1) {
        SafeRetValString("");
        return;
    }

    int len = parm->p[0].val.ev_length;
    if (len <= 0) {
        SafeRetValString("");
        return;
    }
    char *input = GetParamString(parm, 0, &len);
    if (!input) {
        SafeRetValString("");
        return;
    }
    int outLen = 0;
    char* result = StrAutoToUtf8(input, len, &outLen);
    if (!result) {
        SafeRetValString("");
        return;
    }

    SafeRetValString(result);
    free(result);
}

// Exportada a FoxPro: =StrToAnsi(cText)
void CORE_CALL Fox_StrToAnsi(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1) {
        SafeRetValString("");
        return;
    }

    int len = parm->p[0].val.ev_length;
    if (len <= 0) {
        SafeRetValString("");
        return;
    }

    char *input = GetParamString(parm, 0, &len);
    if (!input) {
        SafeRetValString("");
        return;
    } 

    int outLen = 0;
    char* result = StrAutoToAnsi(input, len, &outLen);
    if (!result) {
        SafeRetValString("");
        return;
    }

    SafeRetValString(result);
    free(result);
}
