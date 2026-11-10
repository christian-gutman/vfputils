#include "vfp_req_file.h"

void CORE_CALL Fox_WDownloadToFile(ParamBlk *parm)
{
    // Validamos que desde FoxPro nos envíen como mínimo los 11 parámetros requeridos
    if (!parm || parm->pCount < 11) {
        SafeRetValLogical(FALSE);
        return;
    }

    HINTERNET hConnect = FoxHandleStr2HINTERNET(SafeGetParam(parm, 0));
    if (!hConnect) { 
        SafeRetValLogical(FALSE); 
        return; 
    }

    // 1. Extraemos los parámetros de configuración desde FoxPro
    Value valVerb     = SafeGetParam(parm, 1);
    Value valPath     = SafeGetParam(parm, 2);
    Value valTls      = SafeGetParam(parm, 3);
    Value valSecure   = SafeGetParam(parm, 4);
    Value valIgnore   = SafeGetParam(parm, 5);
    Value valCert     = SafeGetParam(parm, 6);
    Value valHeaders  = SafeGetParam(parm, 7);
    Value valContent  = SafeGetParam(parm, 8);
    Value valSavePath = SafeGetParam(parm, 9);
    
    // Localizador por referencia (@) para capturar el Status Code / Error Code
    Locator locStatus = parm->p[10].loc; 

    // 2. Conversión segura a strings tradicionales de C
    char *szVerb   = SafeGetString(&valVerb);
    char *szPath   = SafeGetString(&valPath);
    char *szCert   = SafeGetString(&valCert);
    char *szHead   = SafeGetString(&valHeaders);
    char *szCont   = SafeGetString(&valContent);
    char *szSave   = SafeGetString(&valSavePath);
    int tlsVersion = (int)valTls.ev_long;

    DWORD statusCode = 0;

    // 3. Invocación a la lógica del Core en C
    BOOL bResult = WDownloadToFile(
        hConnect, szVerb, szPath, tlsVersion, 
        valSecure.ev_length, valIgnore.ev_length, 
        szCert, szHead, szCont, szSave, &statusCode
    );

    // 4. Devolución del código de estado HTTP (o el GetLastError() si bResult falló en red)
    Value vStatus = {'I', 0, 0, 0, 0};
    vStatus.ev_long = (long)(bResult ? statusCode : GetLastError());
    _Store(&locStatus, &vStatus);

    // 5. Limpieza obligatoria de la memoria temporal del Bridge
    if (szVerb) free(szVerb); 
    if (szPath) free(szPath); 
    if (szCert) free(szCert);
    if (szHead) free(szHead); 
    if (szCont) free(szCont); 
    if (szSave) free(szSave);

    SafeRetValLogical(bResult);
}

