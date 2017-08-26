#include <stdio.h>
#include <string.h>

int
main()
{
   int i = 0;
   int j = 0;
   int n = 0;
   int array[] = {3,1,4,1,5,9,2,6,5,3,5,8,9,7};
   int x = array[0];
   
   j = n = sizeof(array)/sizeof(array[0]);
   printf("Size of array %d\n", n);
   for (i = 0; i < n; i++)
   {
      printf("%3d", array[i]);
   }
   printf("\n");
   
   do
   {
      while (array[i] < array[i+1]) i++;
      while (array[j] > array[j-1]) j--;
      printf("I:%3d   J:%3d\n", i, j );
      float t = array[i];
      array[i] = array[j];
      array[j] = t;
   } while (i < j);
   
   for (i= 0; i < n; i++)
   {
      printf("%3d", array[i]);
   }
   printf("\n");
}

