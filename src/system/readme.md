rmdir /s /q build
cmake -S src/vfp/system -B build -A Win32
cmake --build build --config Release


funding