void CORE_CALL Fox_WRequestToFile(ParamBlk *parm)
{
    // Validamos que desde FoxPro nos envíen los 13 parámetros requeridos
    if (!parm || parm->pCount < 13) {
        SafeRetValLogical(FALSE);
        return;
    }

    HINTERNET hConnect = FoxHandleStr2HINTERNET(SafeGetParam(parm, 0));
    if (!hConnect) { 
        SafeRetValLogical(FALSE); 
        return; 
    }

    // 1. Extraemos los parámetros por valor de FoxPro
    Value valVerb      = SafeGetParam(parm, 1);
    Value valPath      = SafeGetParam(parm, 2);
    Value valTls       = SafeGetParam(parm, 3);
    Value valSecure    = SafeGetParam(parm, 4);
    Value valIgnore    = SafeGetParam(parm, 5);
    Value valCert      = SafeGetParam(parm, 6);
    Value valHeaders   = SafeGetParam(parm, 7);
    Value valContent   = SafeGetParam(parm, 8);
    Value valBoundary  = SafeGetParam(parm, 9);
    Value valInputPath = SafeGetParam(parm, 10);
    Value valOutputPath= SafeGetParam(parm, 11);
    
    // Localizador por referencia (@) para el Status Code
    Locator locStatus  = parm->p[12].loc;

    // 2. Conversión segura a strings de C
    char *szVerb   = SafeGetString(&valVerb);
    char *szPath   = SafeGetString(&valPath);
    char *szCert   = SafeGetString(&valCert);
    char *szHead   = SafeGetString(&valHeaders);
    char *szCont   = SafeGetString(&valContent);
    char *szBound  = SafeGetString(&valBoundary);
    char *szInFile = SafeGetString(&valInputPath);
    char *szOutFile= SafeGetString(&valOutputPath);
    int tlsVersion = (int)valTls.ev_long;

    DWORD statusCode = 0;

    // 3. Invocación a la lógica del SDK en C
    BOOL bResult = WRequestToFile(
        hConnect, szVerb, szPath, tlsVersion,
        valSecure.ev_length, valIgnore.ev_length, szCert,
        szHead, szCont, szBound, szInFile, szOutFile, &statusCode
    );

    // 4. Devolución de códigos de control de Windows o HTTP
    Value vStatus = {'I', 0, 0, 0, 0};
    vStatus.ev_long = (long)(bResult ? statusCode : GetLastError());
    _Store(&locStatus, &vStatus);

    // 5. Limpieza de memoria temporal obligatoria de C
    if (szVerb)    free(szVerb);   
    if (szPath)    free(szPath);     
    if (szCert)    free(szCert);
    if (szHead)    free(szHead);   
    if (szCont)    free(szCont);     
    if (szBound)   free(szBound);
    if (szInFile)  free(szInFile); 
    if (szOutFile) free(szOutFile);

    SafeRetValLogical(bResult);
}
 
void CORE_CALL Fox_WDownload(ParamBlk *parm)
{
    if (!parm || parm->pCount < 11)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    // 1. Extraer hConnect binario híbrido
    Value valConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    // 2. Extraer parámetros escalares de FoxPro
    Value valVerb = SafeGetParam(parm, 1);
    Value valPath = SafeGetParam(parm, 2);
    Value valTls = SafeGetParam(parm, 3);
    Value valSecure = SafeGetParam(parm, 4);
    Value valIgnoreSsl = SafeGetParam(parm, 5);
    Value valCertSubject = SafeGetParam(parm, 6);
    Value valHeaders = SafeGetParam(parm, 7);
    Value valContentType = SafeGetParam(parm, 8);
    Value valSavePath = SafeGetParam(parm, 9);

    // Capturamos la última variable por referencia usando el índice directo
    Locator locStatusCode = parm->p[10].loc;

    int tlsVersion = (int)valTls.ev_long;
    BOOL isSecure = (valSecure.ev_long != 0 || valSecure.ev_length != 0);
    BOOL bIgnoreSslErrors = (valIgnoreSsl.ev_long != 0 || valIgnoreSsl.ev_length != 0);

    // 3. Extraer strings ANSI temporales
    char *szVerb = SafeGetString(&valVerb);
    char *szPath = SafeGetString(&valPath);
    char *szCert = SafeGetString(&valCertSubject);
    char *szHead = SafeGetString(&valHeaders);
    char *szCont = SafeGetString(&valContentType);
    char *szFile = SafeGetString(&valSavePath);

    DWORD statusCode = 0;

    // 5. Invocar función core
    BOOL bResult = WDownloadToFile(
        hConnect, szVerb, szPath, tlsVersion, isSecure, bIgnoreSslErrors, szCert,
        szHead, szCont, szFile, &statusCode);

    if (bResult)
    {
        Value vStatus = {'I', 0, 0, 0, 0};
        vStatus.ev_long = (long)statusCode;
        _Store(&locStatusCode, &vStatus);
    }

    if (szVerb)
        free(szVerb);
    if (szPath)
        free(szPath);
    if (szCert)
        free(szCert);
    if (szHead)
        free(szHead);
    if (szCont)
        free(szCont);
    if (szFile)
        free(szFile);

    SafeRetValLogical(bResult);
}