#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define BUFSIZE MAX_PATH

int main()
{
    char path[BUFSIZE];
	TCHAR Buffer[BUFSIZE];
	unsigned int dwRet = 0;
	
	dwRet = GetCurrentDirectory(BUFSIZE, Buffer);
	printf("Length of string & name of current directory: %u, %s\n", dwRet, Buffer);
    GetModuleFileName(NULL, path, sizeof(path));
    printf("Path: %s\n", path);
//    system("pause");
    return 0;
}
