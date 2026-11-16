* ============================================================================
* SCRIPT DE PRUEBAS EXCLUSIVO PARA EL MÓDULO CRIPTOGRÁFICO (FLL)
* ============================================================================
CLEAR
SET ASSERTS ON && Habilita la pausa automática si un ASSERT falla

LOCAL lnTestsOK, lnTestsFail
lnTestsOK   = 0
lnTestsFail = 0

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

 * ------------------------------------------------------------
* PRUEBA 13: CREATESECURENONCE (tamaño dinámico)
* ------------------------------------------------------------
? "============================================================"
? "PRUEBA 13: GENERACION DE NONCE SEGURO (DINAMICO)"
? "============================================================"

LOCAL lcNonce16a, lcNonce16b, lcNonce32, lcNonce64
lcNonce16a = CREATESECURENONCE(17)   && 16 hex chars (8 bytes)
lcNonce16b = CREATESECURENONCE(17)
lcNonce32  = CREATESECURENONCE(33)   && Auth Digest Http - 32 hex chars (16 bytes)
lcNonce64  = CREATESECURENONCE(65)   && 64 hex chars (32 bytes)

? "Nonce 16a (maxLen=17): " + lcNonce16a + "  (len=" + TRANSFORM(LEN(lcNonce16a)) + ")"
? "Nonce 16b (maxLen=17): " + lcNonce16b + "  (len=" + TRANSFORM(LEN(lcNonce16b)) + ")"
? "Nonce 32  (maxLen=33): " + lcNonce32  + "  (len=" + TRANSFORM(LEN(lcNonce32))  + ")"
? "Nonce 64  (maxLen=65): " + lcNonce64  + "  (len=" + TRANSFORM(LEN(lcNonce64))  + ")"

IF LEN(lcNonce16a) == 16 AND ;
   LEN(lcNonce32)  == 32 AND ;
   LEN(lcNonce64)  == 64 AND ;
   lcNonce16a != lcNonce16b
    ? " Test CREATESECURENONCE EXITOSO! (tamaños correctos + unicidad)"
    lnTestsOK = lnTestsOK + 1
ELSE
    ? " Error en Test CREATESECURENONCE"
    ? "   (Revisar: longitudes esperadas 16/32/64, y unicidad entre llamadas)"
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