#include "vfp_strings.h" 

// ============================================================================
// DETECCIÓN DE ENCODING / BOM
// ============================================================================

void CORE_CALL Fox_StrDetectBOM(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input)
    {
        SafeRetValString("UNKNOWN");
        return;
    }

    int startOffset = 0;
    // DetectBOM es estática en core_string.c; reusamos StrDetectEncodingLen
    // para obtener el mismo resultado de detección de BOM + offset.
    int enc = StrDetectEncodingLen(input, len, &startOffset);

    const char *name = "UNKNOWN";
    // Solo reportamos como "detectado por BOM" si el offset es > 0
    // (si offset == 0, pudo haber sido detectado por heurística, no por BOM).
    if (startOffset > 0)
    {
        switch (enc)
        {
        case ENCODING_UTF8:
            name = "UTF-8";
            break;
        case ENCODING_UTF16LE:
            name = "UTF-16LE";
            break;
        case ENCODING_UTF16BE:
            name = "UTF-16BE";
            break;
        default:
            name = "UNKNOWN";
            break;
        }
    }

    // Si hay un 2do parámetro por referencia, guardamos el offset
    if (parm->pCount >= 2 && parm->p[1].loc.l_type != 0)
    {
        SafeStoreReferenceInt(&(parm->p[1].loc), startOffset);
    }

    free(input);
    SafeRetValString(name);
}

void CORE_CALL Fox_StrIsValidUtf8Sequence(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input || len <= 0)
    {
        if (input)
            free(input);
        SafeRetValLogical(0);
        return;
    }

    // Validamos toda la cadena como secuencia UTF-8 estricta usando el mismo
    // criterio que StrDetectEncodingLen (rechaza overlong/surrogates/etc.)
    int contentOffset = 0;
    int enc = StrDetectEncodingLen(input, len, &contentOffset);
    int isValid = (enc == ENCODING_UTF8 || enc == ENCODING_ASCII) ? 1 : 0;

    // charLen del primer carácter (aprox: 1 para ASCII, variable para UTF-8).
    // Como no exponemos IsValidUtf8Sequence (static), reportamos 1 si ASCII,
    // o -1 si no se puede determinar sin acceso al helper interno.
    if (parm->pCount >= 2 && parm->p[1].loc.l_type != 0)
    {
        unsigned char b0 = (unsigned char)input[0];
        int charLen = 1;
        if (b0 > 0x7F)
        {
            if ((b0 & 0xE0) == 0xC0)
                charLen = 2;
            else if ((b0 & 0xF0) == 0xE0)
                charLen = 3;
            else if ((b0 & 0xF8) == 0xF0)
                charLen = 4;
            else
                charLen = -1;
        }
        SafeStoreReferenceInt(&(parm->p[1].loc), charLen);
    }

    free(input);
    SafeRetValLogical(isValid);
}

void CORE_CALL Fox_StrDetectEncodingLen(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input)
    {
        SafeRetValString("UNKNOWN");
        return;
    }

    int contentOffset = 0;
    int enc = StrDetectEncodingLen(input, len, &contentOffset);

    const char *name = "UNKNOWN";
    switch (enc)
    {
    case ENCODING_ASCII:
        name = "ASCII";
        break;
    case ENCODING_UTF8:
        name = "UTF-8";
        break;
    case ENCODING_ANSI:
        name = "ANSI";
        break;
    case ENCODING_UTF16LE:
        name = "UTF-16LE";
        break;
    case ENCODING_UTF16BE:
        name = "UTF-16BE";
        break;
    }

    if (parm->pCount >= 2 && parm->p[1].loc.l_type != 0)
    {
        SafeStoreReferenceInt(&(parm->p[1].loc), contentOffset);
    }

    free(input);
    SafeRetValString(name);
}

// ============================================================================
// TRIM / COMPARACIÓN
// ============================================================================

