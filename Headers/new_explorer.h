//
// Created by Valentin on 30/04/2022.
//

#ifndef NEWEXPLORER_NEW_EXPLORER_H
#define NEWEXPLORER_NEW_EXPLORER_H

#include <time.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>

typedef struct {

} tags_t;

typedef struct {
    // END-USER VARIABLES
    tags_t tags;
    char filename[FILENAME_MAX + 1];
    time_t modifiedAt;
    unsigned short type;
    long fileSize;
    // BACK-END VARIABLES
    char fullpath[PATH_MAX + 1];
} entry_t;

typedef struct {
    entry_t *entries;
    unsigned int entriesCount;
} repository_t;

typedef struct {
    DIR *dir;
    char cursorPath[PATH_MAX + 1];
} cursor_t;

int iterateCurrentDir(cursor_t *current, repository_t *repo);
void dumpEntries(repository_t *repo);
void sortRepoByDefault(repository_t *repo);

#endif //NEWEXPLORER_NEW_EXPLORER_H
