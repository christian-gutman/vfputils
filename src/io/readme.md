# 📂 VFP I/O, Rutas y Archivos INI para Visual FoxPro (`vfpio.fll`)

Módulo nativo de Entrada/Salida para **Visual FoxPro (VFP)** orientado al descubrimiento dinámico de rutas del sistema, gestión completa de archivos de configuración `.INI` (con soporte para caracteres extendidos/Unicode) y registro de logs con marca de tiempo.

Proporciona funciones rápidas y seguras compiladas en C/C++ (x86) sin depender de declaraciones manuales de la API de Windows (`DECLARE ... IN kernel32/shell32`), facilitando el despliegue de aplicaciones en entornos modernos de Windows (como `AppData`).

[Volver al inicio](/README.md)
---

## 🚀 Características

* **Descubrimiento Dinámico de Rutas:** Obtención segura de rutas relativas al ejecutable (`GETEXEPATH`), a la librería FLL (`GETLIBPATH`) y al directorio de datos de usuario (`GETAPPDATAPATH`).
* **Gestión Completa de Archivos `.INI`:** Lectura, escritura y eliminación de claves y secciones tanto para cadenas de texto (`STR`) como para valores enteros (`INT`), preservando acentos y caracteres extendidos (`ñ`, `á`, `é`).
* **Registro de Logs (Logging):** Escritura directa de mensajes de auditoría o depuración en archivos de texto con marca de fecha y hora automática (`WRITELOG`).
* **Nativo en VFP:** Compilado en arquitectura **x86 (32 bits)** listo para usar con `SET LIBRARY TO`.

---

## 📋 Requisitos Previos

* **Visual FoxPro 9.0** (o compatible con librerías FLL de 32 bits).
* Archivo compilado **`vfpio.fll`** o **`vfputils.fll`** (compilado en arquitectura **x86 / 32 bits**).

---

## 📂 Estructura Recomendada

```text
proyecto/
├── vfputils.fll  o vfpio.fll      # Librería compilada (x86)
├── test_io.prg                    # Script principal de pruebas
└── README.md
```

---

## ⚙️ Instalación y Uso

1. **Clonar el repositorio:**
   ```bash 
   ```

2. **Configurar los archivos:**
   * Coloca el archivo `vfpio.fll` (o `vfputils.fll`) en la raíz de tu proyecto o en una ruta incluida en `SET PATH`.

3. **Ejecutar en Visual FoxPro:**
   Desde la ventana de comandos de VFP, ejecuta el script de pruebas:
   ```foxpro
   DO test_io.prg
   ```

---

## 🛠️ Funciones Principales de la FLL

### 1. Descubrimiento de Rutas

| Función | Parámetros | Descripción |
| :--- | :--- | :--- |
| `GETEXEPATH()` | `(cFileName)` | Devuelve la ruta completa combinando el directorio del ejecutable (`.exe`) con el nombre de archivo indicado. |
| `GETLIBPATH()` | `(cFileName)` | Devuelve la ruta completa combinando el directorio donde reside la `.fll` con el nombre de archivo indicado. |
| `GETAPPDATAPATH()` | `(cAppName, cFileName)` | Calcula y crea (si es necesario) una ruta segura en `%APPDATA%\cAppName\cFileName` ideal para permisos de usuario estándar en Windows. |

### 2. Gestión de Archivos `.INI`

| Función | Parámetros | Descripción |
| :--- | :--- | :--- |
| `WRITEINISTR()` | `(cPathIni, cSection, cKey, cValue)` | Escribe o actualiza un valor de texto en el archivo `.ini` (soporta caracteres extendidos). |
| `READINISTR()` | `(cPathIni, cSection, cKey, cDefault)` | Lee un valor de texto desde el `.ini`. Devuelve `cDefault` si la clave o el archivo no existen. |
| `WRITEINIINT()` | `(cPathIni, cSection, cKey, nValue)` | Escribe o actualiza un valor numérico entero en el archivo `.ini`. |
| `READINIINT()` | `(cPathIni, cSection, cKey, nDefault)` | Lee un valor entero desde el `.ini`. Devuelve `nDefault` si la clave no existe. |
| `DELETEINIKEY()` | `(cPathIni, cSection, cKey)` | Elimina una clave específica dentro de una sección del archivo `.ini`. |
| `DELETEINISECTION()` | `(cPathIni, cSection)` | Elimina una sección completa junto con todas sus claves del archivo `.ini`. |

### 3. Logs y Utilidades

| Función | Parámetros | Descripción |
| :--- | :--- | :--- |
| `WRITELOG()` | `(cPathLog, cMessage)` | Añade una línea al archivo de log especificado anteponiendo automáticamente la fecha y hora actual. |

---

## ⚠️ Notas Técnicas

