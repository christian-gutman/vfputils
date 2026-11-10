# Ruta por defecto cmake 2026

C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe

# 1. Comprobar si el archivo realmente existe en esa carpeta
Test-Path "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# 2. Si el comando anterior devuelve True, fuerza el alias en esta sesión:

Set-Alias -Name cmake -Value "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# 3. Prueba si ya responde
cmake --version

# 4. Como admin, Crear un enlace directo en la carpeta System32 (Windows siempre lee esta carpeta primero)
New-Item -ItemType SymbolicLink -Path "C:\Windows\System32\cmake.exe" -Value "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# 5. Verificar nuevamente qye que funcione inmediatamente
cmake --version

# 6. Build

mkdir build
cd build
cmake -A Win32 ..
cmake --build . --config Release

# 5 . Funciones Fll

cTexto=StrToAnsi(cText)
cTexto=StrToUtf8(cText)
cTexto=StrDetectEncoding(cText)
cTexto=StrAutoToUnicode(cText)

cTexto=JsonGetString(cText)
cTexto=JsonGetNumber(cText)
cTexto=JsonGetInt(cText)
cTexto=JsonGetBool(cText)
cTexto=JsonHasValue(cText)
cTexto=JsonArrayCount(cText)
cTexto=JsonGetType(cText)
cTexto=JsonExtractSubNode(cText)
cTexto=JsonGetOString(cText)
cTexto=JsonGetONumber(cText)

cTexto=SHA256(cText)
cTexto=HMACSHA256(cText)

cTexto=CertGetExpiry(cText)
cTexto=CertSignMsg(cText)
 