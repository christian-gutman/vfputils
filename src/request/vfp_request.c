#include "vfp_request.h"

// ---- Utf82Ansi / Ansi2Utf8  ----

// FoxPro: lcTextoAnsi = WUtf8ToAnsi(lcTextoUtf8)
void CORE_CALL Fox_WUtf8ToAnsi(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        _RetChar("");
        return;
    }
    Value valUtf8 = SafeGetParam(parm, 0);
    char *szUtf8 = SafeGetString(&valUtf8);
    if (szUtf8 && szUtf8[0] != '\0')
    {
        int ansiOutLen = 0;
        char *ansiBuffer = StrAutoToAnsi(szUtf8, (int)strlen(szUtf8), &ansiOutLen);
        if (ansiBuffer && ansiOutLen > 0)
        {
            Value vRet = {'C', 0, 0, 0, 0};
            vRet.ev_length = (unsigned int)ansiOutLen;
            vRet.ev_handle = _AllocHand(vRet.ev_length);
            if (vRet.ev_handle != 0)
            {
                _HLock(vRet.ev_handle);
                void *dest = _HandToPtr(vRet.ev_handle);
                if (dest)
                    memcpy(dest, ansiBuffer, vRet.ev_length);
                _HUnLock(vRet.ev_handle);
                _RetVal(&vRet);
            }
            else
            {
                _RetChar("");
            }
            free(ansiBuffer);
        }
        else
        {
            _RetChar("");
        }
    }
    else
    {
        _RetChar("");
    }
    if (szUtf8)
        free(szUtf8);
}

// FoxPro: lcTextoUtf8 = WAnsiToUtf8(lcTextoAnsi)
void CORE_CALL Fox_WAnsiToUtf8(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        _RetChar("");
        return;
    }
    Value valAnsi = SafeGetParam(parm, 0);
    int utf8OutLen = 0;
    char *szUtf8 = SafeGetStringUtf8(&valAnsi, &utf8OutLen);

    if (szUtf8 && utf8OutLen > 0)
    {
        Value vRet = {'C', 0, 0, 0, 0};
        vRet.ev_length = (unsigned int)utf8OutLen;
        vRet.ev_handle = _AllocHand(vRet.ev_length);
        if (vRet.ev_handle != 0)
        {
            _HLock(vRet.ev_handle);
            void *dest = _HandToPtr(vRet.ev_handle);
            if (dest)
                memcpy(dest, szUtf8, vRet.ev_length);
            _HUnLock(vRet.ev_handle);
            _RetVal(&vRet);
        }
        else
        {
            _RetChar("");
        }
        free(szUtf8);
    }
    else
    {
        _RetChar("");
    }
}

void CORE_CALL Fox_WRequest(ParamBlk *parm) 
{ 
    if (!parm || parm->pCount < 15) { 
        SafeRetValLogical(FALSE); 
        return; 
    } 

    Value valHandleConnect = SafeGetParam(parm, 0); 
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect); 
    if (!hConnect) { 
        SafeRetValLogical(FALSE); 
        return; 
    } 

    Value valVerb         = SafeGetParam(parm, 1); 
    Value valPath         = SafeGetParam(parm, 2); 
    Value valTls          = SafeGetParam(parm, 3); 
    Value valSecure       = SafeGetParam(parm, 4); 
    Value valIgnoreSsl    = SafeGetParam(parm, 5); 
    Value valCertSubject  = SafeGetParam(parm, 6); 
    Value valHeaders      = SafeGetParam(parm, 7); 
    Value valContentType  = SafeGetParam(parm, 8); 
    Value valBoundary     = SafeGetParam(parm, 9); 
    Value valTextBody     = SafeGetParam(parm, 10); 
    Value valFilePath     = SafeGetParam(parm, 11); 

    Locator locResponse   = parm->p[12].loc; 
    Locator locRequestOut = parm->p[13].loc;  
    Locator locStatusCode = parm->p[14].loc; 

    int tlsVersion = (int)valTls.ev_long; 
    
    BOOL isSecure          = (BOOL)(valSecure.ev_long != 0); 
    BOOL bIgnoreSslErrors  = (BOOL)(valIgnoreSsl.ev_long != 0); 

    char *szVerb = SafeGetString(&valVerb); 
    char *szPath = SafeGetString(&valPath); 
    char *szCert = SafeGetString(&valCertSubject); 
    char *szHead = SafeGetString(&valHeaders); 
    char *szCont = SafeGetString(&valContentType); 
    char *szBoun = SafeGetString(&valBoundary); 
    char *szBody = SafeGetString(&valTextBody); 
    char *szFile = SafeGetString(&valFilePath); 

    char *responseBuffer = NULL; 
    HINTERNET hRequestOut = NULL; 
    DWORD statusCode = 0; 

    BOOL bResult = WRequest( 
        hConnect, szVerb, szPath, tlsVersion, isSecure, bIgnoreSslErrors, 
        szCert, szHead, szCont, szBoun, szBody, szFile, 
        &responseBuffer, &hRequestOut, &statusCode); 

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode); 

    if (bResult && hRequestOut != NULL) {
        Value vHandleOut = HINTERNET2FoxHandleStr(hRequestOut);
        if (vHandleOut.ev_handle != 0) {
            _Store(&locRequestOut, &vHandleOut);
        }
    } else {
        _Store(&locRequestOut, &(Value){'C', 0, 0, 0, 0});
    }
 
    if (szVerb) free(szVerb); 
    if (szPath) free(szPath); 
    if (szCert) free(szCert); 
    if (szHead) free(szHead); 
    if (szCont) free(szCont); 
    if (szBoun) free(szBoun); 
    if (szBody) free(szBody); 
    if (szFile) free(szFile); 

    SafeRetValLogical(bResult); 
}


