#define _POSIX
#include <stdio.h>
#include <errno.h>

int main()
{
  int my_integer = -42;
  unsigned int my_ui = 23;
  float my_float = 3.56;
  double my_double = 424242.171717;
  char my_char = 'w';
  char my_string[] = "Pardon me, may I borrow your nose?";

  printf ("Integer: %d\n", my_integer);
  printf ("Unsigned integer: %u\n", my_ui);

  printf ("The same, as hexadecimal: %#x %#x\n", my_integer, my_ui);

  printf ("Floating-point: %f\n", my_float);
  printf ("Double, exponential notation: %17.11e\n", my_double);

  printf ("Single character: %c\n", my_char);
  printf ("String: %s\n", my_string);

  errno = EACCES;
  printf ("errno string (EACCES): %m\n");

  return 0;
}
