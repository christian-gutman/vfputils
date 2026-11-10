
Biblioteca de Extensiones para Visual FoxPro (vfp_extensions)

Esta biblioteca proporciona una colección de funciones de alto rendimiento en C/C++ expuestas para Visual FoxPro (VFP) a través de la API de librerías de FoxPro (FoxInfo / FoxTable). Añade capacidades avanzadas de codificación, manipulación de cadenas nativas en memoria, parsing de JSON, criptografía, operaciones de entrada/salida (I/O) y peticiones HTTP/REST (WExec).

🚀 Características principales

• Manipulación de Strings y Encoding: Soporte nativo para conversión y detección de UTF-8, ANSI, Unicode y manejo avanzado de cadenas.

• JSON Extractor: Lectura directa de tipos de datos complejos en JSON mediante rutas (paths).

• Criptografía Avanzada: Funciones Hash y HMAC (MD5, SHA1, SHA256, SHA384, SHA512) tanto para texto como para archivos físicos, además de cifrado simétrico AES256.

• Cliente HTTP / REST (WExec): Soporte completo para métodos REST (GET, POST, PUT, PATCH, DELETE), envío de formularios tradicionales (x-www-form-urlencoded) y subida de archivos vía multipart/form-data.

• Seguridad y Certificados: Firma digital de mensajes y lectura de expiración de certificados.

📚 Referencia de Funciones por Módulo


1. Codificación y Strings (vfp_encoding.c / vfp_strings.c)

Funciones optimizadas para la conversión de páginas de códigos y manejo de texto.
 
STRTOUTF8(lcTexto)	(C)	Convierte una cadena ANSI a UTF-8. 

? STRTOUTF8("Café")

STRTOANSI(lcTextoUtf8)	(C)	Convierte una cadena UTF-8 a ANSI.

STRDETECTENCODING(lcTexto)	(C)	Detecta la codificación de un string.

STRAUTOUNICODE(lcTexto)	(C)	Convierte automáticamente el texto de origen a Unicode.

STRDETECTBOM(lcTexto, @lnOffset)	(C, R)	Detecta la presencia de un BOM en la cadena y devuelve el offset.

STRISVALIDUTF8SEQ(lcText, @lnLen)	(C, R)	Valida si la secuencia es un UTF-8 válido (Devuelve .T. o .F.).

STRALLTRIM(lcTexto)	(C)	Elimina espacios al inicio y al final.

STRCOMPARE(lcStr1, lcStr2)	(C, C)	Compara dos cadenas (Devuelve -1, 0 o 1).

STRNCOMPARE(lcStr1, lcStr2, lnN)	(C, C, N)	Compara los primeros N caracteres de dos cadenas.

STRLEFT(lcTexto, lnCant)	(C, N)	Retorna los caracteres de la izquierda.

STRRIGHT(lcTexto, lnCant)	(C, N)	Retorna los caracteres de la derecha.

STRPADL(lcTexto, lnLen, lcPad)	(C, N, C)	Rellena la cadena por la izquierda. STRPADL("42", 5, 
"0") -> "00042"

STRPADR(lcTexto, lnLen, lcPad)	(C, N, C)	Rellena la cadena por la derecha. STRPADR("42", 5, "0") -> "42000"

STRNORMALIZE(lcTexto)	(C)	Normaliza y pasa a minúsculas quitando espacios redundantes.

STRTOLOWER(lcTexto)	(C)	Convierte la cadena a minúsculas en memoria C.

STRTOUPPER(lcTexto)	(C)	Convierte la cadena a mayúsculas en memoria C.

STRESCAPE(lcTexto)	(C)	Escapa comillas simples. STRESCAPE("O'Brien") -> "O''Brien"

STRUNESCAPE(lcTexto)	(C)	Desescapa cadenas de texto con comillas dobles.

STRFORMAT(lcFormat, ...)	(C, ...)	Formatea una cadena estilo printf. STRFORMAT("Hola %s", "Juan")

STRREMOVECHAR(lcText, lcChar)	(C, C)	Remueve todas las instancias de un caracter específico de la cadena.

STRCLEANSPACE(lcText)	(C)	Limpia espacios duplicados o en blanco consecutivos.


2. Extracción de JSON (vfp_json.c)

Permite leer valores de un string JSON de forma directa sin necesidad de instanciar un parser complejo en VFP, utilizando rutas de nodos separados por puntos (ej: "envio.ciudad").

JSONGETSTRING(cJson, cPath)	(C, C)	Character	Obtiene una cadena de texto.

JSONGETDOUBLE(cJson, cPath)	(C, C)	Numeric	Obtiene un valor numérico decimal (Double).

JSONGETINT(cJson, cPath)	(C, C)	Numeric	Obtiene un entero de 32 bits.

JSONGETINT64(cJson, cPath)	(C, C)	Character	Obtiene un entero de 64 bits como String para evitar desbordamientos.

JSONGETBOOL(cJson, cPath)	(C, C)	Logical	Obtiene un valor lógico (.T. o .F.).

