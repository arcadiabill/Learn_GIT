#include <stdio.h>
#include <string.h>

int main(void)
{
	char *path ="c:/ab/cde/fg.out";
	char *ssc, *sav = path;

	int l = 0;

	printf("%c %c are the Path Separators\n", DIR_SEPARATOR, DIR_SEPARATOR_2);

	ssc = strstr(path, "/");
	do{
  	  l = strlen(ssc) + 1;
    	path = &path[strlen(path)-l+2];
    	ssc = strstr(path, "/");
	}while(ssc);
	printf("%s\t%s\n", path, sav);

	return 0;
}
