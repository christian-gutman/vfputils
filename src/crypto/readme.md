# 🔐 VFP Crypto & Hashing para Visual FoxPro (`vfpcrypto.fll`)

Módulo criptográfico nativo para **Visual FoxPro (VFP)** diseñado para la generación de hashes, firmas HMAC, cifrado simétrico de cadenas, nonces seguros y codificación Unicode/UTF-8 Base64.

Proporciona funciones rápidas y seguras sin depender de componentes COM externos, ActiveX ni scripts de consola, ejecutándose directamente mediante una librería FLL compilada en C/C++ (x86).

[Volver al inicio](/README.md)
---

## 🚀 Características

* **Hashes de Cadenas y Archivos:** Cálculo nativo en memoria y lectura directa en disco para los algoritmos `MD5`, `SHA-1`, `SHA-256`, `SHA-384` y `SHA-512`.
* **Autenticación de Mensajes (HMAC):** Generación de firmas HMAC con clave secreta sobre cadenas de texto o archivos binarios.
* **Despachadores Dinámicos:** Selección del algoritmo criptográfico en tiempo de ejecución mediante `GENHASH()`, `GENFILEHASH()`, `GENHMAC()` y `GENFILEHMAC()`.
* **Cifrado de Cadenas:** Encriptación y desencriptación segura de textos (con soporte completo para acentos y caracteres extendidos) mediante `ENCRYPTSTRING()` y `DECRYPTSTRING()`.
* **Nonces y Codificación Base64:** Generación de tokens hexadecimales aleatorios seguros (`CREATESECURENONCE`) y serialización limpia entre Unicode/ANSI y UTF-8 Base64.
* **Nativo en VFP:** Librería FLL compilada en arquitectura **x86 (32 bits)** lista para usar con `SET LIBRARY TO`.

---

## 📋 Requisitos Previos

* **Visual FoxPro 9.0** (o compatible con librerías FLL de 32 bits).
* Archivo compilado **`vfpcrypto.fll`** o **`vfputils.fll`** (compilado en arquitectura **x86 / 32 bits**).

---

## 📂 Estructura Recomendada

```text
proyecto/
├── vfputils.fll  o vfpcrypto.fll  # Librería compilada (x86)
├── test_crypto.prg                # Script principal de pruebas
└── README.md
```

---

## ⚙️ Instalación y Uso

1. **Clonar el repositorio:**
   ```bash
    
   ```

2. **Configurar los archivos:**
   * Coloca el archivo `vfpcrypto.fll` (o `vfputils.fll`) en la raíz de tu proyecto o en una ruta incluida en `SET PATH`.

3. **Ejecutar en Visual FoxPro:**
   Desde la ventana de comandos de VFP, ejecuta el script de pruebas:
   ```foxpro
   DO test_crypto.prg
   ```

---

## 🛠️ Funciones Principales de la FLL

### 1. Hashes (Cadenas y Archivos)

| Función | Parámetros | Descripción |
| :--- | :--- | :--- |
| `MD5()` | `(cTexto)` | Devuelve el hash MD5 en hexadecimal (32 caracteres). |
| `SHA1()` | `(cTexto)` | Devuelve el hash SHA-1 en hexadecimal (40 caracteres). |
| `SHA256()` | `(cTexto)` | Devuelve el hash SHA-256 en hexadecimal (64 caracteres). |
| `SHA384()` | `(cTexto)` | Devuelve el hash SHA-384 en hexadecimal (96 caracteres). |
| `SHA512()` | `(cTexto)` | Devuelve el hash SHA-512 en hexadecimal (128 caracteres). |
| `GENHASH()` | `(cData, nDataLen, cAlgorithm)` | Calcula el hash dinámico especificando el algoritmo (`"MD5"`, `"SHA-256"`, etc.). |
| `MD5FILE()` | `(cRutaArchivo)` | Calcula el hash MD5 de un archivo en disco. |
| `SHA1FILE()` | `(cRutaArchivo)` | Calcula el hash SHA-1 de un archivo en disco. |
| `SHA256FILE()` | `(cRutaArchivo)` | Calcula el hash SHA-256 de un archivo en disco. |
| `SHA384FILE()` | `(cRutaArchivo)` | Calcula el hash SHA-384 de un archivo en disco. |
| `SHA512FILE()` | `(cRutaArchivo)` | Calcula el hash SHA-512 de un archivo en disco. |
| `GENFILEHASH()` | `(cRutaArchivo, cAlgorithm)` | Calcula el hash dinámico de un archivo según el algoritmo indicado. |

