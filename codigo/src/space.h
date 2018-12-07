#if !defined(SPACE_H)
#define SPACE_H

#include <stdlib.h>
#include <assert.h>

typedef struct space {
    size_t item_size;
    size_t max_num;
    size_t num;
    char *ptr;
} Space;

static inline Space space_alloc(size_t num, size_t size) {
    char *ptr = (char*) calloc(num, size);
    Space space = {
        .item_size = size,
        .max_num = num,
        .num = 0,
        .ptr = ptr,
    };
    return space;
}

static inline void * space_getNext(Space *space) {
    assert(space->num < space->max_num);
    char *ret =
        space->ptr + (space->item_size * space->num);
    space->num++;
    return ret;
}

static inline void space_free(Space *space) {
    free(space->ptr);
}


#endif // SPACE_H
