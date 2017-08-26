#define UNICODE
#ifdef UNICODE
#define _UNICODE
#else
#define _MBCS
#endif

#include <stdio.h>
#include <wchar.h>

int main()
{
     /*Data to be stored in file*/
     wchar_t line_buffer[BUFSIZ]=L"ب";
     /*Opening file for writing in binary mode*/
     FILE *infile=fopen("test_bin.dat","wb");
     /*Writing data to file*/
     fwrite(line_buffer, 1, 13, infile);
     /*Closing File*/
     fclose(infile);

    return 0;
}
