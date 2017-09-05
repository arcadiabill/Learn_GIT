/*────────────────────────────────────────────────────────── ListDir.c
 │ Function: ListDir [-fhqtv][DirName]
 │ Author  : william h robertson
 │
 │ Purpose : List directory tree starting from DirName. If directory
 │           not given, start from current directory. Optionally list
 │           files as well as directories. Shows number of Artists &
 │           number of Albums at the end.
 │
 │ Params  : -h, --help     shows help
 │           -f, --files    lists files as well as directories
 │           -t, --true     lists files as well as directories
 │           -q, --quiet    don't show program header line
 │           -v, --version  show version
 │           DirName        starting directory, default is current
 │
 │ Returns : -1 on, 0 otherwise
 │
 │ Usage   : ListDir              List Dirs starting with current
 │           ListDir g:\Music     List Dirs starting with g:\Music
 │           ListDir -t g:\Music  List Dirs & Files of g:\Music
 │
 │ Notes   : Based on code found in Linux Programming 4th ed 2008
 │           Neil Matthew & Richard Stones
 │           Wiley Publishing Pages 122-126
 │           Modified to work with Windows
 │
 │ Compile : gcc ListDir.c -o ListDir
 │
 │   Ver     Date     Who  Description of the Change
 │     0  07-20-2016  whr  Initial release
 │     1  09-01-2017  whr  It was called PrintDir, Minor cleanup &
 │                         added cmd line options.
 └────────────────────────────────────────────────────────────────────
 */
#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

#define BUFSIZE MAX_PATH
#define true       1
#define false      0

int nDIRs    = 0;       // Global parameters
int nFILES   = 0;
int nArtists = 0;
int nAlbums  = 0;

void   usage();
void   ListDir(char *dir, int indent, int listFiles);

int
main(int argc, char* argv[])
{
   DWORD dwRet;
   TCHAR Buffer[BUFSIZE];
   static struct option long_options[] = {
      {"files",   no_argument, 0, 'f'},
      {"help",    no_argument, 0, 'h'},
      {"quiet",   no_argument, 0, 'q'},
      {"true",    no_argument, 0, 't'},
      {"version", no_argument, 0, 'v'},
      {0, 0, 0, 0}
   };

   // Process Flags & DIRs
   int   index     = 0;
   int   opt       = 0;
   int   listFiles = false;  // if true, also lists filenames
   int   quiet     = false;  // if true, surpresses pgm hdr output
   int   cntr      = 0;
   char *topdir;

   while ((opt = getopt_long(argc, argv, "fhqtv",
            long_options, &index)) != -1){
      switch (opt){
      case 'h':
         usage();       // usage() exits the pgm, exit below redundant
         exit(EXIT_SUCCESS);
      case 'q':
         ++cntr;
         quiet = true;
         break;
      case 'f':         // Set listFiles to true
      case 't':         // on either flag f or t
         ++cntr;
         listFiles = true;
         break;
      case 'v':
         usage();       // usage() exits the pgm, exit below redundant
         exit(EXIT_SUCCESS);
      }
   }

   // Process current DIR if starting directory not given
   if (argc - cntr == 1) {
      dwRet = GetCurrentDirectory(BUFSIZE, Buffer);
      if( dwRet == 0 && !listFiles ) {
         fprintf(stderr, "GetCurrentDirectory failed (%ld)\n",
                    GetLastError());
         exit(EXIT_FAILURE);
      }
      if( dwRet > BUFSIZE ) {
         fprintf(stderr, "Buffer size %d needs to be at least %ld\n",
                    BUFSIZE, dwRet);
         exit(EXIT_FAILURE);
      }
      topdir=Buffer;

   // Otherwise Process the directory given on cmd line
   } else {
      topdir=argv[argc - 1];
   }

   if(!quiet)
      printf("Directory scan of %s\n", topdir);

   // Recursive routine will do all the processing
   ListDir(topdir, 0, listFiles);

   // Get largest length needed to keep the numbers aligned
   cntr = nDIRs > nFILES ? nDIRs : nFILES;
   cntr = strlen(itoa(cntr, Buffer, 10));

   printf("\nNumber of Artists    : %*d\n", cntr, nArtists);
   printf(  "Number of Albums     : %*d\n", cntr, nAlbums);
   printf(  "Number of Directories: %*d\n", cntr, nDIRs);
   printf(  "Number of Files      : %*d\n", cntr, nFILES);

   exit(EXIT_SUCCESS);
}


/*──────────────────────────────────────────────────────────── usage()
 │ Purpose: Show proper usage
 └────────────────────────────────────────────────────────────────────
 */
void
usage()
{
   fprintf(stderr,
      "ListDir version 1.0  2017-Sep-01\n\n"
      "  Usage: ListDir [-htqv] [DirName]\n"
      "    -h, --help    = help\n"
      "    -f, --files   = print filenames as well as direcories\n"
      "    -t, --true    = print filenames as well as direcories\n"
      "    -q, --quiet   = does nothing at this time\n"
      "    -v, --version = print version\n"
      "    [DirName]     = Starting directory, default is current\n");
   exit(EXIT_SUCCESS);
}


/*────────────────────────────────────────────────────────── ListDir()
 │ Purpose: Does all the work of listing the DIRs & FILEs
 │          Recursive routine.
 └────────────────────────────────────────────────────────────────────
 */
void
ListDir(char *dir, int indent, int listFiles)
{
   DIR   *dp;
   struct dirent *entry;
   struct stat statbuf;
   int    spaces = indent*2;

   if((dp = opendir(dir)) == NULL) {
      fprintf(stderr,"cannot open directory: %s\n", dir);
     exit(EXIT_FAILURE);
   }
   chdir(dir);
   while((entry = readdir(dp)) != NULL) {
      stat(entry->d_name,&statbuf);

      if(S_ISDIR(statbuf.st_mode)) {
         /* Found a directory, but ignore . and .. */
         if(strcmp( ".",entry->d_name) == 0 ||
            strcmp("..",entry->d_name) == 0)
            continue;

         // New Directory -- Artist with have 2 spaces before name
         if(spaces == 2) ++nArtists;
         if(spaces == 4) ++nAlbums;
         printf("%*s%s\n", spaces,"",entry->d_name);

         /* Recurse at a new indent level */
         ListDir(entry->d_name, indent+1, listFiles);
         ++nDIRs;
      } else {
         if (listFiles)
            printf("%*s%s\n", spaces,"",entry->d_name);

         nFILES++;
      }
   }
   chdir("..");
   closedir(dp);
}
