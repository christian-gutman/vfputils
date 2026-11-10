#include "fox_table.h"

FoxInfo myFoxInfo[] = {

    {"", (FPFI)Core_InternalInit, CALLONLOAD, ""},
    {"", (FPFI)Core_InternalExit, CALLONUNLOAD, ""},

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


};

FoxTable _FoxTable = {
    (FoxTable *)0,
    sizeof(myFoxInfo) / sizeof(FoxInfo),
    myFoxInfo};