#ifndef VFP_CRYPTO_H
#define VFP_CRYPTO_H

#include "vfp_lib.h"
#include "vfp_types.h"

#include "core_encoding.h"
#include "core_string.h"
#include "core_crypto.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void CORE_CALL Fox_MD5(ParamBlk *parm);
    void CORE_CALL Fox_SHA1(ParamBlk *parm);
    void CORE_CALL Fox_SHA256(ParamBlk *parm);
    void CORE_CALL Fox_SHA384(ParamBlk *parm);
    void CORE_CALL Fox_SHA512(ParamBlk *parm);
    // VFP: cHashHex = GENHASH(cData, nDataLen, cAlgorithm)
    void CORE_CALL Fox_GenerateHashAlgorithm(ParamBlk *parm);

    void CORE_CALL Fox_SHA1File(ParamBlk *parm);
    void CORE_CALL Fox_SHA256File(ParamBlk *parm);
    void CORE_CALL Fox_SHA512File(ParamBlk *parm);
    void CORE_CALL Fox_MD5File(ParamBlk *parm);

    // VFP: cHashHex = GENFILEHASH(cFilePath, cAlgorithm)
    void CORE_CALL Fox_GenerateFileHashAlgorithm(ParamBlk *parm);

    void CORE_CALL Fox_HMACMD5(ParamBlk *parm);
    void CORE_CALL Fox_HMACSHA1(ParamBlk *parm);
    void CORE_CALL Fox_HMACSHA256(ParamBlk *parm);
    void CORE_CALL Fox_HMACSHA384(ParamBlk *parm);
    void CORE_CALL Fox_HMACSHA512(ParamBlk *parm);
    // VFP: cHashHex = GENHMAC(cData, nDataLen, cAlgorithm)
    void CORE_CALL Fox_GenerateHmacAlgorithm(ParamBlk *parm);

    void CORE_CALL Fox_HMACMD5File(ParamBlk *parm);
    void CORE_CALL Fox_HMACSHA1File(ParamBlk *parm);
    void CORE_CALL Fox_HMACSHA256File(ParamBlk *parm);
    void CORE_CALL Fox_HMACSHA384File(ParamBlk *parm);
    void CORE_CALL Fox_HMACSHA512File(ParamBlk *parm);
    void CORE_CALL Fox_GenerateFileHmacAlgorithm(ParamBlk *parm);

    // VFP: cNonceHex = CREATESECURENONCE(nMaxLen)
    void CORE_CALL Fox_CreateSecureNonce(ParamBlk *parm);

    void CORE_CALL Fox_GenerateHashAlgorithm(ParamBlk *parm);

    // VFP: cBase64 = UNITOUTF8BASE64(cUnicodeInput)
    void CORE_CALL Fox_UnicodeToUtf8Base64(ParamBlk *parm);

    // VFP: cUnicodeText = UTF8BASE64TOUNI(cBase64Input)
    void CORE_CALL Fox_Utf8Base64ToUnicode(ParamBlk *parm);

    // VFP: cData = DecryptString(cText, cKey)
    void CORE_CALL Fox_SecureDecryptString(ParamBlk *parm);
    // VFP: cData = EncryptString(cText, cKey)
    void CORE_CALL Fox_SecureEncryptString(ParamBlk *parm);
#ifdef __cplusplus
}
#endif

#endif // VFP_CRYPTO_H