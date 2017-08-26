/*
 * This program displays the names of all files in the current directory.
 */

#include <dirent.h> 
#include <stdio.h> 

int main()
{
  DIR           *d;
  struct dirent *dir;
  d = opendir("d:\\Src\\c");
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
       if (dir->d_type == DT_DIR)
          printf("%s -- Dir\n", dir->d_name);
       else
	      printf("%s %d\n", dir->d_name, dir->d_type);
    } 
    closedir(d);
  }
  else
    return -1;

  return 0;
}
