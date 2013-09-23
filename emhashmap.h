#ifndef _EMHASHMAP_H_
#define _EMHASHMAP_H_

#include "emlist.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MapEntry {
   int key;
   void* value;
};

struct HashMap {
   int capacity;
   int load_factor;
   LinkedList* buckets;
};

HashMap* emhashmap_create();

void emhashmap_destroy(HashMap* map);

void emhashmap_initialize(HashMap* map);

bool emhashmap_contains(HashMap* map, int key);

bool emhashmap_put(HashMap* map, int key, void* value);

bool emhashmap_remove(HashMap* map, int key);

void emhashmap_clear(HashMap* map);

int emhashmap_size(HashMap* map);

bool emhashmap_is_empty(HashMap* map);

#ifdef __cplusplus
}
#endif

#endif // _EMHASHMAP_H_
