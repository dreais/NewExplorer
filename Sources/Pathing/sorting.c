//
// Created by Valentin on 01/05/2022.
//

#include <sys/stat.h>
#include "new_explorer.h"

static int countDirInRepo(repository_t *repo)
{
    int count = 0;
    for (unsigned int i = 0; i < repo->entriesCount; i++) {
        if (S_ISDIR(repo->entries[i].type)) {
            count++;
        }
    }
    return count;
}

void sort_byTypeByName(repository_t *repo)
{
    entry_t swap;
    int boundA = 0, boundB;

    boundB = countDirInRepo(repo);
    for (int i = 0; i < boundB; i++) {
        if (!S_ISDIR(repo->entries[i].type)) {
            for (int j = boundB; j < repo->entriesCount; j++) {
                if (S_ISDIR(repo->entries[j].type)) {
                    swap = repo->entries[j];
                    repo->entries[j] = repo->entries[i];
                    repo->entries[i] = swap;
                }
            }
        }
    }
}

void sortRepoByDefault(repository_t *repo)
{
    // TODO: work with func ptr and configuration will be from user
    sort_byTypeByName(repo);
}