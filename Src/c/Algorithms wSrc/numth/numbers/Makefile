all::
	cl log2-classic.c
	cl pi-classic.c
	cl sqrt2-series.c
	cl e2718-9k.c
	cl primes.c
	./primes | fmt | head
	./e2718-9k.exe | fold -w 10 | fmt | head
	./log2-classic.exe | head -2
	./pi-classic.exe   | head -2
	./sqrt2-series.exe | head -2

clean::
	rm -f *.obj *.o *.exe
