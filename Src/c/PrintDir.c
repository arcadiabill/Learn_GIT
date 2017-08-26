/* Based on Code Found in
   Linux® Programming 4th Edition 2008
   Neil Matthew & Richard Stones
   Wiley Publishing
   Pages:  122-126
   Modified to work with Windows: whr 06 Jun 2012
*/

// #include <unistd.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

#define BUFSIZE MAX_PATH

int numDirectories = 0;
int numFiles = 0;
char *strdup(const char *s);

void printdir(char *dir, int depth, int printFiles)
{
   DIR *dp;
   struct dirent *entry;
   struct stat statbuf;
   int    spaces = depth*2;

   if((dp = opendir(dir)) == NULL) {
      fprintf(stderr,"cannot open directory: %s\n", dir);
      return;
   }
   chdir(dir);
   while((entry = readdir(dp)) != NULL) {
      stat(entry->d_name,&statbuf);
      if(S_ISDIR(statbuf.st_mode)) {
         /* Found a directory, but ignore . and .. */
         if(strcmp( ".",entry->d_name) == 0 ||
            strcmp("..",entry->d_name) == 0)
            continue;
            printf("%*s%s\n",spaces,"",entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+1, printFiles);
            ++numDirectories;
        }
        else
        { if (printFiles)
           printf("%*s%s\n",spaces,"",entry->d_name);
           numFiles++;
        }
    }
    chdir("..");
    closedir(dp);
}

/*  Now we move onto the main function.  */

int main(int argc, char* argv[])
{
   DWORD dwRet;
   TCHAR Buffer[BUFSIZE];
   char *topdir;
   int   printFiles = 0;                  // Set to 1 if filenames are to be printed
   char *old_locale, *saved_locale;       // Going to change the locale to print non-ascii

   /* Get the name of the current locale.  */
   old_locale = setlocale(LC_ALL, NULL);

   /* Copy the name so it won’t be clobbered by setlocale. */
   saved_locale = strdup (old_locale);
   if (saved_locale == NULL)
   {
      fprintf(stderr, "Out of memory\n");
      return 1;
   }

   /* Now change the locale. */
   if (!setlocale(LC_ALL, ""))
   {
      fprintf(stderr, "Can't set the specified locale! "
            "Check LANG, LC_CTYPE, LC_ALL.\n");
      return 1;
   }

   if (argc == 1)
   {
      dwRet = GetCurrentDirectory(BUFSIZE, Buffer);
      if( dwRet == 0 )
      {
         printf("GetCurrentDirectory failed (%ld)\n", GetLastError());
         return 0;
      }
      if( dwRet > BUFSIZE )
      {
         printf("Buffer size of %d needs to be at least %ld\n", BUFSIZE, dwRet);
         return 0;
      }
      topdir=Buffer;
   }
   else
      topdir=argv[1];

   if (argc == 3 && argv[2][0] == 't')
   {
      printFiles = 1;
   }
    
   printf("Directory scan of %s\n",topdir);
   printdir(topdir, 0, printFiles);
   printf("Number of Directories: %d\n", numDirectories);
   if (printFiles) printf("Number of Files      : %d\n", numFiles);

   if (argc == 1)
   {
      printf("\n%s:  v1.0  (30 Sep 2014 whr)\n", argv[0]);
      printf("  Usage: %s [[<Start Dir>] [true]]\n", argv[0]);
      printf("           where [Start Dir] and [true] are optional\n");
      printf("           Start Dir defaults to current directory\n\n");
      printf("           To print filenames, a Directory must be given followed by the letter: t\n");
      printf("           Otherwise only the directory names are listed.\n\n");
   }

   return 0;
}
