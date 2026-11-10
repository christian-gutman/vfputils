#include "vfp_crypto.h"

void CORE_CALL Fox_MD5(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }

    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);

    if (!pData || dataLen <= 0)
    {
        if (pData)
            free(pData);
        SafeRetValString("");
        return;
    }
    char hexHash[65] = {0};

    BOOL success = MD5(pData, (size_t)dataLen, hexHash);
    free(pData);
    if (success && hexHash[0] != '\0')
    {
        SafeRetValString(hexHash);
    }
    else
    {
        SafeRetValString("");
    }
}

// Sintaxis VFP: lcHexHash = SHA1(cData)
void CORE_CALL Fox_SHA1(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }
    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);

    if (!pData || dataLen <= 0)
    {
        if (pData)
            free(pData);
        SafeRetValString("");
        return;
    }

    char hexHash[41] = {0}; // SHA1 = 20 bytes -> 40 hex chars + '\0'
    BOOL success = SHA1(pData, (size_t)dataLen, hexHash);
    free(pData);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// Sintaxis VFP: lcHexHash = SHA256(cData)
// VFP: cHashHex = SHA256(cData)
void CORE_CALL Fox_SHA256(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }
    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);

    if (!pData || dataLen <= 0)
    {
        if (pData)
            free(pData);
        SafeRetValString("");
        return;
    }
    char hexHash[65] = {0};
    BOOL success = SHA256(pData, (size_t)dataLen, hexHash);
    free(pData);
    if (success && hexHash[0] != '\0')
    {
        SafeRetValString(hexHash);
    }
    else
    {
        SafeRetValString("");
    }
}

// VFP: cHashHex = SHA384(cData)
void CORE_CALL Fox_SHA384(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }

    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);

    if (!pData || dataLen <= 0)
    {
        if (pData)
            free(pData);
        SafeRetValString("");
        return;
    }

    char hexHash[97] = {0}; // SHA384 = 48 bytes -> 96 hex chars + '\0'
    BOOL success = SHA384(pData, (size_t)dataLen, hexHash);
    free(pData);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}
// Sintaxis VFP: lcHexHash = SHA512(cData)
void CORE_CALL Fox_SHA512(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }
    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);

    if (!pData || dataLen <= 0)
    {
        if (pData)
            free(pData);
        SafeRetValString("");
        return;
    }

    char hexHash[129] = {0}; // SHA512 = 64 bytes -> 128 hex chars + '\0'
    BOOL success = SHA512(pData, (size_t)dataLen, hexHash);
    free(pData);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// VFP: cHmacHex = HMACSHA1(cData, cKey)
void CORE_CALL Fox_HMACSHA1(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);
    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pData || dataLen <= 0 || !pKey || keyLen <= 0)
    {
        if (pData)
            free(pData);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    char hexHash[41] = {0}; // HMAC-SHA1 = 20 bytes -> 40 hex + '\0'
    BOOL success = HMACSHA1(pData, (size_t)dataLen, pKey, (size_t)keyLen, hexHash);
    free(pData);
    free(pKey);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}
// VFP: cHmacHex = HMACSHA384(cData, cKey)
void CORE_CALL Fox_HMACSHA384(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);
    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pData || dataLen <= 0 || !pKey || keyLen <= 0)
    {
        if (pData)
            free(pData);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    char hexHash[97] = {0}; // HMAC-SHA384 = 48 bytes -> 96 hex chars + '\0'
    BOOL success = HMACSHA384(pData, (size_t)dataLen, pKey, (size_t)keyLen, hexHash);
    free(pData);
    free(pKey);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}
// VFP: cHmacHex = HMACSHA512(cData, cKey)
void CORE_CALL Fox_HMACSHA512(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);
    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pData || dataLen <= 0 || !pKey || keyLen <= 0)
    {
        if (pData)
            free(pData);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    char hexHash[129] = {0}; // HMAC-SHA512 = 64 bytes -> 128 hex + '\0'
    BOOL success = HMACSHA512(pData, (size_t)dataLen, pKey, (size_t)keyLen, hexHash);
    free(pData);
    free(pKey);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// VFP: cHmacHex = HMACMD5(cData, cKey)
void CORE_CALL Fox_HMACMD5(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);
    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pData || dataLen <= 0 || !pKey || keyLen <= 0)
    {
        if (pData)
            free(pData);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    char hexHash[33] = {0}; // HMAC-MD5 = 16 bytes -> 32 hex + '\0'
    BOOL success = HMACMD5(pData, (size_t)dataLen, pKey, (size_t)keyLen, hexHash);
    free(pData);
    free(pKey);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}
