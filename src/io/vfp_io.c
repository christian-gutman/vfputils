#include "vfp_io.h"
/*
void CORE_CALL Fox_ReadFileBytes(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        _RetChar("");
        return;
    }

    int pathLen = 0;
    char *pPath = GetParamString(parm, 0, &pathLen);
    if (!pPath || pathLen <= 0)
    {
        if (pPath)
            free(pPath);
        _RetChar("");
        return;
    }

    wchar_t *wPath = StrAutoToUnicode(pPath, pathLen, NULL);
    free(pPath);

    if (!wPath)
    {
        _RetChar("");
        return;
    }

    DWORD fileSize = 0;
    BYTE *fileBytes = ReadFileBytesC(wPath, &fileSize);
    free(wPath);

    SafeRetValBinary(fileBytes, fileSize);

    if (fileBytes)
    {
        free(fileBytes);
    }
}

// VFP: = WRITEFILEBYTES(cPath, cCommandBuffer, nSize)
void CORE_CALL Fox_WriteFileBytes(ParamBlk *parm) {
    // 1. Validar estrictamente la presencia de los 3 parámetros requeridos
    if (!parm || parm->pCount < 3) {
        SafeRetValLogical(FALSE);
        return;
    }

    // 2. Extraer el primer parámetro: Ruta del archivo (Índice 0)
    int pathLen = 0;
    char *pPath = GetParamString(parm, 0, &pathLen);
    if (!pPath || pathLen <= 0) {
        if (pPath) free(pPath);
        SafeRetValLogical(FALSE);
        return;
    }

    // Convertir ruta local a Unicode para la API de Windows
    wchar_t *wPath = StrAutoToUnicode(pPath, pathLen, NULL);
    free(pPath);
    if (!wPath) {
        SafeRetValLogical(FALSE);
        return;
    }

    // 3. Extraer el segundo parámetro: Datos binarios (Índice 1)
    int dataLen = 0;
    char *pData = GetParamString(parm, 1, &dataLen);
    
    // 4. SOLUCIÓN COMPLETA: Acceso indexado directo gracias al nuevo FoxBridge
    // Accedemos de forma nativa al índice 2 para extraer el entero largo de FoxPro
    DWORD realSize = (DWORD)parm->p[2].val.ev_long;

    // Validación de seguridad para el buffer binario
    if (!pData && realSize > 0) {
        free(wPath);
        SafeRetValLogical(FALSE);
        return;
    }

    // 5. Invocar la función interna de escritura de bytes en Windows
    BOOL success = WriteFileBytesC(wPath, (const BYTE *)pData, realSize);

    // 6. Limpieza estricta de memoria asignada
    free(wPath);
    if (pData) {
        free(pData);
    }

    // 7. Retornar el resultado lógico de forma segura (.T. o .F.)
    SafeRetValLogical(success);
}
*/
// Función auxiliar interna para convertir cadenas ANSI de FoxPro a wchar_t (Unicode)
// Devuelve un buffer asignado dinámicamente que DEBE ser liberado con free()
static wchar_t *FoxStringToWide(ParamBlk *parm, int paramIndex)
{
    // Si el parámetro está vacío o no es una cadena, devolvemos NULL
    if (parm->p[paramIndex].val.ev_length == 0)
        return NULL;

    int length = parm->p[paramIndex].val.ev_length;

    // Bloquear el handle de memoria de FoxPro para leer los datos de forma segura
    _HLock(parm->p[paramIndex].val.ev_handle);
    char *ansiStr = (char *)_HandToPtr(parm->p[paramIndex].val.ev_handle);

    // Calcular el tamaño necesario para el buffer wchar_t
    int wideLength = MultiByteToWideChar(CP_THREAD_ACP, 0, ansiStr, length, NULL, 0);
    wchar_t *wideStr = (wchar_t *)malloc((wideLength + 1) * sizeof(wchar_t));

    if (wideStr)
    {
        MultiByteToWideChar(CP_THREAD_ACP, 0, ansiStr, length, wideStr, wideLength);
        wideStr[wideLength] = L'\0'; // Asegurar el terminador nulo
    }

    // Desbloquear el handle de FoxPro
    _HUnLock(parm->p[paramIndex].val.ev_handle);
    return wideStr;
}

