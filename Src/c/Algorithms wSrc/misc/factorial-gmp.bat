rm.exe -fv factorial-gmp.exe
gcc-4 -Wall -std=c99 -lm -g factorial-gmp.c -lgmp -o factorial-gmp
factorial-gmp.exe 1000
