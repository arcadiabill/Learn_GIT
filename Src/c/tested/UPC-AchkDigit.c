/* chkDigit

   Show the algorithm to calculate the UPC-A check digit
*/
#include <stdio.h>

int main(void)
{
  int chkDigit[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2};
  int temp, sum1, sum2;

  sum1 = chkDigit[0] + chkDigit[2] + chkDigit[4] + chkDigit[6] + chkDigit[8] + chkDigit[10];
  sum2 = chkDigit[1] + chkDigit[3] + chkDigit[5] + chkDigit[7] + chkDigit[9];
  temp = 9 - ( 3*sum1 + sum2 - 1 ) % 10;

  printf("chkDigit: Show the algorithm to check UPC-A check digit\n");
  printf("Example UPC-A '1 23456 78901 2' check digit = 2, the last digit\n\n");
  printf("The algorithm:\n");
  printf("1) Add all the  odd numbered digits (sum1)\n");
  printf("2) Add all the even numbered digits (sum2)\n");
  printf("3) Compute: checkDigit = 9 - (3 * sum1 + sum2 -1) % 10\n\n");
  printf("For the UPC-A code above\n");
  printf("sum1 = 1+3+5+7+9+1 or 26\n");
  printf("sum2 = 2+4+6+8+0   or 20\n");
  printf("chkD = 9 - (3 * 26 + 20 - 1) %% 10\n");
  printf("       9 - (  78   +   19  ) %% 10\n");
  printf("       9 - (     97        ) %% 10\n");
  printf("       9 - 7\n");
  printf("         2\n");
  printf("The check digit is 2 & the last digit of code is 2 so the code is valid\n\n");
  
  return 0;
}
