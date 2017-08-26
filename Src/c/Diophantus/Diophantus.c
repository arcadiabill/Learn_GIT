#include <stdio.h>
unsigned long isqrt(unsigned long x);
int
main(int argc, char * argv[])
{
	FILE * input;
	int a,b,c;
	double d;
	char line[100];  // Lines are only about 20 chars

	if( ( input = fopen("Diophantus.txt", "r") ) == NULL)
	{
		printf("\nCan't find file: Diophantus.txt\n\n");
		return 1;
	}

	fgets( line, 100, input);  // Ignore Header line
	printf("\n\nData from a Babylonian clay tablet about 4500 years old\n\n");
	printf("The data appears to be data describing right triangles\n");
	printf("The missing column b was calculated from b^2 = c^2 - a^2\n");
	printf("Then the square root of b^2 was taken. Notice the data has\n");
	printf("a strong influence of the Babylonians sexagesimal system.\n\n");
	printf("Numbers for columns a & c are from Plimpton 322\n");
	printf("--a--  --c--  --b--  ---b/60---\n");
	while(fscanf(input, "%d %d", &a, &c) == 2)
	{
		b = c*c - a*a;
		b = isqrt(b);
		printf("%5d  %5d  %5d  %5d r %2d\n", a, c, b, b/60, b%60);
	}

	fclose(input);
	return 0;
}

unsigned long isqrt(unsigned long x)
{
    register unsigned long op, res, one;

    op = x;
    res = 0;

    /* "one" starts at the highest power of four <= than the argument. */
    one = 1 << 30;  /* second-to-top bit set */
    while (one > op) one >>= 2;

    while (one != 0) {
        if (op >= res + one) {
            op -= res + one;
            res += one << 1;  // <-- faster than 2 * one
        }
        res >>= 1;
        one >>= 2;
    }
    return res;
}

typedef unsigned char       uint8;
typedef unsigned short int  uint16;
typedef unsigned long int   uint32;

uint32             // OR uint16 OR uint8
isqrt32 (uint32 n) // OR isqrt16 ( uint16 n ) OR  isqrt8 ( uint8 n ) - respectively [ OR overloaded as
                   // isqrt (uint?? n) in C++ ]
{
    register uint32 root, remainder, place;    // OR register uint16 OR register uint8 - respectively

    root = 0;
    remainder = n;
    place = 0x40000000; // OR place = 0x4000; OR place = 0x40; - respectively

    while (place > remainder)
        place = place >> 2;
    while (place)
    {
        if (remainder >= root + place)
        {
            remainder = remainder - root - place;
            root = root + (place << 1);
        }
        root = root >> 1;
        place = place >> 2;
    }
    return root;
}
