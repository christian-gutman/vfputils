# vfputils 


### Visual FoxPro Tools Library


> ⚠️ **Nota de migración y estado del proyecto:** 
> Este desarrollo pertenecía originalmente a la cuenta `@christiangutman`. Lamentablemente, debido a un robo de hardware, se perdió el acceso definitivo a dicha cuenta y a su repositorio original. 
> 
> Gracias a que el código se encontraba respaldado en diferentes proveedores y servidores externos, logré recuperar las fuentes de manera íntegra. A raíz de este suceso, he tomado la firme decisión de liberar el proyecto, transformándolo en un desarrollo completamente **público y de código abierto** para la comunidad. 
> 
> A partir de ahora, **este repositorio será el hogar oficial y definitivo** para el mantenimiento, actualizaciones y evolución de **vfputils**. ¡Las contribuciones y reportes de bugs son más que bienvenidos aquí!

## 🛠️ Version 1.0

https://gitlab.com/christian.gutman/core-windows-c-library


## 🛠️ Requisitos de Compilación

Para generar los binarios del proyecto (tanto la DLL como la FLL de FoxPro), el entorno requiere las siguientes herramientas en Windows:

* **IDE / Compilador:** [Visual Studio 2022](https://learn.microsoft.com/es-es/visualstudio/releases/2026/release-notes "Visual Studio Releases") con la carga de trabajo de desarrollo para el escritorio con C++.
* **SDK del Sistema:** [Windows 11 SDK (Versión 10.0.28000)](https://learn.microsoft.com/en-us/windows/apps/windows-sdk/downloads "Windows SDK Downloads").
* **Generador:** [CMake](https://learn.microsoft.com/es-es/vcpkg/get_started/get-started-vs "CMake Visual Studio Integration") (versión 3.15 o superior).
* **Visual Foxpro LCK 9 Sp 2:** 

## 🛠️ Procedimiento

Abrir ventana de comandos

```bash
git clone https://github.com/christian-gutman/vfputils.git
```

```bash
cd vfputils
```


```bash
rmdir /s /q build
```

```bash
cmake -S src/all -B build -A Win32 
```

```bash
cmake --build build --config Release
```


```bash
rmdir /s /q build
```

```bash
# en bin estan los componentes
```
## 🛠️ Funciones disponibles

Ver https://github.com/christian-gutman/vfputils/blob/main/src/all/fox_table.c