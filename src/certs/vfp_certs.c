#include "vfp_certs.h"

void CORE_CALL Fox_CertGetExpiry(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2) {
        SafeRetValString("ERROR: Parámetros insuficientes");
        return;
    }

    int pathLen = 0;
    char *pPath = GetParamString(parm, 0, &pathLen);
    if (!pPath || pathLen <= 0) {
        SafeRetValString("ERROR: Path del certificado vacío o inválido");
        return;
    }

    int pwdLen = 0;
    char *pPwd = GetParamString(parm, 1, &pwdLen); // Puede retornar NULL de forma segura si está vacío

    char dateStr[64] = {0};
    
    // Delegar al Core puro en C
    if (Cert_GetExpiry(pPath, pathLen, pPwd, pwdLen, dateStr, sizeof(dateStr))) {
        SafeRetValString(dateStr);
    } else {
        SafeRetValString("ERROR: Formato de certificado inválido o contraseña incorrecta");
    }
    free(pPath);
    free(pPwd);
}

void CORE_CALL Fox_CertSignMsg(ParamBlk *parm)
{
    if (!parm || parm->pCount < 3) {
        SafeRetValString("ERROR: Parámetros insuficientes");
        return;
    }

    int xmlLen = 0;
    char *pXml = GetParamString(parm, 0, &xmlLen);
    if (!pXml || xmlLen <= 0) {
        SafeRetValString("ERROR: XML vacío o inválido");
        return;
    }

    int pfxLen = 0;
    char *pPfxPath = GetParamString(parm, 1, &pfxLen);
    if (!pPfxPath || pfxLen <= 0) {
        SafeRetValString("ERROR: Path del PFX vacío o inválido");
        return;
    }

    int pwdLen = 0;
    char *pPwd = GetParamString(parm, 2, &pwdLen);

    // Delegar al Core puro en C
    char *base64Result = Cert_SignMessage(pXml, xmlLen, pPfxPath, pfxLen, pPwd, pwdLen);

    if (base64Result) {
        SafeRetValString(base64Result);
        free(base64Result); // El core hizo malloc, nosotros lo liberamos acá tras enviarlo a VFP
    } else {
        SafeRetValString("ERROR: No se pudo firmar el mensaje");
    }
    free(pPfxPath);
    free(pXml);
    free(pPwd);
}
