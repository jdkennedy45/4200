@echo off
cls

set DRIVE_LETTER=%1:
set COMPILER_PATH=%DRIVE_LETTER%/TDM-GCC-64

set ZLIB_PATH=%COMPILER_PATH%/zlib-1.2.11
set CSC1310_PATH=%DRIVE_LETTER%/Sockets/CSC1310

set PATH=%COMPILER_PATH%/bin;%ZLIB_PATH%/lib;c:/windows

g++ -c -I./ -I%ZLIB_PATH% -I%CSC1310_PATH%/include ZipDriver.cpp
g++ -L./lib -L%CSC1310_PATH% -L%ZLIB_PATH%/lib -o ZipDriver.exe ZipDriver.o -lCSC1310 -lzipp -lzlib

::g++ -I./ -I%ZLIB_PATH% -I%CSC1310_PATH%/include -c Zip.cpp
::ar -r libzipp.a Zip.o
