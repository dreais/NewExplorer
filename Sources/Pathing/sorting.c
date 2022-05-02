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

static unsigned int getStringValue(const char *string)
{
    unsigned int value = 0;

    for (int i = 0; string[i]; i++) {
        value += string[i];
    }
    return value;
}

void sortNamesBounds(repository_t *repo, int boundA, int boundB)
{
    entry_t swap;

    for (int i = boundA; i < boundB; i++) {
        for (int j = i; j < boundB; j++) {
            if (repo->entries[i].filename[0] > repo->entries[j].filename[0]) {
                swap = repo->entries[j];
                repo->entries[j] = repo->entries[i];
                repo->entries[i] = swap;
            }
        }
    }
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
    sortNamesBounds(repo, boundA, boundB);
    sortNamesBounds(repo, boundB + 1, (int) repo->entriesCount);
}

void sortRepoByDefault(repository_t *repo)
{
    // TODO: work with func ptr and configuration will be from user
    sort_byTypeByName(repo);
}