#include <stdio.h>
#include <float.h>

int main(void)
{
   puts("\nCharacteristics of the type float\n");
   printf("Storage size: %d bytes\n"
      "Smallest positive value: %E\n"
      "Greatest positvie value: %E\n"
      "Precision: %d decimal digits\n",
      sizeof(float), FLT_MIN, FLT_MAX, FLT_DIG);
   puts("\nAn example of float precision:\n");
   double d_var = 12345.6;       // A variable of type float
   float f_var = (float)d_var;   // Initialize the float variable
   printf("Floating-point number: %18.10f\n", d_var);
   printf("Stored in type float : %18.10f\n", f_var);
   printf("The rounding error is: %18.10f\n", d_var - f_var);
   printf("The %%error is        : %18.10f\n", (d_var - f_var) * 100. / d_var);
   return 0;
}
