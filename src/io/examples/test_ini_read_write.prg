CLEAR
SET ASSERTS ON 

LOCAL lcLibraryName, lcAppName
lcLibraryName = "vfpio.fll"
lcAppName     = "MyPowerApps"

IF !FILE(lcLibraryName)
    MESSAGEBOX("Error crítico: No se encuentra " + lcLibraryName + " en el directorio actual.", 16, "FLL Faltante")
    RETURN
ENDIF

SET LIBRARY TO (lcLibraryName) ADDITIVE
? "=== LIBRERÍA " + UPPER(lcLibraryName) + " CARGADA EXITOSAMENTE ==="
?

* ============================================================================
* PRUEBA 1: DESCUBRIMIENTO DINÁMICO DE RUTAS
* ============================================================================
? "--- 1. Probando Funciones de Rutas ---"

LOCAL lcPath
lcPath        = GETLIBPATH("Configuracion.ini") 
 
? "Ruta calculada junto a la FLL:    " + lcPath 

ASSERT !EMPTY(lcPath) MESSAGE "Fallo en GETLIBPATH"

* ============================================================================
* PRUEBA 2: MANEJO COMPLETO DE ARCHIVOS INI (Lector, Escritor)
* ============================================================================
? "--- 2. Probando Operaciones de Archivos .INI ---"

* A) Escritura de Datos Mixtos

LOCAL llOkStr1, llOkStr2, llOkInt1, llOkInt2
llOkStr1 = WRITEINISTR(lcPath, "ServidorBD", "Host", "192.168.1.100")

* Soportando caracteres extendidos
llOkStr2 = WRITEINISTR(lcPath, "ServidorBD", "Instancia", "FOX_PROD_ÑÁ") 

llOkInt1 = WRITEINIINT(lcPath, "ServidorBD", "Puerto", 5432)
llOkInt2 = WRITEINIINT(lcPath, "Seguridad",  "NivelAcceso", 3)

llOkStr2 = WRITEINISTR(lcPath, "ServidorBD", "Instancia", "FOX_PROD_ÑÁ") 
llOkInt1 = WRITEINIINT(lcPath, "ServidorBD", "Puerto", 5432)
llOkInt2 = WRITEINIINT(lcPath, "Seguridad",  "NivelAcceso", 3)

ASSERT llOkStr1 AND llOkStr2 AND llOkInt1 AND llOkInt2 MESSAGE "Fallo en las escrituras del archivo .INI"

* B) Lectura de Datos Existentes y Valores por Defecto
LOCAL lcHost, lcInstancia, lnPuerto, lnTimeoutDefecto
lcHost             = READINISTR(lcPath, "ServidorBD", "Host", "127.0.0.1")
lcInstancia        = READINISTR(lcPath, "ServidorBD", "Instancia", "DEFAULT")
lnPuerto           = READINIINT(lcPath, "ServidorBD", "Puerto", 8080)
lnTimeoutDefecto   = READINIINT(lcPath, "ServidorBD", "Timeout", 45) && No existe, debe traer 45

? "  [INI LEÍDO] Host:      " + lcHost
? "  [INI LEÍDO] Instancia: " + lcInstancia
? "  [INI LEÍDO] Puerto:    " + STR(lnPuerto)
? "  [INI LEÍDO] Timeout:   " + STR(lnTimeoutDefecto)

ASSERT lcHost == "192.168.1.100"       MESSAGE "Host leído incorrecto"
ASSERT lcInstancia == "FOX_PROD_ÑÁ"    MESSAGE "Instancia Unicode leída incorrectamente"
ASSERT lnPuerto == 5432                MESSAGE "Puerto leído incorrecto"
ASSERT lnTimeoutDefecto == 45          MESSAGE "El valor por defecto del entero falló"

* ============================================================================
* LIMPIEZA FINAL DEL ENTORNO
* ============================================================================
RELEASE LIBRARY (lcLibraryName)

? "=== TODAS LAS PRUEBAS FINALIZADAS CON ÉXITO SIN ERRORES ==="
WAIT WINDOW "Pruebas completadas. Presione una tecla..." TIMEOUT 3
