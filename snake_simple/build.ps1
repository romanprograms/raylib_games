Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/snake_simple.exe