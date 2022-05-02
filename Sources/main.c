#include <errno.h>
#include <stdlib.h>
#include "new_explorer.h"

#include <sys/time.h>

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
    strcpy(current.cursorPath, "C:\\");
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

    gettimeofday(&endTv, NULL);
    fprintf(stderr, "Execution time:\t%fs\n", (float) (endTv.tv_usec - startTv.tv_usec)/1000000.0f);
    return 0;
}
