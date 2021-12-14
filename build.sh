#!/bin/sh
cd "${0%/*}";
if [ $(uname) = "Darwin" ]; then
  clang++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.dylib" -shared -std=c++17 -arch arm64 -arch x86_64; 
elif [ $(uname) = "Linux" ]; then
  g++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++17 -static-libgcc -static-libstdc++ -fPIC;
elif [ $(uname) = "FreeBSD" ]; then
  clang++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++17 -lc -fPIC;
elif [ $(uname) = "DragonFly" ]; then
  clang++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++17 -lc -fPIC;
else
  g++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.dll" -shared -std=c++17 -static-libgcc -static-libstdc++ -static;
fi;
