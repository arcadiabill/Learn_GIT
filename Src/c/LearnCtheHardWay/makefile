objects = ex1.o
CFLAGS = -Wall -g -c

ex1 : $(objects)
	cc -o ex1 $(objects)

ex1.o: ex1.c
	cc $(CFLAGS) ex1.c
	
clean:
	rm -f ex1 $(objects)
