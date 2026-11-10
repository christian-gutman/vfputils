rmdir /s /q build
cmake -S src/vfp/io -B build -A Win32
cmake --build build --config Release


funding