### 2. Firmas HMAC (Cadenas y Archivos)

| Función | Parámetros | Descripción |
| :--- | :--- | :--- |
| `HMACMD5()` | `(cTexto, cClave)` | Calcula la firma HMAC-MD5 de una cadena. |
| `HMACSHA1()` | `(cTexto, cClave)` | Calcula la firma HMAC-SHA1 de una cadena. |
| `HMACSHA256()` | `(cTexto, cClave)` | Calcula la firma HMAC-SHA256 de una cadena. |
| `HMACSHA384()` | `(cTexto, cClave)` | Calcula la firma HMAC-SHA384 de una cadena. |
| `HMACSHA512()` | `(cTexto, cClave)` | Calcula la firma HMAC-SHA512 de una cadena. |
| `GENHMAC()` | `(cData, nDataLen, cKey, nKeyLen, cAlgo)` | Generador dinámico de HMAC para cadenas. |
| `HMACMD5FILE()` | `(cRutaArchivo, cClave)` | Calcula la firma HMAC-MD5 de un archivo. |
| `HMACSHA1FILE()` | `(cRutaArchivo, cClave)` | Calcula la firma HMAC-SHA1 de un archivo. |
| `HMACSHA256FILE()` | `(cRutaArchivo, cClave)` | Calcula la firma HMAC-SHA256 de un archivo. |
| `HMACSHA384FILE()` | `(cRutaArchivo, cClave)` | Calcula la firma HMAC-SHA384 de un archivo. |
| `HMACSHA512FILE()` | `(cRutaArchivo, cClave)` | Calcula la firma HMAC-SHA512 de un archivo. |
| `GENFILEHMAC()` | `(cRutaArchivo, cClave, cAlgorithm)` | Generador dinámico de HMAC para archivos. |

### 3. Cifrado, Nonces y Codificación Base64

| Función | Parámetros | Descripción |
| :--- | :--- | :--- |
| `ENCRYPTSTRING()` | `(cTexto, cClave)` | Cifra una cadena de texto utilizando una clave secreta. |
| `DECRYPTSTRING()` | `(cTextoCifrado, cClave)` | Descifra una cadena previamente encriptada con `ENCRYPTSTRING()`. |
| `CREATESECURENONCE()` | `(nMaxLen)` | Genera un nonce hexadecimal aleatorio seguro de longitud `nMaxLen - 1` (ej. `33` genera 32 caracteres hex). |
| `UNITOUTF8BASE64()` | `(cTexto)` | Convierte texto con caracteres especiales (`ñ`, tildes) a UTF-8 codificado en Base64. |
| `UTF8BASE64TOUNI()` | `(cBase64)` | Decodifica una cadena Base64 UTF-8 a texto legible en VFP. |

---

## 📊 Tabla de Referencia de Tamaños

| Algoritmo | Bytes | Caracteres Hex | Buffer Mínimo (`+ '\0'`) |
| :--- | :---: | :---: | :---: |
| `MD5` / `HMAC-MD5` | 16 | 32 | 33 |
| `SHA1` / `HMAC-SHA1` | 20 | 40 | 41 |
| `SHA256` / `HMAC-SHA256` | 32 | 64 | 65 |
| `SHA384` / `HMAC-SHA384` | 48 | 96 | 97 |
| `SHA512` / `HMAC-SHA512` | 64 | 128 | 129 |

---

## ⚠️ Notas Técnicas

* **Liberación de memoria:** Al finalizar la ejecución, recuerda liberar la librería de memoria usando `RELEASE LIBRARY vfpcrypto.fll`. *(Nota: asegúrate de que el nombre coincida con la librería cargada al inicio con `SET LIBRARY TO`)*.
* **Tamaño del Nonce:** El parámetro `nMaxLen` de `CREATESECURENONCE(nMaxLen)` incluye el terminador nulo `\0` de C. Por ejemplo, para obtener un nonce de **32 caracteres hexadecimales** (16 bytes, estándar para HTTP Digest Auth), debes pasar `33`.

---

## Ejemplo

## Ejemplos

