/* Get File Name and split it into components */
#include <stdio.h>   
#include <Windows.h>  
#include <string.h>  
  
int main(int argc, char *argv[])  
{  
    char drive[4];  
    char subdir[MAX_PATH];  
    char fn[MAX_PATH];   
    char exten[MAX_PATH];  
    char exe_path[MAX_PATH];  
    FILE *fs = NULL;  
  
    _splitpath(argv[0], drive, subdir, fn, exten);  
  
    printf("Full file name = %s\n", argv[0]);  
    printf("Drive=%s\nSubdir=%s\nfilename=%s\nExtension=%s\n\n",\
           strlen(drive) == 0 ? "null" : drive, \
           strlen(subdir) == 0 ? "null" : subdir, fn, exten);  
  
    sprintf(exe_path, "%s%s", drive, subdir);  
    if (strlen(exe_path) == 0)  
        sprintf(exe_path, ".\\");  
    printf("strlen(exe_path)=%d\n", strlen(exe_path));  
    printf("exe_path=%s\n", exe_path);    
      
    // Can we use the path? now test it as followed.  
    sprintf(fn, "%stest.log", exe_path);  
    fs = fopen(fn, "w+");  
    fprintf(fs, "%s\n", fn);  
    fclose(fs);  
      
    getchar();  
    return 0;   
}  