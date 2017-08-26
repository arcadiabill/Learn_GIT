/* the use of the 32-bit _find() functions to print a list of all files (and their attributes) in the current directory. */
#include <stdio.h>
#include <stdio.h>
#include <io.h>
#include <time.h>
#include <direct.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
  char       *path = ".";
  struct     _finddata_t c_file;
  long       hFile;

  if(argc > 1 )
  {
     path = argv[1];
  }	 
  printf("Change to %s\n", path);
  if(_chdir(path))
  {
    printf("Unable to locate the directory: %s\n", path);
    return -1;
  }

  /* find first in the current directory skipping . & .. */
  hFile = (long) _findfirst("*.*", &c_file);
  printf("Listing of files in the directory %s\n\n", path);
  printf("\nRDO HID SYS ARC DIR  DATE                             SIZE  FILE\n");
  printf(  "--- --- --- --- ---  ------------------------  -----------  ----\n");
 
  /* find the rest of the files */
  do
  {
    /* skip . & .. */
    if( strcmp(c_file.name, "." ) == 0 ||
        strcmp(c_file.name, "..") == 0 )
    {
      continue;
    }
    printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  ");
    printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  ");
    printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  ");
    printf((c_file.attrib & _A_ARCH)   ? " Y  " : " N  ");
    if(c_file.attrib & _A_SUBDIR)
	{
		printf(" Y  ");
		printf(" %.24s    Directory  %-12s \n", ctime(&(c_file.time_write)), c_file.name);
	}
	else
	{
		printf( " N  ");
		printf(" %.24s  %11ld  %-12s \n", ctime(&(c_file.time_write)), c_file.size, c_file.name);
	}
  } while(_findnext(hFile, &c_file) == 0);
  _findclose(hFile);
 
  return 0;
}
 