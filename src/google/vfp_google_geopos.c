#include "vfp_google_geopos.h"

// FoxPro: llOk = WGoogleGeoPos(loConnection, "Calle", "Altura", "Ciudad", "Pais", "ApiKey", @lcJsonOut, @lnStatus)
void CORE_CALL Fox_WGoogleGeoPos(ParamBlk *parm)
{
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

    Value v1 = SafeGetParam(parm, 1);
    Value v2 = SafeGetParam(parm, 2);
    Value v3 = SafeGetParam(parm, 3);
    Value v4 = SafeGetParam(parm, 4);
    Value v5 = SafeGetParam(parm, 5);

    Locator locResponse = parm->p[6].loc;
    Locator locStatusCode = parm->p[7].loc;

    char *sz1 = SafeGetString(&v1);
    char *sz2 = SafeGetString(&v2);
    char *sz3 = SafeGetString(&v3);
    char *sz4 = SafeGetString(&v4);
    char *sz5 = SafeGetString(&v5);

    char *responseBuffer = NULL;
    DWORD statusCode = 0;

    BOOL bResult = WGoogleGeoPos(
        hConnect,
        sz1,
        sz2,
        sz3,
        sz4,
        sz5,
        &responseBuffer,
        &statusCode);

    StoreVfpResponse(bResult, statusCode, responseBuffer, &locResponse, &locStatusCode);

    if (sz1)
        free(sz1);
    if (sz2)
        free(sz2);
    if (sz3)
        free(sz3);
    if (sz4)
        free(sz4);
    if (sz5)
        free(sz5);

    SafeRetValLogical(bResult);
}