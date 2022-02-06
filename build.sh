#!/bin/sh
cd "${0%/*}";
if [ $(uname) = "Darwin" ]; then
  clang++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.dylib" -shared -std=c++20 -arch arm64 -arch x86_64; 
elif [ $(uname) = "Linux" ]; then
  g++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++20 -static-libgcc -static-libstdc++ -fPIC;
elif [ $(uname) = "FreeBSD" ]; then
  clang++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++20 -lc -fPIC;
elif [ $(uname) = "DragonFly" ]; then
  g++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++20 -static-libgcc -static-libstdc++ -fPIC;
elif [ $(uname) = "OpenBSD" ]; then
  clang++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++20 -lkvm -lc -lpthread -fPIC;
else
  g++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.dll" -shared -std=c++20 -static-libgcc -static-libstdc++ -static;
fi;
