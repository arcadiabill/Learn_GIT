#include <stdio.h>
#include <string.h>

#define MAXLINE 150
#define true 1
#define false 0
int ReadLine(char *,int ,FILE *);

int main(int argc, char **argv)
{
   char line[MAXLINE];
   FILE *fp;

   if (argc < 2) {
      printf("USAGE: %s filename\n", *argv);
      printf("list a file name on the command line to be read and printed\n");
      // exit(1);
      return 1;
   }
   if ((fp = fopen(argv[1], "r")) == NULL) {
      printf("cannot open file %s\n", argv[1] );
      return 1;
   }
   /* 
    * Use ReadLine to read the whole file - just print it out for 
    * this example.
    */
   while( ReadLine(line, MAXLINE, fp) ) {
      printf( "%s\n", line );
   }
   /*
    * remember to close the file.
    */
   fclose(fp);
   return 0;
}


int ReadLine(char *buff, int size, FILE *fp)
{
   buff[0] = '\0';
   buff[size - 1] = '\0';             /* mark end of buffer */
   char *tmp;

   if (fgets(buff, size, fp) == NULL) {
      *buff = '\0';                   /* EOF */
      return false;
   }
   else {
      /* remove newline */
      if ((tmp = strrchr(buff, '\n')) != NULL) {
         *tmp = '\0';
      }
   }
   return true; 
}
