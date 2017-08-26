#include <unistd.h>					// getcwd() definition
#include <sys/param.h>				// MAXPATHLEN definition
#include <stdio.h>

int main(int argc, char* argv[])	// Always write main() this way!
{
	// Here's a way to use getcwd()
	char path1[MAXPATHLEN];			// This is a buffer for the text
	
	getcwd(path1, MAXPATHLEN);
    printf("\n%s\n", path1);

	return 0;
}