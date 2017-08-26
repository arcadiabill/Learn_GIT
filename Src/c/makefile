objects = PrintDir.o
CFLAGS = -Wall -std=c99 -c

PrintDir : $(objects)
	cc -o PrintDir $(objects)

PrintDir.o: PrintDir.c
	cc $(CFLAGS) PrintDir.c
	
clean:
	rm -f PrintDir $(objects)
