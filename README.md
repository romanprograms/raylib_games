# Raylib games 

```sh
mkdir build && cd build && cmake .. && cmake --build . --parallel
```

# Windows
install MinGw
install Ninja

check
```sh
gcc --version
g++ --version
ninja --version
```

run on windows 
```sh
# rm -r -fo build
cmake -S . -B build -G Ninja
cmake --build build

```

```ps1
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass

```