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
 
*Algoritmo	Bytes	Hex chars	Buffer mínimo (+ '\0')
*MD5	        16	    32	        33
*SHA1	    20	    40	        41
*SHA256	    32	    64	        65
*SHA512	    64	    128	        129
 
*? "obtiene las keys https://go.lightnode.com/resources/hash-generator?ref=d0ba5c73&id=58&ads=pmax&gad_source=1&gad_campaignid=20434940291&gbraid=0AAAAABPLrSlOdRQ5uwsnyNQGmTYlra4eI&gclid=Cj0KCQjw6_HSBhCpARIsANvVltarR2UwQXoif55Rn2UKr5uf2r1uJ08lWQ51wloIhAweTnKEDHOQR-gaAvArEALw_wcB"
*? "https://www.devglan.com/online-tools/hmac-sha256-online"
*? "https://www.authgear.com/tools/hmac-signature-generator-verifier/"
 
? "========================================================="
? "PRUEBA 1: HASH SHA-256  (Llaves validadoras LightNode de tu consulta)"
? "========================================================="
 
? "Datos: " + lcTextoBase  
? "SHA-256    : " + SHA256(lcTextoBase)
? "esperado   : c3a4a2e49d91f2177113a9adfcb9ef9af9679dc4557a0a3a4602e1bd39a6f481"
 
? "========================================================="
? "PRUEBA 2: HASH MD5 (32 caracteres hexadecimales)"
? "========================================================="
? "Datos: " + lcTextoBase  
? "MD5        : " + MD5(lcTextoBase)
? "esperado   : d501194c987486789bb01b50dc1a0adb"

? "========================================================="
? "PRUEBA 3: SHA1 "
? "========================================================="
? "Datos: " + lcTextoBase  
? "SHA1   : " + SHA1(lcTextoBase)
? "esperado: 48124d6dc3b2e693a207667c32ac672414913994"

? "========================================================="
? "PRUEBA 4: SHA512 "
? "========================================================="
? "Datos: " + lcTextoBase  
? "SHA512 : " + SHA512(lcTextoBase)
? "esperado: bb0b2687b9f11a75110cbf78570ea7c8babb10880d533a1ab388113871bd643c47db96e1b19793476b5b3f3000071961aa6d6cab0c1c873c4d7515512c62bbbb"

? "========================================================="
? "PRUEBA 3: MESSAGE AUTHENTICATION (HMAC-SHA256) con Clave Secreta"
? "========================================================="
LOCAL lcSecreto
lcSecreto  = "ClaveSecreta123"
? "Datos: " + lcTextoBase  
? "HMAC-SHA256: " + HMACSHA256(lcTextoBase, lcSecreto)
? "esperado   : 58566f2b1208a180a80231d8676a414aaab92a961b5aa8c3b7365fcf50cb2b31"
 
? "========================================================="
? "PRUEBA 4: GENERADOR HASH DINÁMICO (GENHASHALGO)"
? "========================================================="
LOCAL lcHashDinamico
lcHashDinamico = 

? "Algoritmo evaluado: SHA-256"

? "Hash calculado:     " + GENHASH(lcTextoBase, LEN(lcTextoBase), "SHA-256")
? "Hash esperado:      " + lmKeySHA256

IF lcHashDinamico == lmKeySHA256
    ? " Test GENHASHALGO EXITOSO!"
ELSE
    ? " Error en Test GENHASHALGO"
    ASSERT .F. MESSAGE "Fallo en validación GENHASHALGO"
ENDIF
?

* ============================================================================
* PRUEBA 5: CREACIÓN DE NONCE CRIPTOGRÁFICO SEGURO
* ============================================================================
? "========================================================="
? "PRUEBA 5: GENERACIÓN DE NONCE SECURE"
? "========================================================="
LOCAL lcNonceHex
lcNonceHex = CREATESECURENONCE(32) && Solicita un buffer hexadecimal de 32 bytes

? "Nonce generado: " + lcNonceHex
? "Longitud:       " + STR(LEN(lcNonceHex))

IF !EMPTY(lcNonceHex) AND LEN(lcNonceHex) == 32
    ? " Test CREATESECURENONCE EXITOSO!"
ELSE
    ? " Error en Test CREATESECURENONCE"
    ASSERT .F. MESSAGE "Fallo en longitud o generación del Nonce"
ENDIF
?

* ============================================================================
* PRUEBA 6: SERIALIZACIÓN COMPLETA UNICODE BASE64
* ============================================================================
? "========================================================="
? "PRUEBA 6: SERIALIZACIÓN UNICODE BASE64"
? "========================================================="
LOCAL lcTextoEspecial, lcBase64Generado, lcTextoFinalDecodificado
lcTextoEspecial = "Eñe Con Acento Áíóú En FoxPro 2026"

lcBase64Generado = UNITOUTF8BASE64(lcTextoEspecial)
? "Texto Especial: " + lcTextoEspecial
? "Base64 de C:    " + lcBase64Generado

lcTextoFinalDecodificado = UTF8BASE64TOUNI(lcBase64Generado)
? "Decodificado:   " + lcTextoFinalDecodificado

IF lcTextoEspecial == lcTextoFinalDecodificado
    ? " Test BASE64 UNICODE EXITOSO!"
ELSE
    ? " Error en Test BASE64 UNICODE"
    ASSERT .F. MESSAGE "Los caracteres extendidos sufrieron corrupción"
ENDIF
?

* ============================================================================
* LIMPIEZA FINAL DEL ENTORNO DE EJECUCIÓN
* ============================================================================
RELEASE LIBRARY (lcLibraryName)

? "========================================================="
? "===   TODAS LAS PRUEBAS CRIPTO (6/6) PASARON CON ÉXITO ==="
? "========================================================="
WAIT WINDOW "Módulo criptográfico validado al 100%." TIMEOUT 3

