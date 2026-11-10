#include "vfp_html.h"

void CORE_CALL Fox_EncodeURIComponent(ParamBlk *parm)
{
    Value valParam = SafeGetParam(parm, 0);
    if (valParam.ev_type != 'C' && valParam.ev_type != 'M')
    {
        _Error(9);
        return;
    }
    if (valParam.ev_length <= 0)
    {
        _RetVal(&valParam);
        return;
    }

    int outLen = valParam.ev_length * 3 + 1;
    MHANDLE hOutput = _AllocHand(outLen);
    if (hOutput == 0)
    {
        _Error(182);
        return;
    }

    char *src = (char *)SafeLockHandle(valParam.ev_handle);
    char *target = (char *)SafeLockHandle(hOutput);
    if (!src || !target)
    {
        SafeUnlockHandle(valParam.ev_handle);
        SafeUnlockHandle(hOutput);
        _FreeHand(hOutput);
        _Error(182);
        return;
    }

    int actualLen = encode_uri_component(src, valParam.ev_length, target);
    SafeUnlockHandle(valParam.ev_handle);
    SafeUnlockHandle(hOutput);

//    Value valResult = {'C', actualLen, hOutput, 0};
    Value valResult;
    valResult.ev_type = 'C';
    valResult.ev_length = actualLen;
    valResult.ev_handle = hOutput;
    valResult.ev_width = 0;

    if (parm->p[0].loc.l_type == 'R')
        _Store(&parm->p[0].loc, &valResult);
    _RetVal(&valResult);
}

void CORE_CALL Fox_DecodeURIComponent(ParamBlk *parm)
{
    Value valParam = SafeGetParam(parm, 0);
    if (valParam.ev_type != 'C' && valParam.ev_type != 'M')
    {
        _Error(9);
        return;
    }
    if (valParam.ev_length <= 0)
    {
        _RetVal(&valParam);
        return;
    }

    int outLen = valParam.ev_length + 1;
    MHANDLE hOutput = _AllocHand(outLen);
    if (hOutput == 0)
    {
        _Error(182);
        return;
    }

    char *src = (char *)SafeLockHandle(valParam.ev_handle);
    char *target = (char *)SafeLockHandle(hOutput);
    if (!src || !target)
    {
        SafeUnlockHandle(valParam.ev_handle);
        SafeUnlockHandle(hOutput);
        _FreeHand(hOutput);
        _Error(182);
        return;
    }

    int actualLen = decode_uri_component(src, valParam.ev_length, target);
    SafeUnlockHandle(valParam.ev_handle);
    SafeUnlockHandle(hOutput);

   Value valResult;
    valResult.ev_type = 'C';
    valResult.ev_length = actualLen;
    valResult.ev_handle = hOutput;
    valResult.ev_width = 0;

    if (parm->p[0].loc.l_type == 'R')
        _Store(&parm->p[0].loc, &valResult);
    _RetVal(&valResult);
}

void CORE_CALL Fox_HtmlEntities(ParamBlk *parm)
{
    Value valParam = SafeGetParam(parm, 0);
    if (valParam.ev_type != 'C' && valParam.ev_type != 'M')
    {
        _Error(9);
        return;
    }
    if (valParam.ev_length <= 0)
    {
        _RetVal(&valParam);
        return;
    }

    int outLen = valParam.ev_length * 6 + 1;
    MHANDLE hOutput = _AllocHand(outLen);
    if (hOutput == 0)
    {
        _Error(182);
        return;
    }

    char *src = (char *)SafeLockHandle(valParam.ev_handle);
    char *target = (char *)SafeLockHandle(hOutput);
    if (!src || !target)
    {
        SafeUnlockHandle(valParam.ev_handle);
        SafeUnlockHandle(hOutput);
        _FreeHand(hOutput);
        _Error(182);
        return;
    }

    int actualLen = html_entities(src, valParam.ev_length, target);
    SafeUnlockHandle(valParam.ev_handle);
    SafeUnlockHandle(hOutput);

    Value valResult;
    valResult.ev_type = 'C';
    valResult.ev_length = actualLen;
    valResult.ev_handle = hOutput;
    valResult.ev_width = 0;

    if (parm->p[0].loc.l_type == 'R')
        _Store(&parm->p[0].loc, &valResult);
    _RetVal(&valResult);
} 

static inline __forceinline int fox_utf8_to_ansi(const char *utf8_src, int src_len, char *ansi_target, int max_target_len)
{
    const int code_page = 1252; 
    if (utf8_src == NULL || ansi_target == NULL || src_len <= 0 || max_target_len <= 0)
    {
        return 0;
    }
 
    const unsigned char *u_src = (const unsigned char *)utf8_src;
    if (src_len >= 3 && u_src[0] == 0xEF && u_src[1] == 0xBB && u_src[2] == 0xBF)
    {
        utf8_src += 3;
        src_len -= 3;
    }
 
    if (src_len <= 0)
    {
        return 0;
    }

    int wide_len = MultiByteToWideChar(CP_UTF8, 0, utf8_src, src_len, NULL, 0);
    if (wide_len <= 0)
    {
        return 0;
    }

    MHANDLE h_wide_buf = _AllocHand(wide_len * sizeof(wchar_t));
    if (h_wide_buf == 0)
    {
        return 0;
    }
    wchar_t *wide_buf = (wchar_t *)_HandToPtr(h_wide_buf);

    MultiByteToWideChar(CP_UTF8, 0, utf8_src, src_len, wide_buf, wide_len);

    int bytes_escritos = WideCharToMultiByte(code_page, 0, wide_buf, wide_len, ansi_target, max_target_len, NULL, NULL);

    _FreeHand(h_wide_buf);

    if (bytes_escritos <= 0)
    {
        return 0;
    }

    return bytes_escritos;
}

