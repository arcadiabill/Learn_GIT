objects = check.o
CFLAGS = -Wall -std=c99 -c

check : $(objects)
	cc -o check $(objects)

check.o: check.c
	cc $(CFLAGS) check.c
	
clean:
	rm -f check $(objects)
