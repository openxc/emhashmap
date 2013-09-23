#include "emhashmap.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

HashMap* emhashmap_create(int capacity) {
    HashMap* map = (HashMap*) malloc(sizeof(HashMap));
}

void emhashmap_destroy(HashMap* map) {
}

void emhashmap_initialize(HashMap* map) {
}

bool emhashmap_contains(HashMap* map, int key) {
}

bool emhashmap_put(HashMap* map, int key, void* value) {
}

bool emhashmap_remove(HashMap* map, int key) {
}

void emhashmap_clear(HashMap* map) {
}

int emhashmap_size(HashMap* map) {
}

bool emhashmap_is_empty(HashMap* map) {
}
