#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "new_explorer.h"

int main(void)
{
    // VARIABLES
    cursor_t current;
    repository_t records;
    int errorCheck = 0;

    struct timeval startTv, endTv;
    gettimeofday(&startTv, NULL);

    // RAYLIB INIT

    // GET TO DEFAULT DIRECTORY
    strcpy(current.cursorPath, "C:\\rear");
    current.dir = opendir(current.cursorPath);
    if (current.dir == NULL) {
        fprintf(stderr, "%s (value: <%s>)\n", strerror(errno), current.cursorPath);
        exit(errno);
    }

    errorCheck = iterateCurrentDir(&current, &records);
    if (errorCheck != 0) {
        fprintf(stderr, "Failed to read directory <%s>\n", current.cursorPath);
        exit(errorCheck);
    }
    dumpEntries(&records);

    // MAIN LOOP STARTS HERE

    // RAYLIB DE-INIT

    // ANY DIR TO CLOSE BELOW
    if (closedir(current.dir) != 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(errno);
    }
    return 0;
}
