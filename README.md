# vfputils 


### Visual FoxPro Runtime Utils Library

## 🛠️ Requisitos de Compilación

Para generar los binarios del proyecto (tanto la DLL como la FLL de FoxPro), el entorno requiere las siguientes herramientas en Windows:

* **IDE / Compilador:** [Visual Studio 2022](https://learn.microsoft.com/es-es/visualstudio/releases/2026/release-notes "Visual Studio Releases") con la carga de trabajo de desarrollo para el escritorio con C++.
* **SDK del Sistema:** [Windows 11 SDK (Versión 10.0.28000)](https://learn.microsoft.com/en-us/windows/apps/windows-sdk/downloads "Windows SDK Downloads").
* **Generador:** [CMake](https://learn.microsoft.com/es-es/vcpkg/get_started/get-started-vs "CMake Visual Studio Integration") (versión 3.15 o superior).
* **Visual Foxpro LCK 9 Sp 2:** 

## 🛠️ Procedimiento

git clone https://github.com/christian-gutman/vfputils.git
cd vfputils


```bash
rmdir /s /q build
```

```bash
cmake -S src/all -B build -A Win32 
```

```bash
cmake --build build --config Release
```

## 🛠️ Funciones disponibles

Ver https://github.com/christian-gutman/vfputils/blob/main/src/all/fox_table.c