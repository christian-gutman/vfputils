rmdir /s /q build_assets
rmdir /s /q build

rmdir /s /q build
cmake -S src/vfp/encoding -B build -A Win32
cmake --build build --config Release

rmdir /s /q build
cmake -S src/vfp/strings -B build -A Win32
cmake --build build --config Release

rmdir /s /q build
cmake -S src/vfp/json -B build -A Win32
cmake --build build --config Release


rmdir /s /q build
cmake -S src/vfp/io -B build -A Win32
cmake --build build --config Release

rmdir /s /q build
cmake -S src/vfp/crypto -B build -A Win32
cmake --build build --config Release

rmdir /s /q build
cmake -S src/vfp/html -B build -A Win32
cmake --build build --config Release

rmdir /s /q build
cmake -S src/vfp/request -B build -A Win32
cmake --build build --config Release

rmdir /s /q build
cmake -S src/vfp/google -B build -A Win32
cmake --build build --config Release

rmdir /s /q build
cmake -S src/vfp/system -B build -A Win32
cmake --build build --config Release

rmdir /s /q build
cmake -S src/vfp/certs -B build -A Win32
cmake --build build --config Release


rmdir /s /q build
cmake -S src/all -B build -A Win32 
cmake --build build --config Release

rmdir /s /q build
rmdir /s /q build_assets
 