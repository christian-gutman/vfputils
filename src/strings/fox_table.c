#include "fox_table.h"

static FoxInfo myFoxInfo[] = {
    
    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},

    // ------------------------------------------------------------------
    // STRINGS - encoding / conversión (vfp_strings.c)
    // ------------------------------------------------------------------
    {"STRDETECTENCODING", (FPFI)Fox_StrDetectEncodingLen, 1, "C"}, // lcEnc = STRDETECTENCODINGLEN(lcTexto, @lnOffset)
    {"STRAUTOUNICODE", (FPFI)Fox_StrAutoToUnicode, 1, "C"},     // ? STRAUTOUNICODE(lcTexto)

    // ------------------------------------------------------------------
    // STRINGS - core utils (vfp_strings_core.c)
    // ------------------------------------------------------------------
    {"STRDETECTBOM", (FPFI)Fox_StrDetectBOM, 1, "C"},                 // lcEnc = STRDETECTBOM(lcTexto, @lnOffset)
    {"STRISVALIDUTF8SEQ", (FPFI)Fox_StrIsValidUtf8Sequence, 1, "C"},  // ? STRISVALIDUTF8SEQ(lcTexto, @lnCharLen)   && .T./.F.
    {"STRDETECTENCODINGLEN", (FPFI)Fox_StrDetectEncodingLen, 1, "C"}, // lcEnc = STRDETECTENCODINGLEN(lcTexto, @lnOffset)
    {"STRALLTRIM", (FPFI)Fox_StrAllTrim, 1, "C"},                     // ? STRALLTRIM("   hola   ")                 && "hola"
    {"STRCOMPARE", (FPFI)Fox_StrCompare, 2, "CC"},                    // ? STRCOMPARE("abc", "abd")                 && -1
    {"STRNCOMPARE", (FPFI)Fox_StrNCompare, 3, "CCN"},                 // ? STRNCOMPARE("abcXYZ", "abcQQQ", 3)      && 0
    {"STRLEFT", (FPFI)Fox_StrLeft, 2, "CN"},                          // ? STRLEFT("Visual FoxPro", 6)             && "Visual"
    {"STRRIGHT", (FPFI)Fox_StrRight, 2, "CN"},                        // ? STRRIGHT("Visual FoxPro", 6)            && "FoxPro"
    {"STRPADL", (FPFI)Fox_StrPadL, 2, "CN"},                          // ? STRPADL("42", 5, "0")                   && "00042"
    {"STRPADR", (FPFI)Fox_StrPadR, 2, "CN"},                          // ? STRPADR("42", 5, "0")                   && "42000"
    {"STRNORMALIZE", (FPFI)Fox_StrNormalize, 1, "C"},                 // ? STRNORMALIZE("   HOLA   ")              && "hola"
    {"STRTRIMALL", (FPFI)Fox_StrTrimAll, 1, "C"},                     // ? STRTRIMALL("   texto   ")               && "texto"
    {"STRTOLOWER", (FPFI)Fox_StrToLower, 1, "C"},                     // ? STRTOLOWER("HOLA")                      && "hola"
    {"STRTOUPPER", (FPFI)Fox_StrToUpper, 1, "C"},                     // ? STRTOUPPER("hola")                      && "HOLA"
    {"STRESCAPE", (FPFI)Fox_StrEscape, 1, "C"},                       // ? STRESCAPE("O'Brien")                    && "O''Brien"
    {"STRUNESCAPE", (FPFI)Fox_StrUnescape, 1, "C"},                   // ? STRUNESCAPE("O''Brien")                 && "O'Brien"
    {"STRFORMAT", (FPFI)Fox_StrFormat, 1, "C"},                       // ? STRFORMAT("Hola %s, tenés %s msjs", "Juan", "5")
    {"STRREMOVECHAR", (FPFI)Fox_StrRemoveChar, 2, "CC"},              // ? lctext= StrRemoveChar("Hola efwf Z U Z", "Z")
    {"STRCLEANSPACE", (FPFI)Fox_StrCleanSpace, 1, "C"},               // cTextClean =STRCLEANSPACE(cText)  
    
};

FoxTable _FoxTable = {(FoxTable *)0, sizeof(myFoxInfo) / sizeof(FoxInfo), myFoxInfo};
