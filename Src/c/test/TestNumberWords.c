#include <stdio.h>
#define TRUE  1
#define FALSE 0

int NumberWords( char szString[]);
int
main(void)
{
   char *cLine01 = "     A file with a few blanks";
   char *cLine02 = "A line with blanks after     ";
   char *cLine03 = "A line without leading or training blanks.";
   char *cLine04 = "    A Line with blanks before and after   ";
   
   printf("Testing Numnber of words\n\n");
   printf("# Words:%3d,  String: [%50s]\n", NumberWords(cLine01), cLine01);
   printf("# Words:%3d,  String: [%50s]\n", NumberWords(cLine02), cLine02);
   printf("# Words:%3d,  String: [%50s]\n", NumberWords(cLine03), cLine03);
   printf("# Words:%3d,  String: [%.50s]\n", NumberWords(cLine04), cLine04);
   
   return 0;
}

int NumberWords( char szString[])
{
   int nBlank = TRUE;
   int nCount = 0;
   
   for(int i=0; szString[i]; i++){
      if(szString[i] != ' ')
      {
         if(nBlank)++nCount;
         
         nBlank = FALSE;
      } else nBlank = TRUE;
   }
   
   return(nCount);
}