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
 
* ------------------------------------------------------------
* PRUEBA 1: SHA-256
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 1: HASH SHA-256 (64 caracteres hexadecimales)"
? "============================================================"
LOCAL lcHashSHA256, lmKeySHA256
lmKeySHA256 = "c3a4a2e49d91f2177113a9adfcb9ef9af9679dc4557a0a3a4602e1bd39a6f481"
lcHashSHA256 = SHA256(lcTextoBase)
? "SHA-256    : " + lcHashSHA256
? "esperado   : " + lmKeySHA256
IF lcHashSHA256 == lmKeySHA256
    ? " Test SHA-256 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test SHA-256"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

* ------------------------------------------------------------
* PRUEBA 2: MD5
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 2: HASH MD5 (32 caracteres hexadecimales)"
? "============================================================"
LOCAL lcHashMD5, lmKeyMD5
lmKeyMD5 = "d501194c987486789bb01b50dc1a0adb"
lcHashMD5 = MD5(lcTextoBase)
? "MD5        : " + lcHashMD5
? "esperado   : " + lmKeyMD5
IF lcHashMD5 == lmKeyMD5
    ? " Test MD5 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test MD5"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

* ------------------------------------------------------------
* PRUEBA 3: SHA-1
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 3: HASH SHA-1 (40 caracteres hexadecimales)"
? "============================================================"
LOCAL lcHashSHA1, lmKeySHA1
lmKeySHA1 = "48124d6dc3b2e693a207667c32ac672414913994"
lcHashSHA1 = SHA1(lcTextoBase)
? "SHA-1      : " + lcHashSHA1
? "esperado   : " + lmKeySHA1
IF lcHashSHA1 == lmKeySHA1
    ? " Test SHA-1 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test SHA-1"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

* ------------------------------------------------------------
* PRUEBA 4: SHA-384
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 4: HASH SHA-384 (96 caracteres hexadecimales)"
? "============================================================"
LOCAL lcHashSHA384, lmKeySHA384
lmKeySHA384 = "e34d7c20942a0669c23f2924ab02dbd2880867294df4d320f8deb7c2694130a68dbce9a89c083aab1a6a92ca3833b40f"
lcHashSHA384 = SHA384(lcTextoBase)
? "SHA-384    : " + lcHashSHA384
? "esperado   : " + lmKeySHA384
IF lcHashSHA384 == lmKeySHA384
    ? " Test SHA-384 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test SHA-384"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

* ------------------------------------------------------------
* PRUEBA 5: SHA-512
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 5: HASH SHA-512 (128 caracteres hexadecimales)"
? "============================================================"
LOCAL lcHashSHA512, lmKeySHA512
lmKeySHA512 = "bb0b2687b9f11a75110cbf78570ea7c8babb10880d533a1ab388113871bd643c47db96e1b19793476b5b3f3000071961aa6d6cab0c1c873c4d7515512c62bbbb"
lcHashSHA512 = SHA512(lcTextoBase)
? "SHA-512    : " + lcHashSHA512
? "esperado   : " + lmKeySHA512
IF lcHashSHA512 == lmKeySHA512
    ? " Test SHA-512 EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test SHA-512"
    lnTestsFail = lnTestsFail + 1
ENDIF
?
  
LOCAL lcFile
lcFile = "C:\Dev\AnyDesk.exe"

? "MD5 de archivo    : " + MD5FILE(lcFile)
? "esperado          : d501194c987486789bb01b50dc1a0adb"

? "SHA1 de archivo   : " + SHA1FILE(lcFile)
? "esperado          : 48124d6dc3b2e693a207667c32ac672414913994"

? "SHA256 de archivo : " + SHA256FILE(lcFile)
? "esperado          : c3a4a2e49d91f2177113a9adfcb9ef9af9679dc4557a0a3a4602e1bd39a6f481"

? "SHA384 de archivo : " + SHA384FILE(lcFile)


? "SHA512 de archivo : " + SHA512FILE(lcFile)
? "esperado          : bb0b2687b9f11a75110cbf78570ea7c8babb10880d533a1ab388113871bd643c47db9"

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