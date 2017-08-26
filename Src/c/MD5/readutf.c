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
    wchar_t *inname = L"test_bin.dat";
    FILE *infile;
    wchar_t line_buffer[BUFSIZ]; /* BUFSIZ is defined if you include stdio.h */

    infile = _wfopen(inname,L"rb");
    if (!infile) {
        wprintf(L"\nfile '%s' not found\n", inname);
        return 0;
    }
    wprintf(L"\n%s\n\n", inname);

    /*Reading data from file into temporary buffer*/
    while (fread(line_buffer,1,13,infile)) {
        /* note that the newline is in the buffer */
        if ( wcscmp ( L"ب" , line_buffer ) == 0 ){
             wprintf(L"YES!\n");
        }else{
             wprintf(L"NO!\n", line_buffer);
        }
    }
    /*Closing File*/
    fclose(infile);
    return 0;
}
