#include "hash.h"
#include <stdio.h>
#include <assert.h>

/* http://www.cse.yorku.ca/~oz/hash.html */
size_t djb2_file(char *path)
{
    FILE *file;
    int chunk;
    size_t hash;

    file = fopen(path, "rb");
    assert(file != NULL);

    hash = 5381;
    while ((chunk = fgetc(file)) != EOF) {
        hash = ((hash << 5) + hash) + chunk;
    }

    fclose(file);
    return hash;
}