@echo off
cls

set DRIVE_LETTER=%1:
set COMPILER_PATH=%DRIVE_LETTER%/TDM-GCC-64
set PATH=%COMPILER_PATH%/bin;%COMPILER_PATH%/wxWidgets-3.1.0/lib;c:/windows
set GAME_PATH=%DRIVE_LETTER%/Endeavor/Endeavor_Networked

mingw32-make GAME_PATH=%GAME_PATH% COMPILER_PATH=%COMPILER_PATH%
ar -r libCSC1310.a build/*.o
