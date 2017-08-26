gettag : main.o tag_reader.o
	cc -o gettag main.o tag_reader.o

main.o : main.c types.h tag_reader.h
	cc -c main.c
tag_reader.o : tag_reader.c types.h tag_reader.h
	cc -c tag_reader.c
clean :
	rm gettag main.o tag_reader.o
