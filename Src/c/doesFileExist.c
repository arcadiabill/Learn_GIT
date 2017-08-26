/*------------------------------------------------- FileName.c -------
 | Function: doesFileExists(const char* filename)
 | Author  : william h robertson
 |
 | Purpose : Check if a file exists using the stat() function
 |
 | Params  : char *filename - File name to check
 |
 | Returns : 0 - If file doesn't exists or don't have access
 |           1 - If file exists
 |
 | Usage   : pdf = isPDFfile( char * PDFfile);
 |
 | Notes   : Function limited to naive checking. Does not verify
 |           that the file has the correct structure.
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    12-26-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
/*
 * Check if a file exist using stat() function
 * return 1 if the file exist otherwise return 0
 */
int doesFileExists(const char* filename)
{
   FILE *tmp;
   
   struct stat buffer;
   int exist = stat(filename, &buffer);
   if(exist == 0)
      return 1;		// File Exists
   else
   {
      // Try fopen
      if((tmp = fopen(filename, "rb encoding=utf-8")) != NULL)
      {
         fclose(tmp);
         
         // remove later -- didn't work
         printf("Does File Exist Experiment\n");
         printf("%s\n", filename);
         return 1;
      }

      // Try _wfopen()  -- didn't work
      if((tmp = _wfopen((const wchar_t *)filename, (const wchar_t*) "rb | _O_U8TEXT | _O_UTF8")) != NULL)
      {
         fclose(tmp);
         return 1;
      }
   }
   
   return 0;		// File Doesn't Exist or can't open
}