// VFP: = WriteLog(cPath, cMessage)
void CORE_CALL Fox_WriteTextLogWithDate(ParamBlk *parm)
{
    wchar_t *wPath = FoxStringToWide(parm, 0);
    wchar_t *wMessage = FoxStringToWide(parm, 1);

    BOOL result = WriteTextLogWithDate(wPath, wMessage);

    free(wPath);
    free(wMessage);
    _RetLogical(result); // Retorna .T. o .F. a FoxPro
}

// VFP: = WriteIniStr(cPathIni, cSection, cKey, cValue)
void CORE_CALL Fox_WriteIniString(ParamBlk *parm)
{
    wchar_t *wPathIni = FoxStringToWide(parm, 0);
    wchar_t *wSection = FoxStringToWide(parm, 1);
    wchar_t *wKey = FoxStringToWide(parm, 2);
    wchar_t *wValue = FoxStringToWide(parm, 3);

    BOOL result = WriteIniString(wPathIni, wSection, wKey, wValue);

    free(wPathIni);
    free(wSection);
    free(wKey);
    free(wValue);
    _RetLogical(result);
}

// VFP: cValor = ReadIniStr(cPathIni, cSection, cKey, cDefault)
void CORE_CALL Fox_ReadIniString(ParamBlk *parm)
{
    wchar_t *wPathIni = FoxStringToWide(parm, 0);
    wchar_t *wSection = FoxStringToWide(parm, 1);
    wchar_t *wKey = FoxStringToWide(parm, 2);
    wchar_t *wDefault = FoxStringToWide(parm, 3);

    wchar_t wBuffer[1024] = {0};
    BOOL success = ReadIniString(wPathIni, wSection, wKey, wDefault, wBuffer, 1024);

    if (success)
    {
        // Convertir el resultado Unicode de vuelta a ANSI para FoxPro
        int ansiLength = WideCharToMultiByte(CP_ACP, 0, wBuffer, -1, NULL, 0, NULL, NULL);
        char *ansiBuffer = (char *)malloc(ansiLength);

        if (ansiBuffer)
        {
            WideCharToMultiByte(CP_ACP, 0, wBuffer, -1, ansiBuffer, ansiLength, NULL, NULL);
            SafeRetValString(ansiBuffer); // Retorna la cadena a FoxPro
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

    free(wPathIni);
    free(wSection);
    free(wKey);
    free(wDefault);
}

// VFP: = WriteIniInt(cPathIni, cSection, cKey, nValue)
void CORE_CALL Fox_WriteIniInt(ParamBlk *parm)
{
    wchar_t *wPathIni = FoxStringToWide(parm, 0);
    wchar_t *wSection = FoxStringToWide(parm, 1);
    wchar_t *wKey = FoxStringToWide(parm, 2);
    int numberValue = (int)parm->p[3].val.ev_long;

    BOOL result = WriteIniInt(wPathIni, wSection, wKey, numberValue);

    free(wPathIni);
    free(wSection);
    free(wKey);
    _RetLogical(result);
}

// VFP: nValor = ReadIniInt(cPathIni, cSection, cKey, nDefault)
void CORE_CALL Fox_ReadIniInt(ParamBlk *parm)
{
    wchar_t *wPathIni = FoxStringToWide(parm, 0);
    wchar_t *wSection = FoxStringToWide(parm, 1);
    wchar_t *wKey = FoxStringToWide(parm, 2);
    int defaultValue = (int)parm->p[3].val.ev_long;

    int result = ReadIniInt(wPathIni, wSection, wKey, defaultValue);

    free(wPathIni);
    free(wSection);
    free(wKey);
    _RetInt(result, 10); // Retorna el entero a FoxPro
}

// VFP: = DeleteIniKey(cPathIni, cSection, cKey)
void CORE_CALL Fox_DeleteIniKey(ParamBlk *parm)
{
    wchar_t *wPathIni = FoxStringToWide(parm, 0);
    wchar_t *wSection = FoxStringToWide(parm, 1);
    wchar_t *wKey = FoxStringToWide(parm, 2);

    BOOL result = DeleteIniKey(wPathIni, wSection, wKey);

    free(wPathIni);
    free(wSection);
    free(wKey);
    _RetLogical(result);
}

// VFP: = DeleteIniSection(cPathIni, cSection)
void CORE_CALL Fox_DeleteIniSection(ParamBlk *parm)
{
    wchar_t *wPathIni = FoxStringToWide(parm, 0);
    wchar_t *wSection = FoxStringToWide(parm, 1);

    BOOL result = DeleteIniSection(wPathIni, wSection);

    free(wPathIni);
    free(wSection);
    _RetLogical(result);
}

void CORE_CALL Fox_FreeBufferC(ParamBlk *parm)
{
    BYTE *buffer = (BYTE *)parm->p[0].val.ev_long;
    FreeBufferC(buffer);
    _RetLogical(TRUE);
}

// VFP: cRutaCompleta = GETAPPDATAPATH(cAppName, cFileName)
void CORE_CALL Fox_GetPathInAppData(ParamBlk *parm)
{
    // Protección adicional: Validar que FoxPro nos haya enviado al menos 2 parámetros
    if (parm->pCount < 2)
    {
        _RetChar("");
        return;
    }

    wchar_t *wAppName = FoxStringToWide(parm, 0);
    wchar_t *wFileName = FoxStringToWide(parm, 1);

    wchar_t wPathBuffer[MAX_PATH] = {0};

    // Llamada a la función nativa que interactúa con el Shell de Windows
    BOOL success = GetPathInAppData(wPathBuffer, MAX_PATH, wAppName, wFileName);

    free(wAppName);
    free(wFileName);

    if (success)
    {
        // Calcular tamaño de conversión usando el hilo actual
        int ansiLength = WideCharToMultiByte(CP_THREAD_ACP, 0, wPathBuffer, -1, NULL, 0, NULL, NULL);

        if (ansiLength > 0)
        {
            char *ansiBuffer = (char *)malloc(ansiLength);
            if (ansiBuffer)
            {
                WideCharToMultiByte(CP_THREAD_ACP, 0, wPathBuffer, -1, ansiBuffer, ansiLength, NULL, NULL);

                // Usamos tu excelente función robusta para devolver la cadena a VFP
                SafeRetValString(ansiBuffer);
                free(ansiBuffer);
                return;
            }
        }
    }

    _RetChar("");
}

// VFP: cRuta = GETEXEPATH(cFileName)
void CORE_CALL Fox_GetPathInExeFolder(ParamBlk *parm)
{
    wchar_t *wFileName = FoxStringToWide(parm, 0);
    wchar_t wPathBuffer[MAX_PATH] = {0};

    BOOL success = GetPathInExeFolder(wPathBuffer, MAX_PATH, wFileName);
    free(wFileName);

    if (success)
    {
        int ansiLength = WideCharToMultiByte(CP_THREAD_ACP, 0, wPathBuffer, -1, NULL, 0, NULL, NULL);
        char *ansiBuffer = (char *)malloc(ansiLength);
        if (ansiBuffer)
        {
            WideCharToMultiByte(CP_THREAD_ACP, 0, wPathBuffer, -1, ansiBuffer, ansiLength, NULL, NULL);
            SafeRetValString(ansiBuffer);
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
}

// VFP: cRuta = GETLIBPATH(cFileName)
void CORE_CALL Fox_GetPathInLibraryFolder(ParamBlk *parm)
{
    wchar_t *wFileName = FoxStringToWide(parm, 0);
    wchar_t wPathBuffer[MAX_PATH] = {0};

    BOOL success = GetPathInLibraryFolder(wPathBuffer, MAX_PATH, wFileName);
    free(wFileName);

    if (success)
    {
        int ansiLength = WideCharToMultiByte(CP_THREAD_ACP, 0, wPathBuffer, -1, NULL, 0, NULL, NULL);
        char *ansiBuffer = (char *)malloc(ansiLength);
        if (ansiBuffer)
        {
            WideCharToMultiByte(CP_THREAD_ACP, 0, wPathBuffer, -1, ansiBuffer, ansiLength, NULL, NULL);
            SafeRetValString(ansiBuffer);
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
}