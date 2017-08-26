#include <stdio.h>
#include <stdlib.h>
#include <io.h>

int main(void)
{
	struct _finddata_t myfile;
	intptr_t p;
	char fileSpec[] = "*.*";

	p = _findfirst(fileSpec, &myfile);
	if(p == -1)
	{printf("'%s' not found.\n", fileSpec);
		return -1;
	}

	if(myfile.attrib & _A_SUBDIR)
		printf("%15s\t%s\n", "<DIR>", myfile.name);
	else
		printf("%15ut%s\n", (unsigned int)myfile.size, myfile.name);
	while(_findnext(p, &myfile) != -1)
	{
		if(myfile.attrib & _A_SUBDIR)
			printf("%15s\t%s\n", "<DIR>", myfile.name);
		else
			printf("%15u\t%s\n", (unsigned int)myfile.size, myfile.name);
	}
	_findclose(p);
	return 0;
}
