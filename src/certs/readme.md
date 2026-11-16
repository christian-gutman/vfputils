# 🔐 VFP Crypto & Firma Digital para ARCA / AFIP (`vfputils.fll`)

Script de demostración y utilidades en **Visual FoxPro (VFP)** para la gestión de certificados digitales y firma de mensajes.

El ejemplo firma Tickets de Requerimiento de Acceso (**TRA**) necesarios para interactuar con los Web Services de **ARCA** (ex AFIP) mediante el servicio de autenticación **WSAA**.

---

## 🚀 Características

* **Validación de Certificados:** Lectura de archivos `.pfx`, `.crt` y `.cer` para obtener la fecha de vencimiento y calcular los días restantes de vigencia.
* **Firma Digital CMS (PKCS#7):** Generación de firmas criptográficas sobre archivos XML (TRA) utilizando la clave privada contenida en un archivo `.pfx`.
* **Salida en Base64:** Entrega el mensaje firmado listo para ser enviado en la etiqueta `<in0>` del método `loginCms` del WSAA.
* **Nativo en VFP:** Sin dependencias externas de COM o scripts de consola pesados, utilizando directamente una librería FLL compilada en C/C++ (x86).

---

## 📋 Requisitos Previos

* **Visual FoxPro 9.0** (o compatible con FLL de 32 bits).
* Archivo compilado **`vfputils.fll`** (debe estar compilado en arquitectura **x86 / 32 bits** con soporte criptográfico habilitado).
* Un certificado digital válido emitido por ARCA/AFIP en formato `.pfx` (con clave privada y contraseña) para realizar pruebas de firma.

---

## 📂 Estructura Recomendada

```text
proyecto/
├── certs/
│   └── mi_certificado.pfx    # Tu certificado digital (no subir a Git)
├── vfputils.fll              # Librería compilada (x86)
├── test_certs.prg        # Script principal de pruebas
└── README.md
```

---

## ⚙️ Instalación y Uso

1. **Clonar el repositorio:**
   ```bash
   
   ```

2. **Configurar los archivos:**
   * Coloca el archivo `vfputils.fll` en la raíz del proyecto.
   * Guarda tu certificado en la carpeta `certs/` (o ajusta la ruta en el código).

3. **Editar credenciales de prueba:**
   Abre el archivo `.prg` y modifica las variables de ruta y contraseña:
   ```foxpro
   lcCertFile = "certs/mi_certificado.pfx"
   lcPassword = "MiPassword123"
   ```

4. **Ejecutar en Visual FoxPro:**
   Desde la ventana de comandos de VFP, ejecuta:
   ```foxpro
   DO test_certs.prg
   ```

---

## 🛠️ Funciones Principales de la FLL

| Función | Parámetros | Descripción |
| :--- | :--- | :--- |
| `CertGetExpiry()` | `(cRutaCert, cPassword)` | Devuelve la fecha y hora de vencimiento del certificado en formato texto. |
| `CertSignMsg()` | `(cMensajeXML, cRutaPFX, cPassword)` | Firma el contenido XML con la clave privada del `.pfx` y lo codifica en Base64 (CMS). |
---

## ⚠️ Notas Técnicas

* **Liberación de memoria:** Al finalizar la ejecución, recuerda liberar la librería de memoria usando `RELEASE LIBRARY vfputils.fll`. *(Nota: asegúrate de que el nombre coincida con la librería cargada al inicio con `SET LIBRARY TO`)*.
* **Seguridad:** Nunca subas archivos `.pfx`, `.key` ni contraseñas reales a repositorios públicos. Agrega `certs/*.pfx` a tu archivo `.gitignore`.

---
## Ejemplo 

[Descargar test_Certs.prg](examples/test_certs.prg)

```code
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
 ```
 
## 📄 Licencia

Este proyecto se distribuye bajo la licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## Compilacion

### Solo esta libreria 

```bash
rmdir /s /q build
cmake -S src/certs -B build -A Win32
cmake --build build --config Release
```

### Todo el proyecto 

```bash
rmdir /s /q build
cmake -S src/all -B build -A Win32
cmake --build build --config Release
 ```

