cd "${0%/*}"

mkdir "FileSystem (ARMv8)"
mkdir "FileSystem (ARMv8)/Linux"
g++ "FileSystem.cpp" "FileSystem/Linux/filesystem.cpp" "FileSystem/POSIX/filesystem.cpp" "FileSystem/Universal/filesystem.cpp" -o "FileSystem (ARMv8)/Linux/libfilesystem.so" -std=c++17 -shared -static-libgcc -static-libstdc++ -fPIC
