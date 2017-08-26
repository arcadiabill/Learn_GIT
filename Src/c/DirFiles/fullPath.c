#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <direct.h>
 
void DisplayFullPath(char *relPath)
{
  /* Buffer */
  char full[_MAX_PATH];
 
  if(_fullpath(full, relPath, _MAX_PATH) != NULL)
    printf("The full path is: %s\n", full);
  else
    printf("Invalid path.\n");
}
 
int main(void)
{
  DisplayFullPath("test.txt");
  DisplayFullPath("d:\\my\\guess\\oranges.txt");
  DisplayFullPath("..\\test.txt");
  DisplayFullPath(".");
return 0;
}