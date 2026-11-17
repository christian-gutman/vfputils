* ============================================================================
* SCRIPT DE PRUEBAS UNITARIAS COMPLETO PARA LA FLL
* ============================================================================
CLEAR
SET ASSERTS ON && Permite pausar el código si una validación crítica falla

LOCAL lcLibraryName, lcAppName
lcLibraryName = "vfpio.fll"
lcAppName     = "MyPowerApps"

* 1. Cargar la librería FLL de forma segura
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
* PRUEBA 3: MANEJO COMPLETO DE ARCHIVOS INI (Borrado)
* ============================================================================

* C) Lectura de Datos Existentes y Valores por Defecto
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

* C) Eliminación de Datos (Claves y Secciones)
LOCAL llDelKey, llDelSec, lnAccesoBorrado
llDelKey = DELETEINIKEY(lcPath, "Seguridad", "NivelAcceso")
lnAccesoBorrado = READINIINT(lcPath, "Seguridad", "NivelAcceso", -1) && Debe devolver -1 al no existir

ASSERT llDelKey AND (lnAccesoBorrado == -1) MESSAGE "Fallo al eliminar la clave INI"

llDelSec = DELETEINISECTION(lcPath, "ServidorBD")
lcHostBorrado = READINISTR(lcPath, "ServidorBD", "Host", "ELIMINADO")

ASSERT llDelSec AND (lcHostBorrado == "ELIMINADO") MESSAGE "Fallo al eliminar la sección INI completa"
? "  [INI] Claves y secciones eliminadas correctamente."
?

 
* ============================================================================
* LIMPIEZA FINAL DEL ENTORNO
* ============================================================================
RELEASE LIBRARY (lcLibraryName)

? "=== TODAS LAS PRUEBAS FINALIZADAS CON ÉXITO SIN ERRORES ==="
WAIT WINDOW "Pruebas completadas. Presione una tecla..." TIMEOUT 3
