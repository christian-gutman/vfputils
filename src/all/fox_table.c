#include "fox_table.h"

 

#include "../encoding/vfp_encoding.h"
#include "../strings/vfp_strings.h"
#include "../json/vfp_json.h"
#include "../io/vfp_io.h"
#include "../crypto/vfp_crypto.h"
#include "../html/vfp_html.h"
#include "../request/vfp_request.h"
#include "../request/vfp_req_file.h"
#include "../request/vfp_rest.h"
#include "../system/vfp_system.h"
#include "../certs/vfp_certs.h"


//#include "../google/vfp_google_geopos.h"

static FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},

    // ------------------------------------------------------------------
    // ENCODING - encoding utils (vfp_encodig.c)
    // ------------------------------------------------------------------

    {"STRTOUTF8", (FPFI)Fox_StrToUtf8, 1, "C"},                    // ? STRTOUTF8("Café")
    {"STRTOANSI", (FPFI)Fox_StrToAnsi, 1, "C"},                    // ? STRTOANSI(lcTextoUtf8)

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
    
    // ------------------------------------------------------------------
    // JSON (vfp_json.c) - familia principal: reciben (cJson, cPath)
    // ------------------------------------------------------------------

    {"JSONGETSTRING", (FPFI)Fox_JsonGetString, 2, "CC"},           // ? JSONGETSTRING(lcJson, "nombre")          && "Juan Pérez"
    {"JSONGETDOUBLE", (FPFI)Fox_JsonGetDouble, 2, "CC"},           // ? JSONGETDOUBLE(lcJson, "precio")          && 199.99
    {"JSONGETINT", (FPFI)Fox_JsonGetInt, 2, "CC"},                 // ? JSONGETINT(lcJson, "cantidad")           && 3
    {"JSONGETINT64", (FPFI)Fox_JsonGetInt64, 2, "CC"},             // ? JSONGETINT64(lcJson, "id")               && "12345678901234"
    {"JSONGETBOOL", (FPFI)Fox_JsonGetBool, 2, "CC"},               // ? JSONGETBOOL(lcJson, "activo")            && .T.
    {"JSONHASVALUE", (FPFI)Fox_JsonHasValue, 2, "CC"},             // ? JSONHASVALUE(lcJson, "envio.ciudad")     && .T.
    {"JSONARRAYCOUNT", (FPFI)Fox_JsonArrayCount, 2, "CC"},         // ? JSONARRAYCOUNT(lcJson, "tags")           && 2
    {"JSONGETTYPE", (FPFI)Fox_JsonGetType, 2, "CC"},               // ? JSONGETTYPE(lcJson, "tags")              && "array"
    {"JSONEXTRACTSUBNODE", (FPFI)Fox_JsonExtractSubNode, 2, "CC"}, // lcSub = JSONEXTRACTSUBNODE(lcJson, "envio")
    {"JSONGETANY", (FPFI)Fox_JsonGetAny, 2, "CC"},                 // uVal = JSONGETANY(lcJson, "precio")  && VARTYPE(uVal) = "N"

    // ------------------------------------------------------------------
    // IO (vfp_io.c)
    // ------------------------------------------------------------------

    {"WRITELOG", (FPFI)Fox_WriteTextLogWithDate, 2, "C,C"},

    {"WRITEINISTR", (FPFI)Fox_WriteIniString, 4, "C,C,C,C"},
    {"WRITEINIINT", (FPFI)Fox_WriteIniInt, 4, "C,C,C,I"},

    {"READINISTR", (FPFI)Fox_ReadIniString, 4, "C,C,C,C"},
    {"READINIINT", (FPFI)Fox_ReadIniInt, 4, "C,C,C,I"},

    {"DELETEINIKEY", (FPFI)Fox_DeleteIniKey, 3, "C,C,C"},
    {"DELETEINISECTION", (FPFI)Fox_DeleteIniSection, 2, "C,C"},

    // {"READFILEBYTES",     (FPFI)Fox_ReadFileBytesC,       1, "C"},
    /// {"WRITEFILEBYTES",    (FPFI)Fox_WriteFileBytesC,      3, "C,C,I"},
    // {"FREEBUFFER",        (FPFI)Fox_FreeBufferC,          1, "I"},

    {"GETAPPDATAPATH", (FPFI)Fox_GetPathInAppData, 2, "C,C"},
    {"GETEXEPATH", (FPFI)Fox_GetPathInExeFolder, 1, "C"},
    {"GETLIBPATH", (FPFI)Fox_GetPathInLibraryFolder, 1, "C"},

     // ------------------------------------------------------------------
    // CRYPTO HASHING   (vfp_crypto.c)
    // ------------------------------------------------------------------

    {"MD5", (FPFI)Fox_MD5, 1, "C"},
    {"SHA1", (FPFI)Fox_SHA1, 1, "C"},
    {"SHA256", (FPFI)Fox_SHA256, 1, "C"},
    {"SHA384", (FPFI)Fox_SHA384, 1, "C"},
    {"SHA512", (FPFI)Fox_SHA512, 1, "C"},

    // Hash genérico
    {"GENHASH", (FPFI)Fox_GenerateHashAlgorithm, 3, "C,I,C"},

    // HMAC con nombre
    {"HMACMD5", (FPFI)Fox_HMACMD5, 2, "CC"},
    {"HMACSHA1", (FPFI)Fox_HMACSHA1, 2, "CC"},
    {"HMACSHA256", (FPFI)Fox_HMACSHA256, 2, "CC"},
    {"HMACSHA384", (FPFI)Fox_HMACSHA384, 2, "CC"}, // si agregaste el wrapper SHA384
    {"HMACSHA512", (FPFI)Fox_HMACSHA512, 2, "CC"},

    // HMAC genérico
    {"GENHMAC", (FPFI)Fox_GenerateHmacAlgorithm, 3, "C,I,C"},

    {"MD5FILE", (FPFI)Fox_MD5File, 1, "C"},
    {"SHA1FILE", (FPFI)Fox_SHA1File, 1, "C"},
    {"SHA256FILE", (FPFI)Fox_SHA256File, 1, "C"},
    {"SHA512FILE", (FPFI)Fox_SHA512File, 1, "C"},
    // MD5 SHA1 SHA-256 SHA-384 SHA-512
    {"GENFILEHASH", (FPFI)Fox_GenerateFileHashAlgorithm, 2, "C,C"},

    {"HMACMD5FILE", (FPFI)Fox_HMACMD5File, 2, "C,C"},
    {"HMACSHA1FILE", (FPFI)Fox_HMACSHA1File, 2, "C,C"},
    {"HMACSHA256FILE", (FPFI)Fox_HMACSHA256File, 2, "C,C"},
    {"HMACSHA384FILE", (FPFI)Fox_HMACSHA384File, 2, "C,C"},
    {"HMACSHA512FILE", (FPFI)Fox_HMACSHA512File, 2, "C,C"},
    {"GENFILEHMAC", (FPFI)Fox_GenerateFileHmacAlgorithm, 3, "C,C,C"},

    {"CREATESECURENONCE", (FPFI)Fox_CreateSecureNonce, 1, "I"},

    {"UNITOUTF8BASE64", (FPFI)Fox_UnicodeToUtf8Base64, 1, "C"},
    {"UTF8BASE64TOUNI", (FPFI)Fox_Utf8Base64ToUnicode, 1, "C"},

    // Encrypt/Decrypt con Aes256
    {"ENCRYPTSTRING", (FPFI)Fox_SecureEncryptString, 2, "C,C"}, // cData = ENCRYPTSTRING(cText, cKey)
    {"DECRYPTSTRING", (FPFI)Fox_SecureDecryptString, 2, "C,C"}, // cData = DECRYPTSTRING(cText, cKey)

    // ------------------------------------------------------------------
    // HTML   (vfp_html.c)
    // ------------------------------------------------------------------


    {"ENCODEURICOMPONENT", (FPFI)Fox_EncodeURIComponent, 1, "C"},
    {"DECODEURICOMPONENT", (FPFI)Fox_DecodeURIComponent, 1, "C"},
    {"HTMLENTITIES",(FPFI) Fox_HtmlEntities, 1, "C"},

    {"UTF8TOANSI", (FPFI)Fox_Utf8ToAnsi, 1, "C"},
    {"ANSITOUTF8", (FPFI)Fox_AnsiToUtf8, 1, "C"},

    // ------------------------------------------------------------------
    // WExec   (vfp_request.c)
    // ------------------------------------------------------------------

    {"WConnect", (FPFI)Fox_WConnect, 4, "CCIC"},
    {"WDisconnect", (FPFI)Fox_WDisconnect, 1, "?"},
    {"WRequest", (FPFI)Fox_WRequest, 15, "CCC????????????"},
    {"WCloseRequest", (FPFI)Fox_WCloseRequest, 1, "?"},
    // ------------------------------------------------------------------
    // WExec (vfp_req_file.c)
    // ------------------------------------------------------------------
    {"WDownloadToFile", (FPFI)Fox_WDownloadToFile, 11, "C,C,C,I,L,L,C,C,C,C,R"},
    {"WRequestToFile", (FPFI)Fox_WRequestToFile, 13, "C,C,C,I,L,L,C,C,C,C,C,C,R"},
    {"WDownload", (FPFI)Fox_WDownload, 10, "C,C,I,L,L,C,C,C,C,R"},

    // ------------------------------------------------------------------
    // WExec (vfp_rest.c)
    // ------------------------------------------------------------------

    {"WRestRequest", (FPFI)Fox_WRestRequest, 10, "C,C,C,C,C,C,C,C,R,R"},
    {"WRestGet", (FPFI)Fox_WRestGet, 5, "C,C,C,R,R"},
    {"WRestPost", (FPFI)Fox_WRestPost, 6, "C,C,C,C,R,R"},
    {"WRestPut", (FPFI)Fox_WRestPut, 6, "C,C,C,C,R,R"},
    {"WRestPatch", (FPFI)Fox_WRestPatch, 6, "C,C,C,C,R,R"},
    {"WRestDelete", (FPFI)Fox_WRestDelete, 5, "C,C,C,R,R"},

    // Formularios Web Tradicionales
    {"WRestFormPost", (FPFI)Fox_WRestFormPost, 6, "C,C,C,C,R,R"},
    {"WRestFormPut", (FPFI)Fox_WRestFormPut, 6, "C,C,C,C,R,R"},
    {"WRestFormPatch", (FPFI)Fox_WRestFormPatch, 6, "C,C,C,C,R,R"},

    // Nuevo Multipart Genérico de Archivos
    {"WRestMultipartPost", (FPFI)Fox_WRestMultipartPost, 7, "C,C,C,C,C,R,R"},

    // ------------------------------------------------------------------
    // Google (vfp_google_request.c)
    // ------------------------------------------------------------------
   // {"WGoogleGeoPos", (FPFI)Fox_WGoogleGeoPos, 8, "CCCCCC??"},

    // ------------------------------------------------------------------
    // System (vfp_system.c)
    // ------------------------------------------------------------------

    {"SOLASTERROR", (FPFI)Fox_SoLastError, 2, "RR"},

    // ------------------------------------------------------------------
    // Certs (vfp_certs.c)
    // ------------------------------------------------------------------

    {"CertGetExpiry", (FPFI)Fox_CertGetExpiry, 2, "CC"},
    {"CertSignMsg",   (FPFI)Fox_CertSignMsg,   3, "CCC"},
};

FoxTable _FoxTable = {(FoxTable *)0, sizeof(myFoxInfo) / sizeof(FoxInfo), myFoxInfo};
