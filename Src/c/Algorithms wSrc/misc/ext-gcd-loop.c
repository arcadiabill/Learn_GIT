// What: Extended GCD, eaa, converted from C++ to C.
// From http://en.literateprograms.org/Extended_Euclidean_algorithm_(C_Plus_Plus)
/*
// from http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Table_method

function eea_loop(a, b)
    x := 0    lastx := 1
    y := 1    lasty := 0
    while b ? 0
        quotient := a div b
        (a, b) := (b, a mod b)
        (x, lastx) := (lastx - quotient*x, x)
        (y, lasty) := (lasty - quotient*y, y)       
    return (lastx, lasty)

function eea_rec(a, b)
    if b == 0
        return (1, 0)
    else
        (q, r) := divide (a, b)
        (s, t) := extended_gcd(b, r)
        return (t, s - q * t)
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#ifdef _WIN32
// diable warning C4514: 'acosl' : unreferenced inline function has been removed
#pragma warning(disable : 4514)
#endif

#define PG printf("gcd(%8d, %8d)= (%8d * %8d) + (%8d * %8d) = %d\n", \
          a,b, a, res.x, b, res.y, res.gcd); \
          assert(a*res.x + b*res.y == res.gcd)

#define PT printf("gcd(%8s, %8s)= (%8s * %8s) + (%8s * %8s) = %s\n", \
          "a","b", "a", "x", "b", "y", "gcd")

typedef struct {
	int gcd, x, y;
} eea_out;
 
eea_out eea_loop(int a, int b) {
    eea_out res;
    int x1 = 1, y1 = 0;
    res.gcd = b;
    res.x = 0;
    res.y = 1;
    while (a!=0) {
      int q = res.gcd / a;
      int r = res.gcd % a;
      int x2 = res.x - x1 * q;
      int y2 = res.y - y1 * q;
      res.gcd = a; a = r;
      res.x = x1;
      res.y = y1;
      x1 = x2;
      y1 = y2;
    }
    return res;
}

int main(int argc, char *argv[]){
  int a, b, k, i, num_pairs=0;
  eea_out res;
  if (argc > 2) { // usage: cmd a b ...
      printf("Reading ext gcd pairs from command line:\n");
      PT;
      for( i = 1; i < argc-1; i+=2 ) {
        a = atoi(argv[i]);
        b = atoi(argv[i+1]);
        res = eea_loop(a, b); PG;
      }
  }else{
    if (argc > 1)
      num_pairs = atoi(argv[1]);
    if (num_pairs==0) {
      PT;
      a=352;  b=168;   res = eea_loop(a, b); PG;
      a=168;  b=352;   res = eea_loop(a, b); PG;
      a=3458; b=4864;  res = eea_loop(a, b); PG;
    } else {
      printf("Generating %d pairs of random(a, b) for ext gcd:\n", num_pairs);
      srand(time(0));
      PT;
      for(k=0;k<num_pairs;k++) {
        a = rand();
        b = rand();
        if (k < 10) {
          i = (int)pow(8,k+1);
          a %= i;
          b %= i;
        }
        res = eea_loop(a,b); PG;
      }
    }
  }
  return 0;
}
