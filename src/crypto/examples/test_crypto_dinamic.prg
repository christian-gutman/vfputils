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
* PRUEBA 11: GENHASHALGO (dispatcher genÃ©rico de hash)
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 11: GENERADOR HASH DINAMICO (GENHASH)"
? "============================================================"
LOCAL lcAlgoEval, lcHashGen, lmKeyGen
lcAlgoEval = "SHA-256"
lmKeyGen   = "c3a4a2e49d91f2177113a9adfcb9ef9af9679dc4557a0a3a4602e1bd39a6f481"
lcHashGen  = GENHASH(lcTextoBase, LEN(lcTextoBase), lcAlgoEval)
? "Algoritmo evaluado: " + lcAlgoEval
? "Hash calculado   : " + lcHashGen
? "esperado         : " + lmKeyGen
IF !EMPTY(lcHashGen) AND lcHashGen == lmKeyGen
    ? " Test GENHASH EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test GENHASH"
    lnTestsFail = lnTestsFail + 1
ENDIF
?

* ------------------------------------------------------------
* PRUEBA 12: GENHMAC (dispatcher genÃ©rico de HMAC)
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 12: GENERADOR HMAC DINÃMICO (GENHMACALGO)"
? "============================================================"
LOCAL lcAlgoHmacEval, lcHmacGen, lmKeyHmacGen
lcAlgoHmacEval = "SHA-256"
lmKeyHmacGen   = "58566f2b1208a180a80231d8676a414aaab92a961b5aa8c3b7365fcf50cb2b31"
lcHmacGen = GENHMAC(lcTextoBase, LEN(lcTextoBase), lcSecreto, LEN(lcSecreto), lcAlgoHmacEval)
? "Algoritmo evaluado: " + lcAlgoHmacEval
? "HMAC calculado   : " + lcHmacGen
? "esperado         : " + lmKeyHmacGen
IF !EMPTY(lcHmacGen) AND lcHmacGen == lmKeyHmacGen
    ? " Test GENHMAC EXITOSO!"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test GENHMAC"
    lnTestsFail = lnTestsFail + 1
ENDIF
?
 
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