* [Descargar hash_dim.txt] | (examples/hash_dim.txt) | (examples/hash_dim.prg) - Tabla de referencia de tamaños de buffer por algoritmo.
* [Descargar test_hash.prg](examples/test_crypto_hash.prg) - Pruebas de hashes (MD5, SHA-1, SHA-256, SHA-384, SHA-512) en texto y archivos.
* [Descargar test_hmac.prg](examples/test_crypto_hmac.prg) - Pruebas de autenticación HMAC en texto y archivos.
* [Descargar test_genhash_hmac.prg](examples/test_crypto_dinamic.prg) - Pruebas de generadores dinámicos (`GENHASH` y `GENHMAC`).
* [Descargar test_encrypt.prg](examples/test_crypto_enc_dec_string.prg) - Pruebas de cifrado y descifrado de cadenas (`ENCRYPTSTRING` / `DECRYPTSTRING`).
* [Descargar test_nonce.prg](examples/test_crypto_nonce.prg) - Pruebas de generación dinámica de nonces seguros (`CREATESECURENONCE`).
* [Descargar test_crypto.prg](examples/test_crypto.prg) - Suite general de pruebas (Hashes, HMAC, Nonce y Unicode Base64).


```foxpro
*----------------------------------------------------------------------
* Programa de prueba para Hashing, HMAC, Cifrado y Base64 con FLL
*----------------------------------------------------------------------
CLEAR

*-- Cargar la FLL
IF !FILE("vfpcrypto.fll")
    ? "Archivo 'vfpcrypto.fll' no encontrado."
    ? "Asegúrese de compilar la FLL primero a 32 bits (x86)."
    RETURN
ENDIF

SET LIBRARY TO vfpcrypto.fll ADDITIVE

LOCAL lcTextoBase, lcSecreto
lcTextoBase = "Hola Mundo"
lcSecreto   = "ClaveSecreta123"

? "========================================================="
? "PRUEBA 1: HASHES ESTÁNDAR Y DINÁMICOS"
? "========================================================="
? "Datos base : " + lcTextoBase
? "MD5        : " + MD5(lcTextoBase)
? "SHA-1      : " + SHA1(lcTextoBase)
? "SHA-256    : " + SHA256(lcTextoBase)
? "SHA-512    : " + SHA512(lcTextoBase)
? "Dinámico   : " + GENHASH(lcTextoBase, LEN(lcTextoBase), "SHA-256")
? ""

? "========================================================="
? "PRUEBA 2: FIRMAS HMAC CON CLAVE SECRETA"
? "========================================================="
? "HMAC-MD5   : " + HMACMD5(lcTextoBase, lcSecreto)
? "HMAC-SHA256: " + HMACSHA256(lcTextoBase, lcSecreto)
? "HMAC-Dinám.: " + GENHMAC(lcTextoBase, LEN(lcTextoBase), lcSecreto, LEN(lcSecreto), "SHA-256")
? ""

? "========================================================="
? "PRUEBA 3: CIFRADO DE CADENAS Y CODIFICACIÓN UNICODE BASE64"
? "========================================================="
LOCAL lcMensaje, lcCifrado, lcDescifrado, lcBase64
lcMensaje    = "Mensaje secreto con eñes y acentos: áéíóú ñ Ñ"
lcCifrado    = ENCRYPTSTRING(lcMensaje, lcSecreto)
lcDescifrado = DECRYPTSTRING(lcCifrado, lcSecreto)

? "Original   : " + lcMensaje
? "Cifrado    : " + lcCifrado
? "Descifrado : " + lcDescifrado

lcBase64 = UNITOUTF8BASE64(lcMensaje)
? "UTF8 Base64: " + lcBase64
? "Decodif.   : " + UTF8BASE64TOUNI(lcBase64)
? ""

? "========================================================="
? "PRUEBA 4: GENERACIÓN DE NONCE SEGURO"
? "========================================================="
LOCAL lcNonce
lcNonce = CREATESECURENONCE(33) && 32 caracteres hexadecimales (16 bytes)
? "Nonce (32) : " + lcNonce + " (Len: " + TRANSFORM(LEN(lcNonce)) + ")"

*-- Liberar la biblioteca
RELEASE LIBRARY vfpcrypto.fll
? ""
? "Pruebas finalizadas."
RETURN
```

## 📄 Licencia

Este proyecto se distribuye bajo la licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## Compilación

### Solo esta librería - vfpcrypto.fll

```bash
cd vfputils
rmdir /s /q build
cmake -S src/crypto -B build -A Win32
cmake --build build --config Release
rmdir /s /q build
```

### Todo el proyecto - vfputils.fll

```bash
cd vfputils
rmdir /s /q build
cmake -S src/all -B build -A Win32
cmake --build build --config Release
rmdir /s /q build
```

[Volver al inicio](/README.md)
