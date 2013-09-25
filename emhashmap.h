#ifndef _EMHASHMAP_H_
#define _EMHASHMAP_H_

#include "emlist/emlist.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Public: An entry in the map.
 *
 * key - the entry key, currently supports only integers.
 * value - a pointer to the value. this must be allocated with malloc or
 *      be in global scope, and the map entry does not take ownership of its
 *      memory.
 */
struct MapEntry {
   int key;
   void* value;
};
typedef struct MapEntry MapEntry;

struct HashMap {
   int capacity;
   LinkedList* buckets;
};
typedef struct HashMap HashMap;

HashMap* emhashmap_create(int capacity);

void emhashmap_destroy(HashMap* map);

bool emhashmap_initialize(HashMap* map, int capacity);

void* emhashmap_get(HashMap* map, int key);

bool emhashmap_contains(HashMap* map, int key);

bool emhashmap_put(HashMap* map, int key, void* value);

/* Public: Remove a value with the given key from the map.
 *
 * Returns the value pointer if found in the map and removed - the map user is
 * responsible for freeing any memory associated with that pointer.
 * Returns NULL if the key was not in the map.
 */
void* emhashmap_remove(HashMap* map, int key);

int emhashmap_size(HashMap* map);

bool emhashmap_is_empty(HashMap* map);

#ifdef __cplusplus
}
#endif

#endif // _EMHASHMAP_H_
