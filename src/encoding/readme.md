rmdir /s /q build
cmake -S src/vfp/encoding -B build -A Win32
cmake --build build --config Release
 
 
funding
 