/* Get MS Version of gcc __MSVCRT_VERSION__ 
   32-bit CPU
	
	Compiled with: gcc -omsvcrtVer msvcrtVer.c
	gcc version  : (tdm-1) 5.1.0
	
	Output       : 0x0600
	
	stdio.h      : Switches to 64-bit fseek, ... only if
	               __MSVCRT_VERSION__ >= 0x800  (line 243 of stdio.h)
*/
#include <stdio.h>

int main(void)
{
	printf("__MSVCRT_VERSION__ = 0x%.4x\n", __MSVCRT_VERSION__);
#ifdef  __MSVCRT_VERSION__
#undef  __MSVCRT_VERSION__
#endif
#define __MSVCRT_VERSION__ 0x999	
	printf("__MSVCRT_VERSION__ = 0x%.4x\n", __MSVCRT_VERSION__);

	return 0;
}