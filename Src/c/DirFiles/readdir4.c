#include <dirent.h>
#include <stdio.h>

int main (int argc, char * argv[])
{
	struct dirent *dirent;
	DIR *dir = opendir("f:\\audio\\lossless");

	while ((dirent = readdir(dir)) != NULL) {
		printf("%s %d\n", dirent->d_name, dirent->attrib);
	}

	closedir(dir);
}
