#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *exten;
char *file_from_path(char *pathname)
{
        char *fname = NULL;
        int diff;
        char *file=strrchr(pathname,'\\')+1;
        exten=strrchr(file,'.');
        diff=exten-file;
        fname=(char *)malloc(diff);

        if (pathname)
        {
                strncpy(fname,file,diff);
        }
      return fname;
}

int main (void)
{

        char pathname[] = "C:\\Users\\Michael\\Desktop\\File Directory\\example.doc";
        char *fname = file_from_path(pathname);
        printf("path     : '%s'\nfilename : '%s'\n", pathname, fname != NULL ? fname    :"(null)");
        printf("extension: '%s'\n",exten);
        printf("\n");
        system("pause");
        return 0;
}