// Sintaxis VFP: lcHexHMAC = HMACSHA256(cData, cKey)
// VFP: cHmacHex = HMACSHA256(cData, cKey)
void CORE_CALL Fox_HMACSHA256(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }
    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pData || dataLen <= 0 || !pKey || keyLen <= 0)
    {
        if (pData)
            free(pData);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    char hexHash[65] = {0};

    BOOL success = HMACSHA256(pData, (size_t)dataLen, pKey, (size_t)keyLen, hexHash);

    free(pData);
    free(pKey);

    if (success && hexHash[0] != '\0')
    {
        SafeRetValString(hexHash);
    }
    else
    {
        SafeRetValString("");
    }
}
// VFP: cHmacHex = GENHMAC(cData, cKey, cAlgorithm)
void CORE_CALL Fox_GenerateHmacAlgorithm(ParamBlk *parm)
{
    if (!parm || parm->pCount < 3)
    {
        _RetChar("");
        return;
    }

    int dataLen = 0;
    char *pData = GetParamStringUtf8(parm, 0, &dataLen);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    Value val2 = SafeGetParam(parm, 2);
    char *pAlgorithm = SafeGetString(&val2);

    if (!pData || dataLen <= 0 || !pKey || keyLen <= 0 || !pAlgorithm)
    {
        if (pData)
            free(pData);
        if (pKey)
            free(pKey);
        if (pAlgorithm)
            free(pAlgorithm);
        _RetChar("");
        return;
    }

    int algoLen = (int)strlen(pAlgorithm);
    wchar_t *wAlgorithm = StrAutoToUnicode(pAlgorithm, algoLen, NULL);

    char outputHex[256] = {0};

    int result = GenerateHmacAlgorithm(pData, (size_t)dataLen, pKey, (size_t)keyLen, wAlgorithm, outputHex);

    if (wAlgorithm)
        free(wAlgorithm);
    if (pAlgorithm)
        free(pAlgorithm);
    if (pKey)
        free(pKey);
    if (pData)
        free(pData);

    if (result != 0 && outputHex[0] != '\0')
    {
        SafeRetValString(outputHex);
    }
    else
    {
        _RetChar("");
    }
}
// VFP: cNonceHex = CREATESECURENONCE(nMaxLen)
void CORE_CALL Fox_CreateSecureNonce(ParamBlk *parm)
{
    // 1. Validar que la estructura de parámetros sea consistente
    if (!parm || parm->pCount < 1)
    {
        _RetChar("");
        return;
    }

    // 2. Extraer el primer parámetro de forma totalmente segura
    Value val0 = SafeGetParam(parm, 0);

    // Extraemos el número entero largo enviado desde FoxPro
    DWORD maxLen = (DWORD)SafeGetLong(&val0);

    // Validación de límites para evitar desbordamientos o asignaciones inválidas
    if (maxLen == 0 || maxLen > 2048)
    {
        _RetChar("");
        return;
    }

    // 3. Asignar memoria dinámica en el Heap para el buffer de salida
    char *outputHex = (char *)malloc(maxLen + 1);
    if (!outputHex)
    {
        _RetChar("");
        return;
    }

    // Inicializar el buffer a ceros de forma segura
    SecureZeroMemory(outputHex, maxLen + 1);

    // 4. Invocar a tu función nativa en C
    CreateSecureNonce(outputHex, maxLen);

    // 5. Retornar el string hexadecimal a FoxPro usando tu API robusta
    SafeRetValString(outputHex);

    // 6. Limpieza estricta de la memoria asignada en el Heap para evitar Leaks
    free(outputHex);
}

