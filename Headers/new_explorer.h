//
// Created by Valentin on 30/04/2022.
//

#ifndef NEWEXPLORER_NEW_EXPLORER_H
#define NEWEXPLORER_NEW_EXPLORER_H

#include <time.h>
#include <limits.h>

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

#endif //NEWEXPLORER_NEW_EXPLORER_H
