#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define  MAX_LINE  120
#define  MAC_Len    18

int GetMAC(char *MAC);

int
main(int argc, char *argv[])
{
   FILE *hRespIn;			     // Response File to read
   char  str[MAX_LINE];
   char  License[MAX_LINE];
   char  MAC_Old[MAC_LEN];
   char  MAC_NEW[MAC_LEN];
	int   nResp = 0;
   
   /* Insure argc = 2 and try to open file */
   if(argc != 2)
   {
      printf("Usage: %s <ResponseFileName>\n\n", argv[0]);
      return 1;
   }

   if((hRespIn = fopen(argv[1], "r")) == NULL)
   {
      printf("Error opening file %s\n\n", argv[1]);
      return 1;
   }
   while( fgets(str, MAX_LINE, hRespIn) != NULL )
   {
		++nResp;
   }
	printf("Number of Lines: %d\n", nResp);
   
   if(GetMAC(str) != 0)
   {
      printf("Error: Couldn't get MAC address");
      return -1;
   }
   d
   printf("MAC address: [%s]", str);
	return 0;
}


/* -------------------------------------------------------------------
   int GetMAC(char *MAC)
*/
int GetMAC(char *MAC)
{
   FILE *hTemp;              // Temp file to store output of GetMAC
   
   if(system("getMAC > hTemp.tmp") == -1)
   {
      printf("Error getting MAC address");
      return -1;
   }
   
   system("CLS");
   if((hTemp = fopen("hTemp.tmp", "r")) == NULL)
   {
      printf("Error opening file hTemp.tmp for reading");
      return -1;
   }
   
   /* file is opened - read and get MAC */
   do
   {
      fgets(MAC, MAX_LINE, hTemp);
   } while(!isdigit(MAC[0]));
   fclose(hTemp);
   system("del hTemp.tmp");

    MAC[17] = '\0';
    
    return 0;
}
