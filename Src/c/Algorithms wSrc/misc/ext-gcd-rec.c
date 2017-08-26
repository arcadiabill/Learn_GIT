// What: Extended GCD, eaa

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int gcd, x, y;
} eea_out;

eea_out eea_rec(int a, int b) {
  eea_out res;
  printf("  Calculating eea_rec(%2d,%2d):\n", a, b);
	if(b==0) {
		res.gcd = a;
		res.x = 1;
		res.y = 0;
	} else {
    eea_out resp = eea_rec(b,a%b);
    res.gcd = resp.gcd;
    res.x = resp.y;
    res.y = resp.x - ((a/b) * resp.y);
  }
   
  printf("  %2d * %2d + %2d * %2d = %2d = gcd(%2d,%2d), ",
    res.x, a, res.y, b, res.gcd, a, b);
  if (res.gcd==1) {
    printf("inv(%d) is %d mod %d", a, res.x, b);
    // printf("ie. %2d * %2d = 1 mod %d.\n", a, res.x, b);
  }
  printf("\n");
  return res;
}

int main(int argc, char *argv[]){
  int a, b, i;
  eea_out res;
  if (argc > 2) { // usage: cmd a b ...
      printf("Reading integer pairs from command line:\n");
      for( i = 1; i < argc-1; i+=2 ) {
        a = atoi(argv[i]);
        b = atoi(argv[i+1]);
        eea_rec(a, b);
      }
  }else if (argc==2) {  
    while(scanf("%d %d",&a,&b)==2) {
     	 if(a==0 && b==0)
     		 break;
     	res = eea_rec(a,b);
     	printf("%d * %d + %d * %d = %d gcd\n", res.x, a, res.y, b, res.gcd);
    }
  } else {
    for(a=9;a<17;a+=1) {
      for(b=12;b<16;b+=1) {
        printf("Calculating eea(%d,%d):\n", a, b);
        res = eea_rec(a,b);
        printf("\n");
      }
    }
  }
  return 0;
}
