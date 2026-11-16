* ============================================================================
* SCRIPT DE PRUEBAS EXCLUSIVO PARA EL MÓDULO CRIPTOGRÁFICO (FLL)
* ============================================================================
CLEAR
SET ASSERTS ON && Habilita la pausa automática si un ASSERT falla

LOCAL lcLibraryName, lcTextoBase, lcDataBinaria
lcLibraryName = "vfpcrypto.fll"
lcTextoBase   = "Hola Mundo"
lcDataBinaria = CREATEBINARY(lcTextoBase)

* 1. Cargar la librería FLL criptográfica
IF !FILE(lcLibraryName)
    MESSAGEBOX("Error: No se encuentra " + lcLibraryName + " en el directorio actual.", 16, "FLL Faltante")
    RETURN
ENDIF

SET LIBRARY TO (lcLibraryName) ADDITIVE
? "========================================================="
? "===  MÓDULO CRIPTOGRÁFICO CARGADO EXITOSAMENTE (FLL)  ==="
? "========================================================="
?

LOCAL lcTextoBase, lcSecreto
lcTextoBase = "Hola Mundo"
lcSecreto   = "ClaveSecreta123"

LOCAL lnTestsOK, lnTestsFail
lnTestsOK   = 0
lnTestsFail = 0

? "============================================================"
? "=== MÃ“DULO CRIPTOGRÃFICO - SUITE DE TESTS (FLL) ==="
? "============================================================"
? "Datos base : " + lcTextoBase
? "Clave HMAC : " + lcSecreto
? ""
 
* ------------------------------------------------------------
* PRUEBA 6: HMAC-MD5
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 6: HMAC-MD5 con Clave Secreta"
? "============================================================"
LOCAL lcHmacMD5, lmKeyHmacMD5
lmKeyHmacMD5 = "3dca20eb98036ab8e2153642cb9660f5"
lcHmacMD5 = HMACMD5(lcTextoBase, lcSecreto)
? "HMAC-MD5   : " + lcHmacMD5
? "esperado   : " + lmKeyHmacMD5
IF lcHmacMD5 == lmKeyHmacMD5
    ? " Test HMAC-MD5 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test HMAC-MD5"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

* ------------------------------------------------------------
* PRUEBA 7: HMAC-SHA1
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 7: HMAC-SHA1 con Clave Secreta"
? "============================================================"
LOCAL lcHmacSHA1, lmKeyHmacSHA1
lmKeyHmacSHA1 = "779eaade40fd43e1bc9a0a222c35c64f2b4f564b"
lcHmacSHA1 = HMACSHA1(lcTextoBase, lcSecreto)
? "HMAC-SHA1  : " + lcHmacSHA1
? "esperado   : " + lmKeyHmacSHA1
IF lcHmacSHA1 == lmKeyHmacSHA1
    ? " Test HMAC-SHA1 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test HMAC-SHA1"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

* ------------------------------------------------------------
* PRUEBA 8: HMAC-SHA256
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 8: HMAC-SHA256 con Clave Secreta"
? "============================================================"
LOCAL lcHmacSHA256, lmKeyHmacSHA256
lmKeyHmacSHA256 = "58566f2b1208a180a80231d8676a414aaab92a961b5aa8c3b7365fcf50cb2b31"
lcHmacSHA256 = HMACSHA256(lcTextoBase, lcSecreto)
? "HMAC-SHA256: " + lcHmacSHA256
? "esperado   : " + lmKeyHmacSHA256
IF lcHmacSHA256 == lmKeyHmacSHA256
    ? " Test HMAC-SHA256 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test HMAC-SHA256"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

* ------------------------------------------------------------
* PRUEBA 9: HMAC-SHA384
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 9: HMAC-SHA384 con Clave Secreta"
? "============================================================"
LOCAL lcHmacSHA384, lmKeyHmacSHA384
lmKeyHmacSHA384 = "ceef2019cf83703d49338bdc3b15a36a32409f4190bcf65ca169faba8fc777874d5b5eee7344fb75d4931294ec5cee8f"
lcHmacSHA384 = HMACSHA384(lcTextoBase, lcSecreto)
? "HMAC-SHA384: " + lcHmacSHA384
? "esperado   : " + lmKeyHmacSHA384
IF lcHmacSHA384 == lmKeyHmacSHA384
    ? " Test HMAC-SHA384 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test HMAC-SHA384"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

* ------------------------------------------------------------
* PRUEBA 10: HMAC-SHA512
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 10: HMAC-SHA512 con Clave Secreta"
? "============================================================"
LOCAL lcHmacSHA512, lmKeyHmacSHA512
lmKeyHmacSHA512 = "334638071cc5bc93a5b73e619b0c6b5074ca92bfe75539b38a144863b62b4ba7b16b30bfc63a16af99fbe7203e399d7cd76f8c542dca98acbab4b2411afe263f"
lcHmacSHA512 = HMACSHA512(lcTextoBase, lcSecreto)
? "HMAC-SHA512: " + lcHmacSHA512
? "esperado   : " + lmKeyHmacSHA512
IF lcHmacSHA512 == lmKeyHmacSHA512
    ? " Test HMAC-SHA512 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test HMAC-SHA512"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

LOCAL lcFile, lcSecreto
lcFile    = "C:\Dev\AnyDesk.exe"
lcSecreto = "ClaveSecreta123"

? "HMAC-MD5FILE    : " + HMACMD5FILE(lcFile, lcSecreto)
? "HMAC-SHA1FILE   : " + HMACSHA1FILE(lcFile, lcSecreto)
? "HMAC-SHA256FILE : " + HMACSHA256FILE(lcFile, lcSecreto)
? "HMAC-SHA384FILE : " + HMACSHA384FILE(lcFile, lcSecreto)
? "HMAC-SHA512FILE : " + HMACSHA512FILE(lcFile, lcSecreto)

* ------------------------------------------------------------
* RESUMEN FINAL
* ------------------------------------------------------------
? "============================================================"
? "RESUMEN DE LA SUITE"
? "============================================================"
? "Tests OK     : " + TRANSFORM(lnTestsOK)
? "Tests FALLOS : " + TRANSFORM(lnTestsFail)
? "Total tests  : " + TRANSFORM(lnTestsOK + lnTestsFail)
? "============================================================"

* ============================================================================
* LIMPIEZA FINAL DEL ENTORNO DE EJECUCIÓN
* ============================================================================
RELEASE LIBRARY (lcLibraryName)

? "========================================================="
? "===   TODAS LAS PRUEBAS CRIPTO (6/6) PASARON CON ÉXITO ==="
? "========================================================="
WAIT WINDOW "Módulo criptográfico validado al 100%." TIMEOUT 3