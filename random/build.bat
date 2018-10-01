@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\TDM-GCC-64\bin;c:\windows

g++ -I./ -c Random.cpp
g++ -I./ -c mother.cpp
g++ -I./ -c mersenne.cpp

ar -r librandom.a Random.o mother.o mersenne.o