void CORE_CALL Fox_StrAllTrim(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input)
    {
        SafeRetValString("");
        return;
    }

    StrAllTrim(input); // in-place
    SafeRetValString(input);
    free(input);
}

void CORE_CALL Fox_StrCompare(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValInt(0);
        return;
    }

    char *s1 = GetParamString(parm, 0, NULL);
    char *s2 = GetParamString(parm, 1, NULL);

    int result = 0;
    if (s1 && s2)
        result = StrCompare(s1, s2);

    if (s1)
        free(s1);
    if (s2)
        free(s2);

    SafeRetValInt(result);
}

void CORE_CALL Fox_StrNCompare(ParamBlk *parm)
{
    if (!parm || parm->pCount < 3)
    {
        SafeRetValInt(0);
        return;
    }

    char *s1 = GetParamString(parm, 0, NULL);
    char *s2 = GetParamString(parm, 1, NULL);
    long maxCount = GetParamLong(parm, 2, 0);

    int result = 0;
    if (s1 && s2 && maxCount > 0)
        result = StrNCompare(s1, s2, (size_t)maxCount);

    if (s1)
        free(s1);
    if (s2)
        free(s2);

    SafeRetValInt(result);
}

// ============================================================================
// EXTRACCIÓN (LEFT/RIGHT)
// ============================================================================

void CORE_CALL Fox_StrLeft(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    long n = GetParamLong(parm, 1, 0);

    if (!input || n < 0)
    {
        if (input)
            free(input);
        SafeRetValString("");
        return;
    }

    // Buffer con margen suficiente: nunca se escribe más de strlen(input)+1
    size_t bufSize = (size_t)len + 1;
    char *dest = (char *)malloc(bufSize);
    if (!dest)
    {
        free(input);
        SafeRetValString("");
        return;
    }

    StrLeftSafe(dest, bufSize, input, (size_t)n);
    SafeRetValString(dest);

    free(dest);
    free(input);
}

void CORE_CALL Fox_StrRight(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    long n = GetParamLong(parm, 1, 0);

    if (!input || n < 0)
    {
        if (input)
            free(input);
        SafeRetValString("");
        return;
    }

    // StrRight clampea n a strlen(src) internamente, así que un buffer
    // de len+1 siempre alcanza.
    size_t bufSize = (size_t)len + 1;
    char *dest = (char *)malloc(bufSize);
    if (!dest)
    {
        free(input);
        SafeRetValString("");
        return;
    }

    StrRight(dest, input, (size_t)n);
    SafeRetValString(dest);

    free(dest);
    free(input);
}

// ============================================================================
// PADDING
// ============================================================================

void CORE_CALL Fox_StrPadL(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    char *input = GetParamString(parm, 0, NULL);
    long totalLen = GetParamLong(parm, 1, 0);

    char padChar = ' ';
    if (parm->pCount >= 3)
    {
        char *padStr = GetParamString(parm, 2, NULL);
        if (padStr && padStr[0] != '\0')
            padChar = padStr[0];
        if (padStr)
            free(padStr);
    }

    if (!input || totalLen < 0)
    {
        if (input)
            free(input);
        SafeRetValString("");
        return;
    }

    size_t bufSize = (size_t)totalLen + 1;
    char *dest = (char *)malloc(bufSize);
    if (!dest)
    {
        free(input);
        SafeRetValString("");
        return;
    }

    StrPadLSafe(dest, bufSize, input, (size_t)totalLen, padChar);
    SafeRetValString(dest);

    free(dest);
    free(input);
}

