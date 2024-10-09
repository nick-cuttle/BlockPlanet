mkdir -p build
cmake -G "MinGW Makefiles" -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release