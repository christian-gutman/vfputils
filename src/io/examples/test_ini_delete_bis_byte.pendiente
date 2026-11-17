* ============================================================================
* SCRIPT DE PRUEBAS UNITARIAS COMPLETO PARA LA FLL
* ============================================================================
CLEAR
SET ASSERTS ON && Permite pausar el código si una validación crítica falla

LOCAL lcLibraryName, lcAppName
lcLibraryName = "vfpio.fll"
lcAppName     = "FoxPro_System_Suite"

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
* PRUEBA 2: MANEJO COMPLETO DE ARCHIVOS INI (Lector, Escritor y Borrado)
* ============================================================================
? "--- 2. Probando Operaciones de Archivos .INI ---"

* A) Escritura de Datos Mixtos
LOCAL llOkStr1, llOkStr2, llOkInt1, llOkInt2
llOkStr1 = WRITEINISTR(lcPathAppData, "ServidorBD", "Host", "192.168.1.100")
llOkStr2 = WRITEINISTR(lcPathAppData, "ServidorBD", "Instancia", "FOX_PROD_ÑÁ") && Soportando caracteres extendidos
llOkInt1 = WRITEINIINT(lcPathAppData, "ServidorBD", "Puerto", 5432)
llOkInt2 = WRITEINIINT(lcPathAppData, "Seguridad",  "NivelAcceso", 3)

ASSERT llOkStr1 AND llOkStr2 AND llOkInt1 AND llOkInt2 MESSAGE "Fallo en las escrituras del archivo .INI"

* B) Lectura de Datos Existentes y Valores por Defecto
LOCAL lcHost, lcInstancia, lnPuerto, lnTimeoutDefecto
lcHost             = READINISTR(lcPathAppData, "ServidorBD", "Host", "127.0.0.1")
lcInstancia        = READINISTR(lcPathAppData, "ServidorBD", "Instancia", "DEFAULT")
lnPuerto           = READINIINT(lcPathAppData, "ServidorBD", "Puerto", 8080)
lnTimeoutDefecto   = READINIINT(lcPathAppData, "ServidorBD", "Timeout", 45) && No existe, debe traer 45

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
llDelKey = DELETEINIKEY(lcPathAppData, "Seguridad", "NivelAcceso")
lnAccesoBorrado = READINIINT(lcPathAppData, "Seguridad", "NivelAcceso", -1) && Debe devolver -1 al no existir

ASSERT llDelKey AND (lnAccesoBorrado == -1) MESSAGE "Fallo al eliminar la clave INI"

llDelSec = DELETEINISECTION(lcPathAppData, "ServidorBD")
lcHostBorrado = READINISTR(lcPathAppData, "ServidorBD", "Host", "ELIMINADO")

ASSERT llDelSec AND (lcHostBorrado == "ELIMINADO") MESSAGE "Fallo al eliminar la sección INI completa"
? "  [INI] Claves y secciones eliminadas correctamente."
?


* ============================================================================
* PRUEBA 3: LOGGING CON MARCA DE TIEMPO Y ROTACIÓN AUTOMÁTICA
* ============================================================================
? "--- 3. Probando Log de Texto Estampado y Rotación ---"

LOCAL llLog1, llLog2, lcLogContent
llLog1 = WRITELOG(lcPathLib, "Auditoría iniciada: El usuario ingresó al sistema.")
llLog2 = WRITELOG(lcPathLib, "Advertencia: Intento de consulta en tabla vacía.")

ASSERT llLog1 AND llLog2 MESSAGE "Fallo al guardar texto en el archivo de log"

* Nota: El proceso de rotación automática a '_OLD.log' se disparará de forma silenciosa
* en la FLL nativa de C en cuanto el archivo 'debug_libreria.log' supere el tamaño límite de 5 MB.
? "  [LOG] Mensajes del sistema volcados en disco."
?


* ============================================================================
* PRUEBA 4: FLUJO DE BYTES PUROS (Lectura, Escritura y Liberación de Memoria)
* ============================================================================
? "--- 4. Probando Manejo de Bytes Puros (Binarios/Archivos) ---"

LOCAL lcFileOrigen, lcFileDestino, lcDataOriginal, llWriteBytes, lcDataLeida 
lcFileOrigen  = GETEXEPATH("origen_binario.dat") 
lcFileDestino = GETEXEPATH("destino_binario.dat") 

* A) Preparar un bloque de bytes crudos simulados
LOCAL lcRawText
lcRawText = "BYTES_DE_PRUEBA_HEADER_" + REPLICATE(CHR(0) + CHR(255) + CHR(128), 50)

* SOLUCIÓN: Convertimos a String Binario Puro para que VFP no altere los CHR(0) ni CHR(255)
lcDataOriginal = CREATEBINARY(lcRawText)

* B) Escribir el buffer de bytes puros (Ahora enviará el puntero binario exacto)
llWriteBytes = WRITEFILEBYTES(lcFileOrigen, lcDataOriginal, LEN(lcDataOriginal)) 

ASSERT llWriteBytes MESSAGE "Fallo al escribir los bytes puros en disco"

* C) Leer los bytes puros desde el archivo
lcDataLeida = READFILEBYTES(lcFileOrigen)

ASSERT LEN(lcDataLeida) == LEN(lcDataOriginal) MESSAGE "El tamaño del archivo leído difiere del original"
ASSERT lcDataLeida == lcDataOriginal           MESSAGE "Corrupción de datos binarios durante el ciclo lectura/escritura"

* D) Guardar el duplicado exacto en el destino
= WRITEFILEBYTES(lcFileDestino, lcDataLeida, LEN(lcDataLeida))

* E) Liberación explícita (Mapeando conceptualmente el descarte del buffer)
* Dado que VFP copia el retorno a su pool interno de strings, invocamos a FREEBUFFER 
* pasando el manejo del puntero nulo para certificar que el colector de la FLL quede limpio.
= FREEBUFFER(0) 

? "  [BYTES] Datos binarios intactos. Archivo origen replicado con éxito en destino."
?


* ============================================================================
* LIMPIEZA FINAL DEL ENTORNO
* ============================================================================
RELEASE LIBRARY (lcLibraryName)

? "=== TODAS LAS PRUEBAS FINALIZADAS CON ÉXITO SIN ERRORES ==="
WAIT WINDOW "Pruebas completadas. Presione una tecla..." TIMEOUT 3
