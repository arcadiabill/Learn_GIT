#define FILENAME "I:\\iso files\\Windows_7_64bit.iso"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char * argv[]) {
	off64_t file_size;
	struct _stat64 stbuf;
	int fd;

	fd = open(FILENAME, O_RDONLY);
	if (fd == -1) {
	/* Handle error */
	printf("Couldn't open file: %s\n", FILENAME);
	return 1;
	}
  
	if ((fstat(fd, &stbuf) != 0) || (!S_ISREG(stbuf.st_mode))) {
	/* Handle error */
	printf("Error: fstat\n");
	return 1;
	}
  
	file_size = stbuf.st_size;
	printf("Size of off_t %d\n", sizeof(off64_t));
	printf("File Size: %I64d\n", file_size);
	
	return 0;
}
