//
// Created by Valentin on 01/05/2022.
//

#include <stdlib.h>
#include <sys/stat.h>
#include "new_explorer.h"

static unsigned int countFiles(cursor_t *current)
{
    struct dirent *entry;
    unsigned int entriesCount = 0;

    while ((entry = readdir(current->dir)) != NULL) {
        entriesCount++;
    }
    return entriesCount;
}

void dumpEntries(repository_t *repo)
{
    for (int i = 0; i < repo->entriesCount; i++) {
        fprintf(stderr, "%s:\t", S_ISDIR(repo->entries[i].type) ? "DIR" : "FILE");
        fprintf(stderr, "<%s>\n", repo->entries[i].filename);
    }
}

int iterateCurrentDir(cursor_t *current, repository_t *repo)
{
    struct dirent *entry;
    unsigned int cnt = 0;
    int error = 0;
    struct stat fileInfo;

    repo->entriesCount = countFiles(current);
    repo->entries = malloc(sizeof(entry_t) * repo->entriesCount);

    rewinddir(current->dir);
    if (repo->entries == NULL) {
        fprintf(stderr, "Could not allocate records.\n");
        return 1;
    }
    while ((entry = readdir(current->dir)) != NULL) {
        error = strcpy_s(repo->entries[cnt].filename, FILENAME_MAX, entry->d_name);
        if (error != 0) {
            fprintf(stderr, "Could not copy filename to Entry <%d> labeled <%s>.\n", cnt, entry->d_name);
            return 1;
        }
        strcpy(repo->entries[cnt].fullpath, current->cursorPath);
        strcat(repo->entries[cnt].fullpath, entry->d_name);

        stat(repo->entries[cnt].fullpath, &fileInfo);
        repo->entries[cnt].modifiedAt = fileInfo.st_mtime;
        repo->entries[cnt].fileSize = fileInfo.st_size;
        repo->entries[cnt].type = fileInfo.st_mode;
        cnt++;
    }

    return 0;
}