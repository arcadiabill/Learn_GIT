// File: makedir.c
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	char * dir = ".\\testTemp";

	system("cls");
	printf("makedir: Test to make a directory '.\\testTemp' & then remove it\n\n");
	if( _mkdir(dir) == 0)
	{
		printf("Directory '%s' was successfully created\n", dir);
		system("dir");
		if( _rmdir(dir) == 0)
		{
			printf("\nDirectory '%s' was successfully removed\n", dir);
			system("dir");
		}
		else
		{
			printf("Problem removing directory '%s'\n", dir);
			perror("Error: ");
		}
	}
	else
	{
			printf("Directory '\\testTemp' was not created.\n");
			perror("Error: ");
	}
	return 0;
}
