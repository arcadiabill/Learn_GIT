all:
	gcc -o log2-classic log2-classic.c
	gcc -o pi-classic pi-classic.c
	gcc -o sqrt2-series sqrt2-series.c
	gcc -o e2718-9k e2718-9k.c
	gcc -o primes primes.c
	primes | fmt | head
	e2718-9k.exe | fold -w 10 | fmt | head
	log2-classic.exe | head -2
	pi-classic.exe   | head -2
	sqrt2-series.exe | head -2

clean:
	del *.obj *.o *.exe