void CORE_CALL Fox_StrPadR(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2)
    {
        SafeRetValString("");
        return;
    }

    char *input = GetParamString(parm, 0, NULL);
    long totalLen = GetParamLong(parm, 1, 0);

    char padChar = ' ';
    if (parm->pCount >= 3)
    {
        char *padStr = GetParamString(parm, 2, NULL);
        if (padStr && padStr[0] != '\0')
            padChar = padStr[0];
        if (padStr)
            free(padStr);
    }

    if (!input || totalLen < 0)
    {
        if (input)
            free(input);
        SafeRetValString("");
        return;
    }

    size_t bufSize = (size_t)totalLen + 1;
    char *dest = (char *)malloc(bufSize);
    if (!dest)
    {
        free(input);
        SafeRetValString("");
        return;
    }

    StrPadRSafe(dest, bufSize, input, (size_t)totalLen, padChar);
    SafeRetValString(dest);

    free(dest);
    free(input);
}

// ============================================================================
// NORMALIZACIÓN / CASE
// ============================================================================

void CORE_CALL Fox_StrNormalize(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input)
    {
        SafeRetValString("");
        return;
    }

    char *dest = (char *)malloc((size_t)len + 1);
    if (!dest)
    {
        free(input);
        SafeRetValString("");
        return;
    }

    StrNormalize(dest, input);
    SafeRetValString(dest);

    free(dest);
    free(input);
}

void CORE_CALL Fox_StrTrimAll(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input)
    {
        SafeRetValString("");
        return;
    }

    char *dest = (char *)malloc((size_t)len + 1);
    if (!dest)
    {
        free(input);
        SafeRetValString("");
        return;
    }

    StrTrimAll(dest, input);
    SafeRetValString(dest);

    free(dest);
    free(input);
}

void CORE_CALL Fox_StrToLower(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input)
    {
        SafeRetValString("");
        return;
    }

    char *dest = (char *)malloc((size_t)len + 1);
    if (!dest)
    {
        free(input);
        SafeRetValString("");
        return;
    }

    StrToLower(dest, input);
    SafeRetValString(dest);

    free(dest);
    free(input);
}

void CORE_CALL Fox_StrToUpper(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input)
    {
        SafeRetValString("");
        return;
    }

    char *dest = (char *)malloc((size_t)len + 1);
    if (!dest)
    {
        free(input);
        SafeRetValString("");
        return;
    }

    StrToUpper(dest, input);
    SafeRetValString(dest);

    free(dest);
    free(input);
}

// ============================================================================
// ESCAPE / UNESCAPE
// ============================================================================

void CORE_CALL Fox_StrEscape(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input || len <= 0)
    {
        if (input)
            free(input);
        SafeRetValString("");
        return;
    }

    // Peor caso: cada byte es una comilla simple -> se duplica el tamaño
    size_t bufSize = (size_t)len * 2 + 1;
    char *dest = (char *)malloc(bufSize);
    if (!dest)
    {
        free(input);
        SafeRetValString("");
        return;
    }

    char *result = StrEscapeOut(input, len, dest, bufSize);
    SafeRetValString(result ? result : "");

    free(dest);
    free(input);
}

void CORE_CALL Fox_StrUnescape(ParamBlk *parm)
{
    int len = 0;
    char *input = GetParamString(parm, 0, &len);
    if (!input || len <= 0)
    {
        if (input)
            free(input);
        SafeRetValString("");
        return;
    }

    char *result = StrUnescape(input, len);
    SafeRetValString(result ? result : "");

    if (result)
        free(result);
    free(input);
}

// ============================================================================
// FORMATO (versión simplificada: solo reemplaza tokens "%s")
// ============================================================================

