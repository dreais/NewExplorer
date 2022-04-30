#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>

#include <time.h>

#include <stdio.h>

int main(void)
{
    DIR *mainDir;
    struct dirent *dir;
    struct stat buff;
    char FPATH[PATH_MAX + 1];
    char relativePath[PATH_MAX + 1] = "C:\\";

    mainDir = opendir(relativePath);

    while ((dir = readdir(mainDir)) != NULL) {
        strcpy(FPATH, relativePath);
        strcat(FPATH, dir->d_name);
        if ((stat(FPATH, &buff)) == 0) {
            printf("%s:\t", (S_ISREG(buff.st_mode)) ? "FILE" : "DIR");
            printf("%s\t", ctime(&buff.st_mtime));
            printf("%s\n", dir->d_name);
        } else {
            printf("Could not retrieve information about <%s>\n", dir->d_name);
        }
    }

    closedir(mainDir);

    return 0;
}
