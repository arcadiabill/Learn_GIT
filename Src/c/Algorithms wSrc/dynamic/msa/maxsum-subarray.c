// Maximal sum sub array.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 10

int main() {
  int A[N];
  int i,j;
  int b, e;
  int sum, max_sum;
  printf("Array A=[");
  for(i=0;i<N;i++){
    A[i]= 1 + (int ) (N * (float) rand()/(float)RAND_MAX) - N/2 ;
    printf("%d ",A[i]);
  }
  printf("]\n");

  b=-1;
  e=-1;
  max_sum=-INT_MAX;
  for(j=0;j<N;j++){
    sum=0;
    for(i=j;i<N;i++){
      sum+=A[i];
      if(sum>max_sum){
        max_sum=sum;
        b=j;
        e=i;
      }
    }
  }
  printf("max_sum=%d subarray A[%d..%d]=[",max_sum, b, e);
  for(i=b;i<e+1;i++){
    printf("%d ",A[i]);
  }
  printf("]\n");
  return 0;
}
