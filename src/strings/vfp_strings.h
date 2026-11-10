#ifndef VFP_STRINGS_H
#define VFP_STRINGS_H
 
 
#include "vfp_lib.h"
#include "vfp_types.h"
#include "core_encoding.h"
#include "core_string.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // cText = StrRemoveChar("texto","x")
    //StrRemoveChar("texto","x")
    void CORE_CALL Fox_StrRemoveChar(ParamBlk *parm);

    // cTextClean =STRCLEANSPACE(cJson)
    void CORE_CALL Fox_StrCleanSpace(ParamBlk *parm);
    // ============================================================================
    // DETECCIÓN DE ENCODING / BOM
    // ============================================================================

    // =StrDetectBOM(cText [, @nOffset])
    // Devuelve el nombre del encoding detectado por BOM ("UTF-8", "UTF-16LE",
    // "UTF-16BE", "UNKNOWN" si no hay BOM). Si se pasa el 2do parámetro por
    // referencia, se almacena ahí el offset de contenido (bytes que ocupa el BOM).
    void CORE_CALL Fox_StrDetectBOM(ParamBlk *parm);

    // =StrIsValidUtf8Sequence(cText [, @nCharLen])
    // Valida si cText (completo, desde el byte 0) es una secuencia UTF-8 válida
    // y estricta (rechaza overlong encodings, surrogates, codepoints fuera de
    // rango). Devuelve .T./.F. Si se pasa el 2do parámetro por referencia, se
    // almacena ahí la longitud en bytes del primer carácter.
    void CORE_CALL Fox_StrIsValidUtf8Sequence(ParamBlk *parm);

    // =StrDetectEncodingLen(cText [, @nOffset])
    // Igual que StrDetectEncoding pero usa la longitud real del buffer VFP
    // (soporta binarios con nulos embebidos) en vez de asumir null-terminated.
    // Si se pasa el 2do parámetro por referencia, se almacena el offset de BOM.
    void CORE_CALL Fox_StrDetectEncodingLen(ParamBlk *parm);

    // =StrDetectEncoding(cText)  [ya existía en vfp_strings.c]
    // void CORE_CALL Fox_StrDetectEncoding(ParamBlk *parm);

    // ============================================================================
    // CONVERSIÓN DE ENCODING
    // ----------------------------------------------------------------------------
    // Fox_StrAutoToUnicode / Fox_StrAutoToAnsi / Fox_StrAutoToUtf8 ya existen en
    // vfp_strings.c (como Fox_StrAutoToUnicode, Fox_StrToAnsi, Fox_StrToUtf8).
    // No se duplican acá.
    // ============================================================================

    // ============================================================================
    // TRIM / COMPARACIÓN
    // ============================================================================

    // =StrAllTrim(cText)
    void CORE_CALL Fox_StrAllTrim(ParamBlk *parm);

    // =StrCompare(cStr1, cStr2)
    void CORE_CALL Fox_StrCompare(ParamBlk *parm);

    // =StrNCompare(cStr1, cStr2, nMaxCount)
    void CORE_CALL Fox_StrNCompare(ParamBlk *parm);

    // ============================================================================
    // EXTRACCIÓN (LEFT/RIGHT)
    // ============================================================================

    // =StrLeft(cText, nChars)
    void CORE_CALL Fox_StrLeft(ParamBlk *parm);

    // =StrRight(cText, nChars)
    void CORE_CALL Fox_StrRight(ParamBlk *parm);

    // ============================================================================
    // PADDING
    // ============================================================================

    // =StrPadL(cText, nTotalLen [, cPadChar])   cPadChar default = " "
    void CORE_CALL Fox_StrPadL(ParamBlk *parm);

    // =StrPadR(cText, nTotalLen [, cPadChar])   cPadChar default = " "
    void CORE_CALL Fox_StrPadR(ParamBlk *parm);

    // ============================================================================
    // NORMALIZACIÓN / CASE
    // ============================================================================

    // =StrNormalize(cText)   (trim + lowercase)
    void CORE_CALL Fox_StrNormalize(ParamBlk *parm);

    // =StrTrimAll(cText)
    void CORE_CALL Fox_StrTrimAll(ParamBlk *parm);

    // =StrToLower(cText)
    void CORE_CALL Fox_StrToLower(ParamBlk *parm);

    // =StrToUpper(cText)
    void CORE_CALL Fox_StrToUpper(ParamBlk *parm);

    // ============================================================================
    // ESCAPE / UNESCAPE (comillas simples para SQL embebido)
    // ============================================================================

    // =StrEscape(cText)
    void CORE_CALL Fox_StrEscape(ParamBlk *parm);

    // =StrUnescape(cText)
    void CORE_CALL Fox_StrUnescape(ParamBlk *parm);

    // ============================================================================
    // FORMATO
    // ----------------------------------------------------------------------------
    // Versión simplificada: reemplaza tokens "%s" en cFormato, en orden, por los
    // parámetros string adicionales. No soporta %d/%f/etc. (Str_Core_Format de
    // core_string.h es variádico en C y no se puede exportar tal cual a VFP).
    // Uso: =StrFormat("Hola %s, tenés %s mensajes", "Juan", "5")
    // ============================================================================
    void CORE_CALL Fox_StrFormat(ParamBlk *parm);


    void CORE_CALL Fox_StrAutoToUnicode(ParamBlk *parm);

#ifdef __cplusplus
}
#endif

#endif // VFP_STRINGS_H
