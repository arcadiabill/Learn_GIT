all:
	cl e2718.c FFT.c BigInt.c
	rm -fv *.obj *.o
	./e2718.exe 200

gcc::
	gcc -o e2718.exe -g e2718.c bigint.c fft.c
	./e2718.exe
