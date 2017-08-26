#include <stdio.h>
#include <strings.h>
int
main(void)
{
   int nGrades =  0;
   int grade   =  0;
   int total   =  0;
   
   float average;

   // get grades -1 to stop
   puts("Enter -1 to stop entering grades.");
   while( grade >= 0 )
   {
      total += grade;
      ++nGrades;
      
      printf("Grade%3d: ", nGrades);
      scanf("%d", &grade);
   }
   
   if(--nGrades)   // Subtract one because of the -1 entry
   {
      // There was a least one grade so calc avg
      average = (float) total/nGrades;
      printf("Number Grades:%4d\n", nGrades);
      printf("Grades Total :%4d\n", total);
      puts("--------------------");
      printf("Average Grade:%6.1f\n", average);
   }
   else
      puts("\nNo grades were entered.");
   
   return 0;
}