void CORE_CALL Fox_StrFormat(ParamBlk *parm)
{
    if (!parm || parm->pCount < 1)
    {
        SafeRetValString("");
        return;
    }

    char *formato = GetParamString(parm, 0, NULL);
    if (!formato)
    {
        SafeRetValString("");
        return;
    }

    // Calculamos tamaño de salida: formato + suma de longitudes de args
    // (sobra espacio de sobra, ya que %s se reemplaza 1:1)
    size_t outSize = strlen(formato) + 1;
    int argCount = parm->pCount - 1;
    char **args = NULL;

    if (argCount > 0)
    {
        args = (char **)calloc((size_t)argCount, sizeof(char *));
        if (!args)
        {
            free(formato);
            SafeRetValString("");
            return;
        }
        for (int i = 0; i < argCount; i++)
        {
            args[i] = GetParamString(parm, i + 1, NULL);
            if (args[i])
                outSize += strlen(args[i]);
        }
    }

    char *result = (char *)malloc(outSize);
    if (!result)
    {
        free(formato);
        if (args)
        {
            for (int i = 0; i < argCount; i++)
                if (args[i])
                    free(args[i]);
            free(args);
        }
        SafeRetValString("");
        return;
    }

    // Reemplazo secuencial de "%s"
    const char *src = formato;
    char *dst = result;
    int argIndex = 0;

    while (*src)
    {
        if (src[0] == '%' && src[1] == 's')
        {
            if (argIndex < argCount && args[argIndex])
            {
                size_t alen = strlen(args[argIndex]);
                memcpy(dst, args[argIndex], alen);
                dst += alen;
            }
            argIndex++;
            src += 2;
        }
        else
        {
            *dst++ = *src++;
        }
    }
    *dst = '\0';

    SafeRetValString(result);

    free(result);
    free(formato);
    if (args)
    {
        for (int i = 0; i < argCount; i++)
            if (args[i])
                free(args[i]);
        free(args);
    }
}



// Convierte cualquier encoding a Unicode internamente y retorna en ANSI a FoxPro
// Uso en FoxPro: =StrAutoToUnicode(cText)
void CORE_CALL Fox_StrAutoToUnicode(ParamBlk *parm)
{
    char* input = NULL;
    wchar_t* wResult = NULL;
    char* ansiResult = NULL;
    int len = 0;
    int wLen = 0;
    int ansiLen = 0;

    // Validar parámetros
    if (!parm || parm->pCount < 1) {
        SafeRetValString("");
        return;
    }
    len = parm->p[0].val.ev_length;
    if (len <= 0) {
        SafeRetValString("");
        return;
    }

    input = GetParamString(parm, 0, &len);
    if (!input) {
        SafeRetValString("");
        return;
    } 

    // Convertir a Unicode (detecta encoding automáticamente)
    wResult = StrAutoToUnicode(input, len, &wLen);
    if (!wResult || wLen <= 0) {
        SafeRetValString("");
        return;
    }

    // Convertir Unicode a ANSI para retornar a FoxPro
    ansiResult = UnicodeToAnsiC(wResult, wLen, &ansiLen);
    free(wResult);
    wResult = NULL;

    if (!ansiResult) {
        SafeRetValString("");
        return;
    }

    // Retornar resultado a FoxPro
    SafeRetValString(ansiResult);
    free(ansiResult);
}
void CORE_CALL Fox_StrCleanSpace(ParamBlk *parm)
{    
    char *json = SafeGetString(&(parm->p[0].val));
    if (!json)
    {
        SafeRetValString("");
        return;
    }
    char *result = StrCleanSpaces(json);    
    if (!result)
    {
        SafeRetValString("");
        free(json);
        return;
    }
    SafeRetValString(result);
    free(result);
    free(json);
}
void CORE_CALL Fox_StrRemoveChar(ParamBlk *parm)
{
    if (!parm || parm->pCount < 2) {
        SafeRetValString("");
        return;
    }
    
    char *str = SafeGetString(&(parm->p[0].val));
    char *c_str = SafeGetChar(&(parm->p[1].val)); 
     
    if (!str)
    {
        if (c_str) free(c_str);
        SafeRetValString("");
        return;
    }
 
    if (!c_str) {
        SafeRetValString(str);
        free(str);
        return;
    }

    char c = c_str[0]; 
    free(c_str); 
 
    char *result = StrRemoveChar(str, c);    
    
    if (!result)
    {
        SafeRetValString("");
        free(str);
        return;
    }
     
    SafeRetValString(result);
    free(str); 
}