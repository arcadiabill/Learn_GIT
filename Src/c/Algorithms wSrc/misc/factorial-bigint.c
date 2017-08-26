/* 
What: compute n! exactly using bigint.
Date: 2013-03-22 
Usage: 
  $ gcc -g -lm factorial-bigint.c -o fact
  $ fact 1000
  1000!= 402387260077093773543702...<long output not shown>.........000
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000

typedef struct { char digits[N]; } bigint;
// To make it easy to extend a bigint on right side during multiplication.
// we store bigint value as reverse(digits), so digits="321" => value=123.

void print_bigint(bigint *b) {
  int len=strlen(b->digits);
  while(len>=0)
    printf("%c", b->digits[len--]);
  printf("\n");
}

void mult_bigint_int(bigint *b, int n) {
  int carry=0, len = strlen(b->digits), k;
  for(k=0;k<len;k++) {
    int t = b->digits[k] - '0', s;
    s = t * n + carry;
    b->digits[k] = (char) (s % 10 + '0');
    carry = s / 10;
  }
  while(carry) {
    b->digits[k++] = (char) (carry % 10 + '0');
    carry /= 10;
    if (k>=N) printf("Overflow at n=%d\n", n), exit(-1);
  }
  b->digits[k] = '\0';
}

int main(int argc, char *argv[]){
  int i, input = 1000;
  bigint fact; fact.digits[0]='1'; fact.digits[1] = '\0';
  if ( argc > 1 ) input = atoi(argv[1]);
  for(i=1;i<=input;i++) 
    mult_bigint_int(&fact, i);
  printf("%d!=",input); print_bigint(&fact);
  return 0;
}

