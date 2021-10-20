#!/bin/sh
cd "${0%/*}";
if [ $(uname) = "Darwin" ]; then
  clang++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.dylib" -shared -std=c++17; 
elif [ $(uname) = "Linux" ]; then
  g++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++17 -static-libgcc -static-libstdc++;
elif [ $(uname) = "FreeBSD" ]; then
  clang++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++17 -lc;
elif [ $(uname) = "DragonFly" ]; then
  g++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.so" -shared -std=c++17 -static-libgcc -static-libstdc++ -lc;
else
  g++ "filesystem.cpp" "gamemaker.cpp" -o "libfilesystem.dll" -shared -std=c++17 -static-libgcc -static-libstdc++ -static;
fi;
