#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
        char resolved_path[100];
        realpath("..", resolved_path);
        printf("\n%s\n",resolved_path);
        return 0;
}
