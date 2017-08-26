#include <sys/types.h> 
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

/* The following macros will test whether a file is of the specified type.
   The value m supplied to the macros is the value of st_mode from a stat
   structure. The macro evaluates to a non-zero value if the test is true,
   0 if the test is false.

S_ISBLK(m) : Test for a block special file.
S_ISCHR(m) : Test for a character special file.
S_ISDIR(m) : Test for a directory.
S_ISFIFO(m): Test for a pipe or FIFO special file.
S_ISREG(m) : Test for a regular file.
S_ISLNK(m) : Test for a symbolic link.
*/

/* Check for regular file. */
int check_reg(const char *path) {
	struct stat sb;
	return stat(path, &sb) == 0 && S_ISREG(sb.st_mode);
}
 
/* Check for directory. */
int check_dir(const char *path) {
	struct stat sb;
	return stat(path, &sb) == 0 && S_ISDIR(sb.st_mode);
}
 
int main() {
	printf("\nCheckFiles assumes it is in \\src\\c directory\n");
	printf ("ReadDir.c is a regular file? %s\n",
	    check_reg("ReadDir.c") ? "yes" : "no");
	printf ("test is a directory? %s\n",
	    check_dir("test") ? "yes" : "no");
	printf ("CheckFiles.c is a regular file? %s\n",
	    check_reg("CheckFiles.c") ? "yes" : "no");
	printf ("NeedsWork is a directory? %s\n",
	    check_dir("NeedsWork") ? "yes" : "no");
	return 0;
}
