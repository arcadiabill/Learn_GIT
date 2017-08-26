/* wordCount.c_cnt
   Counts the number of words of a file.
   The file name is given on the command line.
*/

#include <stdio.h>
#include <ctype.h>

int main (argc, argv)
int argc;
char *argv[];
{
  int i;
  unsigned long int w_total = 0, l_total = 0, c_total = 0;

  if(argc < 2)
  {
    printf("Usage: wordCount filename [,filename, filename, etc.]\n");
	return -1;
  }
  
  printf ("   lines    words    bytes file\n");
  for (i = 1; i < argc; ++i)
  {
    FILE *input;
    unsigned long int w_cnt, l_cnt, c_cnt;
    int c, inword = 0;

    if ((input = fopen(argv[i], "rb")) == NULL)
    {
      printf ("wc: cannot open %s\n", argv[i]);
      continue;
    }

    w_cnt = l_cnt = c_cnt = 0;
    while ((c = fgetc(input)) != EOF)
    {
      if (c == '\n')
        ++l_cnt;
      if (!isspace(c))
      {
        if (!inword){
          inword = 1;
          ++w_cnt;
        }
      }
      else
        inword = 0;
      ++c_cnt;
    }
    fclose (input);
    printf ("%8lu%9lu%9lu %s\n", l_cnt, w_cnt, c_cnt, argv[i]);
    l_total += l_cnt;
    w_total += w_cnt;
    c_total += c_cnt;
  }
  if (argc > 2)
  {
    printf ("--------------------------------------\n%8lu%8lu%8lu total",
      l_total, w_total, c_total);
  }
  return 0;
}
