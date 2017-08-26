#define _FILE_OFFSET_BITS 64
#include <stdio.h>
 
int main(int argc, char * argv[])
{
    FILE *fptr;
	 
	 /* Get File name from argv[1] */
	 if(argc < 2)
	 {
		 printf("Usage: LargeSize fileName\n");
		 return -1;
	 }

#ifdef  __MSVCRT_VERSION__
#undef  __MSVCRT_VERSION__
#endif
#define __MSVCRT_VERSION__ 0x800	
	printf("__MSVCRT_VERSION__ = 0x%.4x\n", __MSVCRT_VERSION__);
	 
	 if((fptr = fopen(argv[1],"r")) == NULL)
	 {
		 printf("Error: Can't find file %s\n", argv[1]);
		 return -1;
	 }

	 _fseeki64(fptr, (__int64)0, SEEK_END);
	 printf("File Name: %s, Size: %lld\n", argv[1], _ftelli64(fptr));
      
    return 0;
}
