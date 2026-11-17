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

LOCAL lcPathExe, lcPathLib, lcPathAppData
lcPathExe     = GETEXEPATH("config_global.ini")
lcPathLib     = GETLIBPATH("debug_libreria.log")
lcPathAppData = GETAPPDATAPATH(lcAppName, "usuario_local.ini")

? "Ruta calculada junto al EXE:      " + lcPathExe
? "Ruta calculada junto a la FLL:    " + lcPathLib
? "Ruta calculada segura en AppData: " + lcPathAppData
?
ASSERT !EMPTY(lcPathExe)     MESSAGE "Fallo en GETEXEPATH"
ASSERT !EMPTY(lcPathLib)     MESSAGE "Fallo en GETLIBPATH"
ASSERT !EMPTY(lcPathAppData) MESSAGE "Fallo en GETAPPDATAPATH"
 
* ============================================================================
* LIMPIEZA FINAL DEL ENTORNO
* ============================================================================
RELEASE LIBRARY (lcLibraryName)

? "=== TODAS LAS PRUEBAS FINALIZADAS CON ÉXITO SIN ERRORES ==="
WAIT WINDOW "Pruebas completadas. Presione una tecla..." TIMEOUT 3
