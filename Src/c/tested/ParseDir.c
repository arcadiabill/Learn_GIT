/* Works only for current directory. Fails if parameter given to a
   directory other than current directory. Probably need to change
   to the directory and make it the current directory before issuing
   the call.
*/

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  DIR *dir;
  struct dirent *entry;
  struct stat eStat;
  char *root;

  if(argc > 1)
    root = argv[1];
  else
    root = ".";

  dir = opendir(root);
  /* Replacing lstat() with stat() but could use _stat() */
  while((entry = readdir(dir)) != NULL) {
    stat(entry->d_name, &eStat);
	if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
	
    if(S_ISDIR(eStat.st_mode))
      printf("found directory %s\n", entry->d_name);
    else
      printf("     %s is not a dir\n", entry->d_name);
  }
  return 0;
}
