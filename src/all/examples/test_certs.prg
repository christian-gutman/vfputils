*----------------------------------------------------------------------
* Programa de prueba para Lectura y Firma de Certificados con FLL (ARCA / AFIP)
*----------------------------------------------------------------------
CLEAR

*-- Cargar la FLL
IF !FILE("vfputils.fll")
    ? "Archivo 'vfputils.fll' no encontrado."
    ? "Asegúrese de compilar la FLL primero a 32 bits (x86) con soporte Crypto."
    RETURN
ENDIF

SET LIBRARY TO vfputils.fll ADDITIVE

? "========================================================="
? "PRUEBA 1: LECTURA Y VALIDACIÓN DE VENCIMIENTO DE CERTIFICADO"
? "========================================================="

*-- Ajustar las rutas a sus archivos reales
LOCAL lcCertFile, lcPassword, lcExpiry
lcCertFile = "certs/mi_certificado.pfx"  && O mi_certificado.crt / .cer
lcPassword = "MiPassword123"            && Dejar vacío "" si no tiene password

IF FILE(lcCertFile)
    *-- Obtener fecha de vencimiento desde la FLL
    lcExpiry = CertGetExpiry(lcCertFile, lcPassword)
    
    IF ATC("ERROR", lcExpiry) = 0
        ? " Certificado leído correctamente."
        ? "   Fecha de Vencimiento: " + lcExpiry
        
        *-- Validar si ya venció comparando con la fecha actual de VFP
        LOCAL ltExpiry, ltNow
        ltExpiry = CTOT(STRTRAN(lcExpiry, "-", "/")) && Convertir a Datetime
        ltNow = DATETIME()
        
        IF ltExpiry < ltNow
            ? " ADVERTENCIA: ¡El certificado ya ha vencido!"
            ? "   Venció hace: " + TRANSFORM(ROUND((ltNow - ltExpiry) / 86400, 1)) + " días."
        ELSE
            ? " El certificado está VIGENTE."
            ? "   Vence en: " + TRANSFORM(ROUND((ltExpiry - ltNow) / 86400, 1)) + " días."
        ENDIF
    ELSE
        ? " Error al leer certificado: " + lcExpiry
    ENDIF
ELSE
    ? " Archivo '" + lcCertFile + "' no encontrado para probar."
    ? "   (Genere o copie un archivo .pfx o .crt en la carpeta para realizar la prueba real)."
ENDIF


? ""
? "========================================================="
? "PRUEBA 2: FIRMA DE XML (TRA) PARA ACCESO A ARCA (WSAA)"
? "========================================================="

*-- Crear un Ticket de Requerimiento de Acceso (TRA) XML de ejemplo para AFIP
LOCAL lcXmlTRA, lcSignedB64
lcXmlTRA = '<?xml version="1.0" encoding="UTF-8"?>' + CHR(10) + ;
           '<loginTicketRequest version="1.0">' + CHR(10) + ;
           '  <header>' + CHR(10) + ;
           '    <uniqueId>' + ALLTRIM(STR(VAL(SYS(2007, TIME())))) + '</uniqueId>' + CHR(10) + ;
           '    <generationTime>2026-05-24T21:40:00-03:00</generationTime>' + CHR(10) + ;
           '    <expirationTime>2026-05-24T21:50:00-03:00</expirationTime>' + CHR(10) + ;
           '  </header>' + CHR(10) + ;
           '  <service>wsfe</service>' + CHR(10) + ;
           '</loginTicketRequest>'

? "XML Original a firmar:"
? lcXmlTRA
? "---------------------------------------------------------"

IF FILE(lcCertFile) AND (LOWER(JUSTEXT(lcCertFile)) == "pfx")
    ? "Firmando XML usando clave privada en el PFX..."
    lcSignedB64 = CertSignMsg(lcXmlTRA, lcCertFile, lcPassword)
    
    IF !EMPTY(lcSignedB64) and ATC("ERROR", lcSignedB64) = 0
        ? " XML firmado y codificado en Base64 con éxito!"
        ? "Firma CMS (Base64) (Primeros 150 caracteres):"
        ? SUBSTR(lcSignedB64, 1, 150) + "..."
        ? "---------------------------------------------------------"
        ? "Esta firma está lista para colocarse directamente en la etiqueta <in0>"
        ? "del servicio loginCms de WSAA."
    ELSE
        ? " Error de Firma. Detalle: " + lcSignedB64
    ENDIF
ELSE
    ? " Requiere un archivo .pfx con clave privada para probar la firma de mensajes."
ENDIF

*-- Liberar la biblioteca
RELEASE LIBRARY vfputils.fll
? ""
? "Pruebas finalizadas."
RETURN

   ? "✅ OK"
   ? "💚 OK"
   ? "⚠️ ADVERTENCIA"
   ? "❌ ERROR"
   ? "ℹ️ INFO" 