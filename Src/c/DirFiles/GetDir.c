#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int getdir(string rootDir, vector<string> &files)
{
    DIR *dir; //the directory
    struct dirent *dp;

    //open the directory
    if((dir  = opendir(rootDir.c_str())) == NULL)
    {
        cout << "Error(" << errno << ") opening " << rootDir << endl;
        return errno;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        files.push_back(string(dp->d_name));

     //   if(directory do something) //need help here

     //   if(file do something else)
    }

    closedir(dir);
    return 0;
}

int main()
{
    string rootDir = string(".");
    vector<string> files = vector<string>();
    getdir(rootDir, files);

    for (unsigned int i = 0; i < files.size(); i++)
        cout << files[i] << endl;

    return 0;
}