static inline __forceinline int fox_ansi_to_utf8(const char *ansi_src, int src_len, char *utf8_target, int max_target_len)
{
     const int code_page = 1252; 
    if (ansi_src == NULL || utf8_target == NULL || src_len <= 0 || max_target_len <= 0)
    {
        return 0;
    }

    int wide_len = MultiByteToWideChar(code_page, 0, ansi_src, src_len, NULL, 0);
    if (wide_len <= 0)
    {
        return 0;
    }

    MHANDLE h_wide_buf = _AllocHand(wide_len * sizeof(wchar_t));
    if (h_wide_buf == 0)
    {
        return 0;
    }
    wchar_t *wide_buf = (wchar_t *)_HandToPtr(h_wide_buf);

    MultiByteToWideChar(code_page, 0, ansi_src, src_len, wide_buf, wide_len);

    int bytes_escritos = WideCharToMultiByte(CP_UTF8, 0, wide_buf, wide_len, utf8_target, max_target_len, NULL, NULL);

    _FreeHand(h_wide_buf);

    if (bytes_escritos <= 0)
    {
        return 0;
    }

    return bytes_escritos;
}

void CORE_CALL Fox_Utf8ToAnsi(ParamBlk *parm) {
    Value valParam = SafeGetParam(parm, 0);

    if (valParam.ev_type != 'C' && valParam.ev_type != 'M') {
        _Error(9); // Data type mismatch
        return;
    }

    if (valParam.ev_length <= 0) {
        _RetVal(&valParam);
        return;
    }

    int max_len = valParam.ev_length + 1;
    MHANDLE hOutput = _AllocHand(max_len);
    if (hOutput == 0) {
        _Error(182); // Insufficient memory
        return;
    }

    char *src = (char *)SafeLockHandle(valParam.ev_handle);
    char *target = (char *)SafeLockHandle(hOutput);

    if (!src || !target) {
        SafeUnlockHandle(valParam.ev_handle);
        SafeUnlockHandle(hOutput);
        _FreeHand(hOutput);
        _Error(182);
        return;
    }

    int actual_len = fox_utf8_to_ansi(src, valParam.ev_length, target, max_len - 1);

    target[actual_len] = '\0';

    SafeUnlockHandle(valParam.ev_handle);
    SafeUnlockHandle(hOutput);

    if (actual_len == 0) {
        _FreeHand(hOutput);
        
        // CORRECCIÓN: Inicialización explícita segura para string vacío
        Value valEmpty;
        valEmpty.ev_type = 'C';
        valEmpty.ev_length = 0;
        valEmpty.ev_handle = 0;
        valEmpty.ev_width = 0;
        
        _RetVal(&valEmpty);
        return;
    }

    // CORRECCIÓN: Asignación explícita por miembros para evitar C4244 y el crash de MHANDLE
    Value valResult;
    valResult.ev_type = 'C';
    valResult.ev_length = actual_len;
    valResult.ev_handle = hOutput;
    valResult.ev_width = 0;

    if (parm && parm->pCount > 0 && parm->p[0].loc.l_type == 'R') {
        _Store(&parm->p[0].loc, &valResult);
        
        Value valEmpty;
        valEmpty.ev_type = 'C';
        valEmpty.ev_length = 0;
        valEmpty.ev_handle = 0;
        valEmpty.ev_width = 0;
        
        _RetVal(&valEmpty);
    } else {
        _RetVal(&valResult);
    }
}

void CORE_CALL Fox_AnsiToUtf8(ParamBlk *parm) {
    Value valParam = SafeGetParam(parm, 0);

    if (valParam.ev_type != 'C' && valParam.ev_type != 'M') {
        _Error(9);
        return;
    }

    if (valParam.ev_length <= 0) {
        _RetVal(&valParam);
        return;
    }

    int max_len = (valParam.ev_length * 3) + 1;
    MHANDLE hOutput = _AllocHand(max_len);
    if (hOutput == 0) {
        _Error(182);
        return;
    }

    char *src = (char *)SafeLockHandle(valParam.ev_handle);
    char *target = (char *)SafeLockHandle(hOutput);

    if (!src || !target) {
        SafeUnlockHandle(valParam.ev_handle);
        SafeUnlockHandle(hOutput);
        _FreeHand(hOutput);
        _Error(182);
        return;
    }

    int actual_len = fox_ansi_to_utf8(src, valParam.ev_length, target, max_len - 1);

    target[actual_len] = '\0';

    SafeUnlockHandle(valParam.ev_handle);
    SafeUnlockHandle(hOutput);

    if (actual_len == 0) {
        _FreeHand(hOutput);
        
        Value valEmpty;
        valEmpty.ev_type = 'C';
        valEmpty.ev_length = 0;
        valEmpty.ev_handle = 0;
        valEmpty.ev_width = 0;
        
        _RetVal(&valEmpty);
        return;
    }

    // CORRECCIÓN: Asignación explícita por miembros para evitar C4244 y el crash de MHANDLE
    Value valResult;
    valResult.ev_type = 'C';
    valResult.ev_length = actual_len;
    valResult.ev_handle = hOutput;
    valResult.ev_width = 0;

    if (parm && parm->pCount > 0 && parm->p[0].loc.l_type == 'R') {
        _Store(&parm->p[0].loc, &valResult);
        
        Value valEmpty;
        valEmpty.ev_type = 'C';
        valEmpty.ev_length = 0;
        valEmpty.ev_handle = 0;
        valEmpty.ev_width = 0;
        
        _RetVal(&valEmpty);
    } else {
        _RetVal(&valResult);
    }
}