* **Liberación de memoria:** Al finalizar la ejecución, recuerda liberar la librería de memoria usando `RELEASE LIBRARY vfpio.fll`. *(Nota: asegúrate de que el nombre coincida con la librería cargada al inicio con `SET LIBRARY TO`)*.
* **Permisos de escritura en Windows:** Si tu aplicación se instala en `C:\Program Files (x86)\`, evita guardar archivos `.ini` o `.log` junto al ejecutable mediante `GETEXEPATH()`. Utiliza `GETAPPDATAPATH("MiApp", "config.ini")` para evitar bloqueos por control de cuentas de usuario (UAC).

---

## Ejemplo

## Ejemplos

* [Descargar test_paths.prg](examples/test_paths.prg) - Pruebas de descubrimiento dinámico de rutas (`GETEXEPATH`, `GETLIBPATH` y `GETAPPDATAPATH`).
* [Descargar test_ini_rw.prg](examples/test_ini_rw.prg) - Pruebas de escritura y lectura de cadenas y enteros en archivos `.INI` con soporte Unicode.
* [Descargar test_ini_delete.prg](examples/test_ini_delete.prg) - Pruebas de borrado de claves (`DELETEINIKEY`) y secciones completas (`DELETEINISECTION`) en archivos `.INI`.


```foxpro
*----------------------------------------------------------------------
* Programa de prueba para Rutas, Archivos INI y Logs con FLL
*----------------------------------------------------------------------
CLEAR

*-- Cargar la FLL
IF !FILE("vfpio.fll")
    ? "Archivo 'vfpio.fll' no encontrado."
    ? "Asegúrese de compilar la FLL primero a 32 bits (x86)."
    RETURN
ENDIF

SET LIBRARY TO vfpio.fll ADDITIVE

LOCAL lcAppName, lcPathExe, lcPathLib, lcPathAppData, lcPathLog
lcAppName = "MyPowerApps"

? "========================================================="
? "PRUEBA 1: DESCUBRIMIENTO DINÁMICO DE RUTAS"
? "========================================================="
lcPathExe     = GETEXEPATH("config_global.ini")
lcPathLib     = GETLIBPATH("Configuracion.ini")
lcPathAppData = GETAPPDATAPATH(lcAppName, "usuario_local.ini")
lcPathLog     = GETLIBPATH("actividad.log")

? "Ruta junto al EXE  : " + lcPathExe
? "Ruta junto a la FLL: " + lcPathLib
? "Ruta en AppData    : " + lcPathAppData
? ""

? "========================================================="
? "PRUEBA 2: ESCRITURA Y LECTURA DE ARCHIVOS .INI"
? "========================================================="
WRITEINISTR(lcPathLib, "ServidorBD", "Host", "192.168.1.100")
WRITEINISTR(lcPathLib, "ServidorBD", "Instancia", "FOX_PROD_ÑÁ")
WRITEINIINT(lcPathLib, "ServidorBD", "Puerto", 5432)
WRITEINIINT(lcPathLib, "Seguridad",  "NivelAcceso", 3)

? "Host      : " + READINISTR(lcPathLib, "ServidorBD", "Host", "127.0.0.1")
? "Instancia : " + READINISTR(lcPathLib, "ServidorBD", "Instancia", "DEFAULT")
? "Puerto    : " + TRANSFORM(READINIINT(lcPathLib, "ServidorBD", "Puerto", 8080))
? "Timeout   : " + TRANSFORM(READINIINT(lcPathLib, "ServidorBD", "Timeout", 45))
? ""

? "========================================================="
? "PRUEBA 3: ELIMINACIÓN DE CLAVES/SECCIONES Y LOGS"
? "========================================================="
DELETEINIKEY(lcPathLib, "Seguridad", "NivelAcceso")
DELETEINISECTION(lcPathLib, "ServidorBD")
? "Host tras borrar sección: " + READINISTR(lcPathLib, "ServidorBD", "Host", "ELIMINADO")

WRITELOG(lcPathLog, "Pruebas de configuración INI ejecutadas correctamente.")
? "Log registrado en: " + lcPathLog

*-- Liberar la biblioteca
RELEASE LIBRARY vfpio.fll
? ""
? "Pruebas finalizadas."
RETURN
```

## 📄 Licencia

Este proyecto se distribuye bajo la licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## Compilación

### Solo esta librería - vfpio.fll

```bash
cd vfputils
rmdir /s /q build
cmake -S src/io -B build -A Win32
cmake --build build --config Release
rmdir /s /q build
```

### Todo el proyecto - vfputils.fll

```bash
cd vfputils
rmdir /s /q build
cmake -S src/io -B build -A Win32
cmake --build build --config Release
rmdir /s /q build
```

[Volver al inicio](/README.md)

 