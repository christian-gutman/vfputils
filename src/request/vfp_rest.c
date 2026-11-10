#include "vfp_rest.h"
 
void CORE_CALL Fox_WRestRequest(ParamBlk *parm)
{
    if (!parm || parm->pCount < 10)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valVerb = SafeGetParam(parm, 1);
    Value valPath = SafeGetParam(parm, 2);
    Value valHeaders = SafeGetParam(parm, 3);
    Value valContentType = SafeGetParam(parm, 4);
    Value valBoundary = SafeGetParam(parm, 5);
    Value valTextBody = SafeGetParam(parm, 6);
    Value valFilePath = SafeGetParam(parm, 7);

    Locator locResponse = parm->p[8].loc;
    Locator locStatusCode = parm->p[9].loc;

    char *szVerb = SafeGetString(&valVerb);
    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);
    char *szCont = SafeGetString(&valContentType);
    char *szBoundary = SafeGetString(&valBoundary);
    char *szBody = SafeGetString(&valTextBody);
    char *szFile = SafeGetString(&valFilePath);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestRequest(
        hConnect,
        szVerb,
        szPath,
        szHead ? szHead : "",
        szCont ? szCont : "",
        szBoundary ? szBoundary : "",
        szBody ? szBody : "",
        szFile ? szFile : "",
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szVerb)
        free(szVerb);
    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);
    if (szCont)
        free(szCont);
    if (szBoundary)
        free(szBoundary);
    if (szBody)
        free(szBody);
    if (szFile)
        free(szFile);

    SafeRetValLogical(bResult);
}
 

void CORE_CALL Fox_WRestPut(ParamBlk *parm)
{
    if (!parm || parm->pCount < 6)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value valPath = SafeGetParam(parm, 1);
    Value valHeaders = SafeGetParam(parm, 2);
    Value valTextBody = SafeGetParam(parm, 3);

    Locator locResponse = parm->p[4].loc;
    Locator locStatusCode = parm->p[5].loc;

    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);
    char *szBody = SafeGetString(&valTextBody);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestPut(
        hConnect,
        szPath,
        szHead,
        szBody,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);
    if (szBody)
        free(szBody);

    SafeRetValLogical(bResult);
}

void CORE_CALL Fox_WRestPatch(ParamBlk *parm)
{
    if (!parm || parm->pCount < 6)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value valPath = SafeGetParam(parm, 1);
    Value valHeaders = SafeGetParam(parm, 2);
    Value valTextBody = SafeGetParam(parm, 3);

    Locator locResponse = parm->p[4].loc;
    Locator locStatusCode = parm->p[5].loc;

    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);
    char *szBody = SafeGetString(&valTextBody);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestPatch(
        hConnect,
        szPath,
        szHead,
        szBody,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);
    if (szBody)
        free(szBody);

    SafeRetValLogical(bResult);
}

void CORE_CALL Fox_WRestPost(ParamBlk *parm)
{
    if (!parm || parm->pCount < 6)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value valPath = SafeGetParam(parm, 1);
    Value valHeaders = SafeGetParam(parm, 2);
    Value valTextBody = SafeGetParam(parm, 3);

    Locator locResponse = parm->p[4].loc;
    Locator locStatusCode = parm->p[5].loc;

    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);
    char *szBody = SafeGetString(&valTextBody);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestPost(
        hConnect,
        szPath,
        szHead,
        szBody,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);
    if (szBody)
        free(szBody);

    SafeRetValLogical(bResult);
}

void CORE_CALL Fox_WRestDelete(ParamBlk *parm)
{
    if (!parm || parm->pCount < 5)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value valPath = SafeGetParam(parm, 1);
    Value valHeaders = SafeGetParam(parm, 2);

    Locator locResponse = parm->p[3].loc;
    Locator locStatusCode = parm->p[4].loc;

    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestDelete(
        hConnect,
        szPath,
        szHead,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);

    SafeRetValLogical(bResult);
}

void CORE_CALL Fox_WRestGet(ParamBlk *parm)
{
    if (!parm || parm->pCount < 5)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value valPath = SafeGetParam(parm, 1);
    Value valHeaders = SafeGetParam(parm, 2);

    Locator locResponse = parm->p[3].loc;
    Locator locStatusCode = parm->p[4].loc;

    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestGet(
        hConnect,
        szPath,
        szHead,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);

    SafeRetValLogical(bResult);
}

void CORE_CALL Fox_WRestFormPost(ParamBlk *parm)
{
    if (!parm || parm->pCount < 6)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value valPath = SafeGetParam(parm, 1);
    Value valHeaders = SafeGetParam(parm, 2);
    Value valTextBody = SafeGetParam(parm, 3);

    Locator locResponse = parm->p[4].loc;
    Locator locStatusCode = parm->p[5].loc;

    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);
    char *szBody = SafeGetString(&valTextBody);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestFormPost(
        hConnect,
        szPath,
        szHead,
        szBody,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);
    if (szBody)
        free(szBody);

    SafeRetValLogical(bResult);
}

void CORE_CALL Fox_WRestFormPut(ParamBlk *parm)
{
    if (!parm || parm->pCount < 6)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value valPath = SafeGetParam(parm, 1);
    Value valHeaders = SafeGetParam(parm, 2);
    Value valTextBody = SafeGetParam(parm, 3);

    Locator locResponse = parm->p[4].loc;
    Locator locStatusCode = parm->p[5].loc;

    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);
    char *szBody = SafeGetString(&valTextBody);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestFormPut(
        hConnect,
        szPath,
        szHead,
        szBody,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);
    if (szBody)
        free(szBody);

    SafeRetValLogical(bResult);
}

void CORE_CALL Fox_WRestFormPatch(ParamBlk *parm)
{
    if (!parm || parm->pCount < 6)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }
    Value valPath = SafeGetParam(parm, 1);
    Value valHeaders = SafeGetParam(parm, 2);
    Value valTextBody = SafeGetParam(parm, 3);

    Locator locResponse = parm->p[4].loc;
    Locator locStatusCode = parm->p[5].loc;

    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);
    char *szBody = SafeGetString(&valTextBody);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestFormPatch(
        hConnect,
        szPath,
        szHead,
        szBody,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);
    if (szBody)
        free(szBody);

    SafeRetValLogical(bResult);
}
void CORE_CALL Fox_WRestMultipartPost(ParamBlk *parm)
{
    // Validamos que desde FoxPro nos envíen los 7 parámetros requeridos
    if (!parm || parm->pCount < 7)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valHandleConnect = SafeGetParam(parm, 0);
    HINTERNET hConnect = FoxHandleStr2HINTERNET(valHandleConnect);
    if (!hConnect)
    {
        SafeRetValLogical(FALSE);
        return;
    }

    Value valPath = SafeGetParam(parm, 1);
    Value valHeaders = SafeGetParam(parm, 2);
    Value valBoundary = SafeGetParam(parm, 3);
    Value valFilePath = SafeGetParam(parm, 4);

    Locator locResponse = parm->p[5].loc;
    Locator locStatusCode = parm->p[6].loc;

    char *szPath = SafeGetString(&valPath);
    char *szHead = SafeGetString(&valHeaders);
    char *szBoundary = SafeGetString(&valBoundary);
    char *szFile = SafeGetString(&valFilePath);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WRestMultipartPost(
        hConnect,
        szPath,
        szHead,
        szBoundary,
        szFile,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (szPath)
        free(szPath);
    if (szHead)
        free(szHead);
    if (szBoundary)
        free(szBoundary);
    if (szFile)
        free(szFile);

    SafeRetValLogical(bResult);
}