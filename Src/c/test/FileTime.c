#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h> // for printf
#include <stdlib.h> // for EXIT_FAILURE

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        struct stat st = {0};
        int ret = lstat(argv[i], &st);
        if (ret == -1) {
            perror("lstat");
            return EXIT_FAILURE;
        }

        printf("%s: mtime sec=%lld nsec=%lld\n", argv[i],
               (long long) st.st_mtime.tv_sec, 
               (long long) st.st_mtime.tv_nsec);
    }

    return 0;
}
