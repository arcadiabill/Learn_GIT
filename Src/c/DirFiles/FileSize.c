/* Program to find the file size of the file entered on the command line
   On 32-bit systems you should compile this with the option
      -D_FILE_OFFSET_BITS=64
*/
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

long long fsize(const char *filename);

int
main(int argc, char *argv[])
{
	long fileSize;
	
	if( argc < 2 )
	{
		printf("\nUsage: FileSize filename\n");
		return -1;
	}
	
	fileSize = (long) fsize(argv[1]);
	if(fileSize == -1)
	{
		fprintf(stderr, "Cannot determine size of %s: %s\n", argv[1], strerror(errno));
		return -1;
	}
	else
		fprintf(stdout, "File size of %s: %lld\n", argv[1], fileSize);

	return 0;
}

long long
fsize(const char *filename)
{
	struct stat st;

   if (stat(filename, &st) == 0)
		return (long long)st.st_size;
	else
		return -1L;
}
