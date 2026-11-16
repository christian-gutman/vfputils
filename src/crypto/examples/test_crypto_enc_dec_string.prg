CLEAR
SET ASSERTS ON && Habilita la pausa automática si un ASSERT falla

LOCAL lcLibraryName, cTexto, cClave
lcLibraryName = "vfpcrypto.fll"

cTexto = "Este es un mensaje secreto  con eñes y acentos ó o lo que sea."
cClave = "ClaveUltraSecreta123"
 
IF !FILE(lcLibraryName)
    MESSAGEBOX("Error: No se encuentra " + lcLibraryName + " en el directorio actual.", 16, "FLL Faltante")
    RETURN
ENDIF

SET LIBRARY TO (lcLibraryName) ADDITIVE 


LOCAL lcEncrypt, lcDecrypt
lcEncrypt = ENCRYPTSTRING(cTexto, cClave)
lcDecrypt = DECRYPTSTRING(lcEncrypt, cClave)

?cTexto
?""
?lcEncrypt
?""
?lcDecrypt
?""

IF cTexto == lcDecrypt and len(cTexto)=len(lcDecrypt)
    ? " Test EXITOSO!"
ELSE
    ? " Error en Test "
ENDIF
? 

RELEASE LIBRARY (lcLibraryName) 