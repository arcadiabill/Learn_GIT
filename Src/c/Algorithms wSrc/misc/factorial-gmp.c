// Compile: gcc-4 -Wall factorial-gmp.c -lgmp -g -o factorial-gmp

#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"

void fact(mpz_t r, int n){
    unsigned int i;
    mpz_t temp;
    mpz_init(temp);
    mpz_set_ui(r,1);
    for(i=1;i<=n;i++){
        mpz_set_ui(temp,i);
        mpz_mul(r,r,temp);
    }
    mpz_clear(temp);
}
int main(int argc, char *argv[]){
    double num=1000;
    mpz_t r;
    if ( argc > 1 ){ num = atof(argv[1]);
    } else {
      printf("Enter a number to find its factorial using gmp:");
      scanf("%lf",&num);	
    }
    mpz_init(r);
    fact(r,num);
    printf("%.0lf!=",num);
    gmp_printf("%Zd\n",r);
    mpz_clear(r);
    return(0);
}
