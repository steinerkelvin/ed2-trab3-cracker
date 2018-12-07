#include "space.h"

Space space_alloc(size_t num, size_t size) {
    char *ptr = (char*) calloc(num, size);
    Space space = {
        .item_size = size,
        .max_num = num,
        .num = 0,
        .ptr = ptr,
    };
    return space;
}

void * space_getNext(Space *space) {
    assert(space->num < space->max_num);
    char *ret =
        space->ptr + (space->item_size * space->num);
    space->num++;
    return ret;
}

void space_free(Space *space) {
    free(space->ptr);
}