// VFP: cHashHex = GENHASHALGO(cData, nDataLen, cAlgorithm)
void CORE_CALL Fox_GenerateHashAlgorithm(ParamBlk *parm)
{
    // 1. Validar rigurosamente que la estructura de parámetros sea consistente
    if (!parm || parm->pCount < 3)
    {
        _RetChar("");
        return;
    }

    // 2. Extraer los 3 valores usando tus abstracciones seguras (Descomentadas)
    Value val0 = SafeGetParam(parm, 0);
    Value val1 = SafeGetParam(parm, 1);
    Value val2 = SafeGetParam(parm, 2);

    // 3. Obtener los punteros a los buffers y longitudes físicas reales
    char *pData = SafeGetString(&val0);
    int pDataLen = SafeGetLong(&val1);
    char *pAlgorithm = SafeGetString(&val2);

    // Validación de seguridad para los punteros de entrada
    if (!pData || !pAlgorithm)
    {
        if (pAlgorithm)
            free(pAlgorithm);
        if (pData)
            free(pData);
        _RetChar("");
        return;
    }

    int algoLen = (int)strlen(pAlgorithm);
    wchar_t *wAlgorithm = StrAutoToUnicode(pAlgorithm, algoLen, NULL);

    char outputHex[256] = {0};

    int result = GenerateHashAlgorithm(pData, (size_t)pDataLen, wAlgorithm, outputHex);

    if (wAlgorithm)
        free(wAlgorithm);
    if (pAlgorithm)
        free(pAlgorithm);
    if (pData)
        free(pData);

    if (result != 0 && outputHex[0] != '\0')
    {
        SafeRetValString(outputHex);
    }
    else
    {
        _RetChar("");
    }
}

