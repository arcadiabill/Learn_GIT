#include "stdio.h"
#include "stdlib.h"
/* Move top n disks from peg to peg, using aux peg */
void hanoi(int n,char frompeg,char topeg,char auxpeg) {
	  if(n==1) {
        printf("disk 1 %c -> %c\n",frompeg,topeg);
	      return;
    }
	  hanoi(n-1,frompeg,auxpeg,topeg);
	  printf("disk %d %c -> %c\n",n,frompeg,topeg);
	  hanoi(n-1,auxpeg,topeg,frompeg);
	}
main() {
  int n=4;
  printf("Enter the number of disks in tower of Hanoi:");
  scanf("%d",&n);
  hanoi(n,'A','C','B');
  return 0;
}
