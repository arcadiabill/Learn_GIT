#include <stdio.h>
#include <math.h>
int
main(void)
{
 
   double length = 6.14;          // In inches
   double width  = 2.61;          // In inches
   double thick  = 0.0043;        // In inches
   double volCubicInches;
   double volCubicFeet;
   long   nBills = 1000000000L;    // A Billion of them
   // Calculate the volume of nBills in Cubic inches
   volCubicInches = nBills * length * width * thick;
   volCubicFeet   = volCubicInches / (12*12*12);
   
   printf("Calculate the volume of 1,000,000,000 $bills\n\n");
   printf("  Thickness %7.4lf inches\n", thick);
   printf("  Length:%6.2lf inches\n", length);
   printf("  Width :%6.2lf inches\n", width);
   printf("\nVolume Cubic Inches: %.0lf", volCubicInches);
   printf("\nVolume Cubic Feet  : %.0lf\n", volCubicFeet);
   printf("\nThat would fill a cube %lf feet in each dimension\n", pow(volCubicFeet, 1./3.));
   
   return 0;
}