JSONHASVALUE(cJson, cPath)	(C, C)	Logical	Verifica si el nodo o propiedad existe.

JSONARRAYCOUNT(cJson, cPath)	(C, C)	Numeric	Devuelve la cantidad de elementos en un arreglo JSON.

JSONGETTYPE(cJson, cPath)	(C, C)	Character	Retorna el tipo de nodo ("array", "object", "string", etc).

JSONEXTRACTSUBNODE(cJson, cPath)	(C, C)	Character	Extrae el fragmento crudo de un objeto o subnodo JSON.

JSONGETANY(cJson, cPath)	(C, C)	Variant	Obtiene el tipo de dato nativo correspondiente dinámicamente.

3. Entrada/Salida e Inicialización (vfp_io.c)

Manejo de archivos de configuración (.INI), logs del sistema y rutas de aplicación.
foxpro

WRITEINISTR(cArchivoIni, cSeccion, cClave, cValor)

WRITEINIINT(cArchivoIni, cSeccion, cClave, nValor)

READINISTR(cArchivoIni, cSeccion, cClave, cDefault)

READINIINT(cArchivoIni, cSeccion, cClave, nDefault)

DELETEINIKEY(cArchivoIni, cSeccion, cClave)

DELETEINISECTION(cArchivoIni, cSeccion)

* Escritura de logs cronológicos automatizados
WRITELOG(cArchivoLog, cMensaje)

* Obtención de rutas del sistema relativas

GETAPPDATAPATH(cSubFolder, cFileName) -> Retorna el Path en AppData local.

GETEXEPATH(cFileName)                -> Retorna el Path relativo al ejecutable principal.

GETLIBPATH(cFileName)                -> Retorna el Path relativo a la carpeta de esta librería.

4. Criptografía, Hashing y Cifrado (vfp_crypto.c)

Cálculo de hashes criptográficos para strings y archivos en disco, generación de firmas HMAC y criptografía simétrica.

• Hashes de Cadenas: MD5(cStr), SHA1(cStr), SHA256(cStr), SHA384(cStr), SHA512(cStr)

• Hashes Algorítmicos Genéricos: GENHASH(cStr, nAlgo, cKey)

• HMAC para Firmas de API: HMACMD5(cStr, cKey), HMACSHA1(cStr, cKey), HMACSHA256(cStr, cKey), HMACSHA384(cStr, cKey), HMACSHA512(cStr, cKey)

• HMAC Genérico: GENHMAC(cStr, nAlgo, cKey)

• Hashes de Archivos Físicos: MD5FILE(cPath), SHA1FILE(cPath), SHA256FILE(cPath), SHA512FILE(cPath), GENFILEHASH(cPath, cAlgo)

• HMAC de Archivos Físicos: HMACMD5FILE(cPath, cKey), HMACSHA1FILE(cPath, cKey), HMACSHA256FILE(cPath, cKey), HMACSHA384FILE(cPath, cKey), HMACSHA512FILE(cPath, cKey), GENFILEHMAC(cPath, 
cKey, cAlgo)

• Seguridad y Encriptación:

	• CREATESECURENONCE(nSize) -> Crea un token único e irrepetible (nonce).

	• UNITOUTF8BASE64(cStr) y UTF8BASE64TOUNI(cStr) -> Conversión directa útil para tokens JWT u payloads de red.

	• ENCRYPTSTRING(cTexto, cClave) -> Encripta una cadena mediante AES-256.

	• DECRYPTSTRING(cTextoCifrado, cClave) -> Desencripta cadenas cifradas con AES-256.

5. Utilidades Web HTML (vfp_html.c)

• ENCODEURICOMPONENT(cStr) / DECODEURICOMPONENT(cStr) -> Codificación/Decodificación URL estándar.

• HTMLENTITIES(cStr) -> Convierte caracteres especiales a sus entidades HTML correspondientes.

• UTF8TOANSI(cStr) / ANSITOUTF8(cStr) -> Métodos complementarios rápidos para HTML/Web.

6. Módulo de Red y Consumo REST (vfp_request.c, vfp_req_file.c, vfp_rest.c)

Proporciona llamadas síncronas de bajo nivel para comunicación HTTP/HTTPS sin depender de objetos pesados de ActiveX como MSXML2.ServerXMLHTTP.

Conexiones Persistentes / Tradicionales

• WConnect(cHost, cPort, nFlags, cExtra)

• WDisconnect(hConnect)

• WRequest(hConnect, ...)

• WCloseRequest(hRequest)

Descargas e Intercambio de Archivos

• WDownloadToFile(cUrl, cDestPath, ...)

• WRequestToFile(cUrl, ...)

• WDownload(cUrl, ...)

Cliente REST de Alto Nivel (Fácil integración)

Encapsulan las peticiones devolviendo el contenido directamente y permitiendo la captura de códigos de estado de forma nativa por referencia (@).
foxpro

* Petición REST genérica base

