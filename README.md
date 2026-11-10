# vfputils 


git clone https://github.com/christian-gutman/vfputils.git
cd vfputils

rmdir /s /q build
cmake -S src/all -B build -A Win32 
cmake --build build --config Release

Para las funciones. Ver

Ver https://github.com/christian-gutman/vfputils/blob/main/src/all/fox_table.c