@echo off
echo compiling %1.c
gcc %1.c -o %1 -std=c11 -L\src\lib -lwhr