WRestRequest(cMethod, cUrl, cPayload, cHeaders, ..., @nHttpStatus, @cResponseHeaders)

* Envolturas específicas (Envío y recepción de strings / JSON)

WRestGet(cUrl, cHeaders, cParams, @nStatus, @cResponse)

WRestPost(cUrl, cPayload, cHeaders, cParams, @nStatus, @cResponse)

WRestPut(cUrl, cPayload, cHeaders, cParams, @nStatus, @cResponse)

WRestPatch(cUrl, cPayload, cHeaders, cParams, @nStatus, @cResponse)

WRestDelete(cUrl, cHeaders, cParams, @nStatus, @cResponse)

* Envío de formularios Web tradicionales (application/x-www-form-urlencoded)

WRestFormPost(cUrl, cFormData, cHeaders, cParams, @nStatus, @cResponse)

WRestFormPut(cUrl, cFormData, cHeaders, cParams, @nStatus, @cResponse)

WRestFormPatch(cUrl, cFormData, cHeaders, cParams, @nStatus, @cResponse)

* Envío de archivos binarios complejos (multipart/form-data)

WRestMultipartPost(cUrl, cFileField, cFilePath, cHeaders, cParams, @nStatus, @cResponse)

Usa el código con precaución.

7. Diagnósticos del Sistema y Certificados (vfp_system.c / vfp_certs.c)

• SOLASTERROR(@nErrCode, @cErrMessage) -> Captura el último error del sistema operativo (Win32 API) por referencia.

• CertGetExpiry(cCertPath, cPassword) -> Obtiene la fecha de expiración de un certificado de seguridad.

• CertSignMsg(cMessage, cCertPath, cPassword) -> Firma un mensaje digitalmente utilizando una clave/certificado privado.

🛠️ Convención de Argumentos en la API

Al invocar estas funciones desde FoxPro, los tipos mapeados en la estructura corresponden a:

• C: Character (Cadena de texto pasada por valor).

• I: Integer (Entero numérico de 32 bits).

• N: Numeric (Valores numéricos estándar de FoxPro).

• L: Logical (Variables lógicas .T. o .F.).

• R: Reference (Variables que deben ser precedidas por @ al invocarse para recibir datos de 
retorno).

• ?: Verificación de tipo flexible dependiente del contexto de inicialización interno de la API.


Codificación y Cadenas

• ? STRTOUTF8("Café")

• ? STRTOANSI(lcTextoUtf8)

• lcEnc = STRDETECTENCODINGLEN(lcTexto, @lnOffset)

• ? STRAUTOUNICODE(lcTexto)

• lcEnc = STRDETECTBOM(lcTexto, @lnOffset)

• ? STRISVALIDUTF8SEQ(lcTexto, @lnCharLen)   && .T./.F.

• lcEnc = STRDETECTENCODINGLEN(lcTexto, @lnOffset)

• ? STRALLTRIM("   hola   ")                 && "hola"

• ? STRCOMPARE("abc", "abd")                 && -1

• ? STRNCOMPARE("abcXYZ", "abcQQQ", 3)      && 0

• ? STRLEFT("Visual FoxPro", 6)             && "Visual"

• ? STRRIGHT("Visual FoxPro", 6)            && "FoxPro"

• ? STRPADL("42", 5, "0")                   && "00042"

• ? STRPADR("42", 5, "0")                   && "42000"

• ? STRNORMALIZE("   HOLA   ")              && "hola"

• ? STRTRIMALL("   texto   ")               && "texto"

• ? STRTOLOWER("HOLA")                      && "hola"

• ? STRTOUPPER("hola")                      && "HOLA"

• ? STRESCAPE("O'Brien")                    && "O''Brien"

• ? STRUNESCAPE("O''Brien")                 && "O'Brien"

• ? STRFORMAT("Hola %s, tenés %s msjs", "Juan", "5")

• ? lctext= StrRemoveChar("Hola efwf Z U Z", "Z")

• cTextClean =STRCLEANSPACE(cText)

Extracción de JSON

• ? JSONGETSTRING(lcJson, "nombre")          && "Juan Pérez"

• ? JSONGETDOUBLE(lcJson, "precio")          && 199.99

• ? JSONGETINT(lcJson, "cantidad")           && 3

• ? JSONGETINT64(lcJson, "id")               && "12345678901234"

• ? JSONGETBOOL(lcJson, "activo")            && .T.

• ? JSONHASVALUE(lcJson, "envio.ciudad")     && .T.

• ? JSONARRAYCOUNT(lcJson, "tags")           && 2

• ? JSONGETTYPE(lcJson, "tags")              && "array"

• lcSub = JSONEXTRACTSUBNODE(lcJson, "envio")

• uVal = JSONGETANY(lcJson, "precio")  && VARTYPE(uVal) = "N"

Criptografía y Cifrado

• cData = ENCRYPTSTRING(cText, cKey)

• cData = DECRYPTSTRING(cText, cKey)
