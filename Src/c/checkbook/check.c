/*Programmed: Mr. Jake Rodriguez Pomperada,MAED - Instructional Technology
              Purok Pag-asa Barangay Alijis 6100 Bacolod City, Negros Occidental
              Philippines

              Email Address : jakerpomperada@yahoo.com
              Facebook Account Address :jakerpomperada@yahoo.com
              March 24, 2010 Wednesday   9:19 AM
              Tool : Code Blocks
              Language : C
 */
#include <stdio.h>
#include <math.h>
#define  EPSILON   0.009  // Data should be accurate within a penny (0.01)

int
main()
{
   double inputValue = 0.;
   double checksOutstanding = 0.;
   double depositsOutstanding = 0.;
   double statementBalance;
   double checkbookBalance;
   double trialBalance;
   int    i;
 
/* Enter and accumulate outstanding checks */
   printf("\t\t CHECKBOOK SOLVER VERSION 1.0");
   printf("\n\n");
   printf("\t Created By: Jake Rodriguez Pomperada, MAED-IT ");
   printf("\n\n");

   printf( "Enter an outstanding check amount (zero when done):\n" );
   i = 1;
   
   do
   {
      printf("%2d: ", i++);
     (void) scanf( "%lf", &inputValue );
      checksOutstanding += inputValue;
   } while ( fabs(inputValue) > EPSILON);

/* Enter and accumulate outstanding deposits */
   printf( "Enter an outstanding deposit (zero when done)\n" );
   i = 1;
   
   do
   {
      printf("%2d: ", i++);
      (void) scanf( "%lf", &inputValue );
      depositsOutstanding += inputValue;
   } while ( fabs(inputValue) > EPSILON);

/* Enter the checkbook balance */
    printf( "Enter your latest checkbook balance: " );
    (void) scanf( "%lf", &checkbookBalance );

/* Enter the statement balance */
   printf( "Enter the statement balance: " );
   (void) scanf( "%lf", &statementBalance );

   trialBalance = checkbookBalance + checksOutstanding - depositsOutstanding;
   if ( fabs(trialBalance - statementBalance) < EPSILON )
      printf( "Congratulations, your checkbook balances!\n" );
   else
      printf( "Sorry, your balance is different from the bank's by %.2f.\n",
               statementBalance - trialBalance );

   return 0;
}
