#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char **argv)
{
   struct stat fileStat;

   if(argc != 2){
      puts("Usage: stat filename (show status of filename.");
      return 1;
   }
      
   errno = 0;                // Global error variable
   if(stat(argv[1],&fileStat) < 0){
      perror("Error");
      return errno;
   }
       

   printf("\nInformation for %s\n",argv[1]);
   printf("---------------------------\n");
   printf("File Size: \t\t%i bytes\n",fileStat.st_size);
   printf("Number of Links: \t%d\n",fileStat.st_nlink);
   printf("File inode: \t\t%d\n",fileStat.st_ino);

   printf("File Permissions: \t");
   printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
   printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
   printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
   printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
   printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
   printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
   printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
   printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
   printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
   printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
   printf("\n\n");

//    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

   return 0;
}