void CORE_CALL Fox_WConnect(ParamBlk *parm)
{
    if (!parm || parm->pCount < 3)
    {
        _RetChar("");
        return;
    }

    Value valAgent = SafeGetParam(parm, 0);
    Value valHost = SafeGetParam(parm, 1);
    Value valPort = SafeGetParam(parm, 2);
    Value valProxy = (parm->pCount > 3) ? SafeGetParam(parm, 3) : (Value){0};

    INTERNET_PORT port = (INTERNET_PORT)valPort.ev_long;

    char *szAgent = SafeGetString(&valAgent);
    char *szHost = SafeGetString(&valHost);
    char *szProxy = (parm->pCount > 3) ? SafeGetString(&valProxy) : NULL;

    HINTERNET hConnect = WConnect(szAgent, szHost, port, szProxy);

    if (hConnect)
    {
        Value foxResultHandleStr = HINTERNET2FoxHandleStr(hConnect);
        _RetVal(&foxResultHandleStr);
    }
    else
    {
        /* DWORD dwLastError = GetLastError();
         char szErrLog[128];

         _snprintf_s(szErrLog, sizeof(szErrLog), _TRUNCATE, "Fallo WConnect. GetLastError = %lu", dwLastError);
         _PutChr('\n');
         _PutStr(szErrLog);
         _PutChr('\n');
 */
        _RetChar("");
    }

    if (szAgent)
        free(szAgent);
    if (szHost)
        free(szHost);
    if (szProxy)
        free(szProxy);

    return;
}
void CORE_CALL Fox_WDisconnect(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    // por uno u otro ?
    Value val0 = SafeGetParam(parm, 0);
    BOOL L = FALSE;
    HINTERNET hConnect = FoxHandleStr2HINTERNET(val0);
    if (hConnect)
    {
        L = WDisconnect(&hConnect);
        if (L)
        {
            if (parm->p[0].loc.l_type == 'R')
            {
                _Store(&parm->p[0].loc, &(Value){'C', 0, 0, 0, 0});
            }
        }
    }
    SafeRetValLogical(L);
    return;
    /* por referencia R
    Locator loc0 = parm->p[0].loc;
    Value val0;
    _Load(&loc0, &val0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(val0);
    if (hConnect) {
        BOOL L = WDisconnect(&hConnect);
        if (L) {
            _Store(&loc0, &(Value){'C', 0, 0, 0, 0});
        }
        SafeRetValLogical(L);
        return;
    }
    SafeRetValLogical(FALSE);
    */
    /*por valor C if (!parm || parm->pCount < 1)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value val0 = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(val0);
    if (hConnect)
    {
        BOOL L = WDisconnect(&hConnect);
        SafeRetValLogical(L);
        return;
    }
    SafeRetValLogical(FALSE);*/
}

void CORE_CALL Fox_WCloseRequest(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value val0 = SafeGetParam(parm, 0);
    BOOL L = FALSE;
    HINTERNET hConnect = FoxHandleStr2HINTERNET(val0);
    if (hConnect)
    {
        L = WCloseRequest(&hConnect);
        if (L)
        {
            if (parm->p[0].loc.l_type == 'R')
            {
                _Store(&parm->p[0].loc, &(Value){'C', 0, 0, 0, 0});
            }
        }
    }
    SafeRetValLogical(L);
    return;
    /* por referencia R
    Locator loc0 = parm->p[0].loc;
    Value val0;
    _Load(&loc0, &val0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(val0);
    if (hConnect) {
        BOOL L = WDisconnect(&hConnect);
        if (L) {
            _Store(&loc0, &(Value){'C', 0, 0, 0, 0});
        }
        SafeRetValLogical(L);
        return;
    }
    SafeRetValLogical(FALSE);
    */
    /*por valor C if (!parm || parm->pCount < 1)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value val0 = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(val0);
    if (hConnect)
    {
        BOOL L = WDisconnect(&hConnect);
        SafeRetValLogical(L);
        return;
    }
    SafeRetValLogical(FALSE);*/
}