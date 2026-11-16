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

## 📄 Licencia

Este proyecto se distribuye bajo la licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## Compilacion

### Solo esta libreria - > pendiente

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

