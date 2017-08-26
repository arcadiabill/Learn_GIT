// Generating all subset of a set
// (needed for HW, for finding largest clique):

#include <stdio.h>
#include <stdlib.h>

void subset(char *set, int i){
  int k=0;
  printf("%3d: set = { ", i);
  while(i) {
    if ( i&1 )
      printf("%c, ",set[k]);
    k++;
    i /= 2;
  }
  printf(" }\n");
}
void all_subset(char *set){
  int i, n=strlen(set), two_power_n=1<<n;
  printf("The %d subset of %s are: { \n", two_power_n, set);
  for(i=0;i< two_power_n; i++)
    subset(set,i);
  printf("}\n");
}  
int main( ) {
  all_subset("abcd");
  return 0;
}
