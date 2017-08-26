// What: Multiply p(x)*q(x) = r(x),
// naive multiplication algorithm, O(n^2).
// 2013-Feb-18

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LEN(A)      (sizeof(A)/sizeof(A[0]))
int main() {
  float p[] = {2, 3}, q [] = {5,0,7}, r[10];
  int i, j, pn = LEN(p), qn = LEN(q), rn = LEN(r);

  for(i=0;i<rn;i++)
    r[i] = 0;
  assert(pn+qn < rn);

  for(i=0; i<pn; i++) {
    for(j=0; j<qn; j++) {
      r[i+j] += p[i]*q[j];
    }
  }

  printf("p(x)*q(x)=r(x) = ");
  for(i=0;i<rn;i++)
    if (r[i] != 0)
      printf("%+g x^%d ", r[i], i);
  printf("\n");

  return 0;
}
