
rm -r -fo build
cmake -S . -B build -G Ninja
cmake --build build
./build/flappy_bird.exe