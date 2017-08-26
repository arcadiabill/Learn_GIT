/* ----------------------------------------
 * gcc -D_FILE_OFFSET_BITS=64 largefiles.c
 * ----------------------------------------*/

#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv){
  char *fname;
  int fd;
  if(argc > 1){
    fname = argv[1];
    fprintf(stdout, "Filename is %s\n", fname);
  }
  else {
	  fprintf(stdout, "Usage: largefile fileName\n");
	  return 1;
  }
  fd = open(fname, O_RDONLY);
  if(fd == -1 ){
    perror("Could not open file");
    return 1;
  }
  fprintf(stdout, "File %s was open success fully\n", fname);
  close(fd);
  return 0;
}
