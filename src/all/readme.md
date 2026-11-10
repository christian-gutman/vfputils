rmdir /s /q build
cmake -S src -B build -A Win32
cmake --build build --config Release
