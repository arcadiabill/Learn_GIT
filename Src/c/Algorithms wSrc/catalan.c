// from http://crypto.stanford.edu/~blynn/c/ch09.html
// 2013-03-12 
// what: prints all ways of nesting 5 pairs of parentheses in lexicographic order.

#include <stdio.h>

int main() {
  int n = 5, k=0;
  char s[2*n+2], *end = s + 2*n-1, *m = end;
  *s = end[1] = ')', end[2] = 0;
  for(char *c = s+1; c <= end; *c++ = '(', *c++ = ')');
  for(;; ) {
    printf("%3d %s\n", ++k, s+1);
    *m = ')';
    if (')' == *--m && (*m = '(')) continue;
    char *j = m;
    for(char *k = end; '(' == *j; *j-- = ')', *k = '(', k-=2);
    if (s == j) break;
    *j = '(', m = end;
  }
  return 0;
}