// VFP: cHashHex = MD5File(cFilePath)
void CORE_CALL Fox_MD5File(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    char *pPath = SafeGetString(&val0);

    if (!pPath || pPath[0] == '\0')
    {
        if (pPath)
            free(pPath);
        SafeRetValString("");
        return;
    }

    int pathLen = (int)strlen(pPath);
    wchar_t *wPath = StrAutoToUnicode(pPath, pathLen, NULL);

    char hexHash[33] = {0};
    BOOL success = MD5File(wPath, hexHash);

    free(wPath);
    free(pPath);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// VFP: cHashHex = MD5File(cFilePath)
void CORE_CALL Fox_SHA1File(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    char *pPath = SafeGetString(&val0);

    if (!pPath || pPath[0] == '\0')
    {
        if (pPath)
            free(pPath);
        SafeRetValString("");
        return;
    }

    int pathLen = (int)strlen(pPath);
    wchar_t *wPath = StrAutoToUnicode(pPath, pathLen, NULL);

    char hexHash[41] = {0};
    BOOL success = SHA1File(wPath, hexHash);

    free(wPath);
    free(pPath);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}
// VFP: cHashHex = SHA256FILE(cFilePath)
void CORE_CALL Fox_SHA256File(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    char *pPath = SafeGetString(&val0);

    if (!pPath || pPath[0] == '\0')
    {
        if (pPath)
            free(pPath);
        SafeRetValString("");
        return;
    }

    int pathLen = (int)strlen(pPath);
    wchar_t *wPath = StrAutoToUnicode(pPath, pathLen, NULL);

    char hexHash[65] = {0};
    BOOL success = SHA256File(wPath, hexHash);

    free(wPath);
    free(pPath);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// VFP: cHashHex = MD5File(cFilePath)
void CORE_CALL Fox_SHA512File(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    char *pPath = SafeGetString(&val0);

    if (!pPath || pPath[0] == '\0')
    {
        if (pPath)
            free(pPath);
        SafeRetValString("");
        return;
    }

    int pathLen = (int)strlen(pPath);
    wchar_t *wPath = StrAutoToUnicode(pPath, pathLen, NULL);

    char hexHash[129] = {0};
    BOOL success = SHA512File(wPath, hexHash);

    free(wPath);
    free(pPath);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}
// VFP: cHashHex = GENFILEHASH(cFilePath, cAlgorithm)
void CORE_CALL Fox_GenerateFileHashAlgorithm(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        _RetChar("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    Value val1 = SafeGetParam(parm, 1);
    char *pPath = SafeGetString(&val0);
    char *pAlgorithm = SafeGetString(&val1);

    if (!pPath || pPath[0] == '\0' || !pAlgorithm)
    {
        if (pPath)
            free(pPath);
        if (pAlgorithm)
            free(pAlgorithm);
        _RetChar("");
        return;
    }

    wchar_t *wPath = StrAutoToUnicode(pPath, (int)strlen(pPath), NULL);
    wchar_t *wAlgorithm = StrAutoToUnicode(pAlgorithm, (int)strlen(pAlgorithm), NULL);

    char outputHex[256] = {0};
    int result = GenerateFileHashAlgorithm(wPath, wAlgorithm, outputHex);

    free(wPath);
    free(wAlgorithm);
    free(pPath);
    free(pAlgorithm);

    if (result != 0 && outputHex[0] != '\0')
        SafeRetValString(outputHex);
    else
        _RetChar("");
}
// VFP: cHmacHex = HMACSHA256FILE(cFilePath, cKey)
void CORE_CALL Fox_HMACSHA256File(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    char *pPath = SafeGetString(&val0);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pPath || pPath[0] == '\0' || !pKey || keyLen <= 0)
    {
        if (pPath)
            free(pPath);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    wchar_t *wPath = StrAutoToUnicode(pPath, (int)strlen(pPath), NULL);

    char hexHash[65] = {0}; // HMAC-SHA256 = 32 bytes -> 64 hex + '\0'
    BOOL success = HMACSHA256File(wPath, pKey, (size_t)keyLen, hexHash);

    free(wPath);
    free(pPath);
    free(pKey);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// VFP: cHmacHex = HMACMD5FILE(cFilePath, cKey)
void CORE_CALL Fox_HMACMD5File(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    char *pPath = SafeGetString(&val0);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pPath || pPath[0] == '\0' || !pKey || keyLen <= 0)
    {
        if (pPath)
            free(pPath);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    wchar_t *wPath = StrAutoToUnicode(pPath, (int)strlen(pPath), NULL);

    char hexHash[33] = {0}; // HMAC-MD5 = 16 bytes -> 32 hex + '\0'
    BOOL success = HMACMD5File(wPath, pKey, (size_t)keyLen, hexHash);

    free(wPath);
    free(pPath);
    free(pKey);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// VFP: cHmacHex = HMACSHA1FILE(cFilePath, cKey)
void CORE_CALL Fox_HMACSHA1File(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    char *pPath = SafeGetString(&val0);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pPath || pPath[0] == '\0' || !pKey || keyLen <= 0)
    {
        if (pPath)
            free(pPath);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    wchar_t *wPath = StrAutoToUnicode(pPath, (int)strlen(pPath), NULL);

    char hexHash[41] = {0}; // HMAC-SHA1 = 20 bytes -> 40 hex + '\0'
    BOOL success = HMACSHA1File(wPath, pKey, (size_t)keyLen, hexHash);

    free(wPath);
    free(pPath);
    free(pKey);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// VFP: cHmacHex = HMACSHA384FILE(cFilePath, cKey)
void CORE_CALL Fox_HMACSHA384File(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    char *pPath = SafeGetString(&val0);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pPath || pPath[0] == '\0' || !pKey || keyLen <= 0)
    {
        if (pPath)
            free(pPath);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    wchar_t *wPath = StrAutoToUnicode(pPath, (int)strlen(pPath), NULL);

    char hexHash[97] = {0}; // HMAC-SHA384 = 48 bytes -> 96 hex + '\0'
    BOOL success = HMACSHA384File(wPath, pKey, (size_t)keyLen, hexHash);

    free(wPath);
    free(pPath);
    free(pKey);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// VFP: cHmacHex = HMACSHA512FILE(cFilePath, cKey)
void CORE_CALL Fox_HMACSHA512File(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    char *pPath = SafeGetString(&val0);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pPath || pPath[0] == '\0' || !pKey || keyLen <= 0)
    {
        if (pPath)
            free(pPath);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }

    wchar_t *wPath = StrAutoToUnicode(pPath, (int)strlen(pPath), NULL);

    char hexHash[129] = {0}; // HMAC-SHA512 = 64 bytes -> 128 hex + '\0'
    BOOL success = HMACSHA512File(wPath, pKey, (size_t)keyLen, hexHash);

    free(wPath);
    free(pPath);
    free(pKey);

    SafeRetValString(success && hexHash[0] != '\0' ? hexHash : "");
}

// VFP: cHmacHex = GENFILEHMAC(cFilePath, cKey, cAlgorithm)
void CORE_CALL Fox_GenerateFileHmacAlgorithm(ParamBlk *parm)
{
    if (!parm || parm->pCount < 3)
    {
        _RetChar("");
        return;
    }

    Value val0 = SafeGetParam(parm, 0);
    Value val2 = SafeGetParam(parm, 2);
    char *pPath = SafeGetString(&val0);
    char *pAlgorithm = SafeGetString(&val2);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pPath || pPath[0] == '\0' || !pKey || keyLen <= 0 || !pAlgorithm)
    {
        if (pPath)
            free(pPath);
        if (pKey)
            free(pKey);
        if (pAlgorithm)
            free(pAlgorithm);
        _RetChar("");
        return;
    }

    wchar_t *wPath = StrAutoToUnicode(pPath, (int)strlen(pPath), NULL);
    wchar_t *wAlgorithm = StrAutoToUnicode(pAlgorithm, (int)strlen(pAlgorithm), NULL);

    char outputHex[256] = {0};
    int result = GenerateFileHmacAlgorithm(wPath, pKey, (size_t)keyLen, wAlgorithm, outputHex);

    free(wPath);
    free(wAlgorithm);
    free(pPath);
    free(pKey);
    free(pAlgorithm);

    if (result != 0 && outputHex[0] != '\0')
        SafeRetValString(outputHex);
    else
        _RetChar("");
}
// ============================================================================
// VFP: cBase64 = UNITOUTF8BASE64(cUnicodeInput)
// ============================================================================
void CORE_CALL Fox_UnicodeToUtf8Base64(ParamBlk *parm)
{
    Value val0 = SafeGetParam(parm, 0);
    char *pInput = SafeGetString(&val0);

    if (!pInput)
    {
        _RetChar("");
        return;
    }

    int inputLen = (int)strlen(pInput);
    wchar_t *wInput = StrAutoToUnicode(pInput, inputLen, NULL);

    free(pInput);

    if (!wInput)
    {
        _RetChar("");
        return;
    }

    wchar_t *wResult = UnicodeToUtf8Base64(wInput);
    free(wInput);

    if (wResult)
    {

        int ansiLength = WideCharToMultiByte(CP_THREAD_ACP, 0, wResult, -1, NULL, 0, NULL, NULL);
        char *ansiBuffer = (char *)malloc(ansiLength);

        if (ansiBuffer)
        {
            WideCharToMultiByte(CP_THREAD_ACP, 0, wResult, -1, ansiBuffer, ansiLength, NULL, NULL);
            SafeRetValString(ansiBuffer);
            free(ansiBuffer);
        }
        else
        {
            _RetChar("");
        }
        free(wResult);
    }
    else
    {
        _RetChar("");
    }
}

// ============================================================================
// VFP: cUnicodeText = UTF8BASE64TOUNI(cBase64Input)
// ============================================================================
void CORE_CALL Fox_Utf8Base64ToUnicode(ParamBlk *parm)
{

    Value val0 = SafeGetParam(parm, 0);
    char *pBase64Input = SafeGetString(&val0);

    if (!pBase64Input)
    {
        _RetChar("");
        return;
    }

    int base64Len = (int)strlen(pBase64Input);
    wchar_t *wBase64Input = StrAutoToUnicode(pBase64Input, base64Len, NULL);

    free(pBase64Input);

    if (!wBase64Input)
    {
        _RetChar("");
        return;
    }

    wchar_t *wResult = Utf8Base64ToUnicode(wBase64Input);
    free(wBase64Input);

    if (wResult)
    {
        int ansiLength = WideCharToMultiByte(CP_THREAD_ACP, 0, wResult, -1, NULL, 0, NULL, NULL);
        char *ansiBuffer = (char *)malloc(ansiLength);

        if (ansiBuffer)
        {
            WideCharToMultiByte(CP_THREAD_ACP, 0, wResult, -1, ansiBuffer, ansiLength, NULL, NULL);

            SafeRetValString(ansiBuffer);
            free(ansiBuffer);
        }
        else
        {
            _RetChar("");
        }

        free(wResult);
    }
    else
    {
        _RetChar("");
    }
}
// VFP: cData = EncryptString(cText, cKey)
void CORE_CALL Fox_SecureEncryptString(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    int textLen = 0;
    char *pText = GetParamStringUtf8(parm, 0, &textLen);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pText || textLen <= 0 || !pKey || keyLen <= 0)
    {
        if (pText)
            free(pText);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }
    char *cData = NULL;
    BOOL result = SecureEncryptString(pText, pKey, &cData);

    if (result && cData)
    {
        SafeRetValString(cData);
        free(cData);
    }
    else
    {
        SafeRetValString("");
    }

    free(cData);
    free(pText);
    free(pKey);
}

// VFP: cData = DecryptString(cText, cKey)
void CORE_CALL Fox_SecureDecryptString(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    int textLen = 0;
    char *pText = GetParamStringUtf8(parm, 0, &textLen);

    int keyLen = 0;
    char *pKey = GetParamStringUtf8(parm, 1, &keyLen);

    if (!pText || textLen <= 0 || !pKey || keyLen <= 0)
    {
        if (pText)
            free(pText);
        if (pKey)
            free(pKey);
        SafeRetValString("");
        return;
    }
    char *cData = NULL;
    BOOL result = SecureDecryptString(pText, pKey, &cData);

    if (result && cData)
    {
        SafeRetValString(cData);
        free(cData);
    }
    else
    {
        SafeRetValString("");
    }

    free(cData);
    free(pText);
    free(pKey);
}