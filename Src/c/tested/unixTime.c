#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t now;
	now = time(NULL); /* time(&now) works to */
	printf("Current UNIX time is %lu\n", now);
	printf("Which is GMT %s\n", asctime(gmtime(&now)));

	/* Unix time runs out at 0x7fffffff, see when that is */
	now = 0x7fffffff;
	printf("UNIXtime will die at %lu\n", now);
	printf("Which is  GMT %s\n", asctime(gmtime(&now)));

	return 0;
}
