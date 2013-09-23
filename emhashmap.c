#include "emhashmap.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

HashMap* emhashmap_create(int capacity) {
    HashMap* map = (HashMap*) malloc(sizeof(HashMap));
    emhashmap_initialize(map, capacity);
    return map;
}

void emhashmap_destroy(HashMap* map) {
    if(map->buckets != NULL && map->capacity > 0) {
        free(map->buckets);
    }
}

bool emhashmap_initialize(HashMap* map, int capacity) {
    map->capacity = capacity;
    map->buckets = (LinkedList*) malloc(sizeof(LinkedList) * map->capacity);
    return map->buckets != NULL;
}

bool emhashmap_contains(HashMap* map, int key) {
}

bool emhashmap_put(HashMap* map, int key, void* value) {
}

void* emhashmap_remove(HashMap* map, int key) {
}

int emhashmap_size(HashMap* map) {
}

bool emhashmap_is_empty(HashMap* map) {
    return emhashmap_size(map) > 0;
}
