#include <stdio.h>
#include <strings.h>

void *padStr(char *str, int padLen)
{
	int lenStr = strlen(str);

	if(lenStr < padLen)
		for(int i = 0; i < padLen; i++)
			str[lenStr+i] = ' ';

	str[padLen] = '\0';
}

int
main()
{
	char str[101];
	char *test;

	strncat(str, "Less than 30 chars", 100);
	padStr(str, 30);
	printf("len:%3d <%s>\n", strlen(str), str);

	str[0] = '\0';
	strncat(str, "This is more than thirty characters by a little bit", 100);
	padStr(str, 30);
	printf("len:%3d <%s>\n", strlen(str), str);

    return 0;
}