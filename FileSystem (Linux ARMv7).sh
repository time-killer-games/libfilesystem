cd "${0%/*}"

mkdir "FileSystem (ARMv7)"
mkdir "FileSystem (ARMv7)/Linux"
g++ "FileSystem.cpp" "FileSystem/Linux/filesystem.cpp" "FileSystem/POSIX/filesystem.cpp" "FileSystem/Universal/filesystem.cpp" -o "FileSystem (ARMv7)/Linux/libfilesystem.so" -std=c++17 -shared -static-libgcc -static-libstdc++ -fPIC
