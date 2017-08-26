# makefile for compare
#
compare: compare.o getFilesize.o
	gcc -o compare compare.o getFilesize.o

compare.o: compare.c
	gcc -c -o compare.o compare.c

getFilesize.o: getFilesize.c
	gcc -c -o getFilesize.o getFilesize.c

clean:
	del compare.exe compare.o getFilesize.o
