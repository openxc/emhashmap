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

/* Public: A fixed bucket capacity HashMap container, supporting unlimited
 * objects (but with an increasing load factor).
 *
 * capacity - the number of buckets in the hash map.
 * buckets - a dynamically allocated array of LinkedLists, representing the
 * buckets.
 */
struct HashMap {
   int capacity;
   LinkedList* buckets;
};
typedef struct HashMap HashMap;

struct MapIterator {
   HashMap* map;
   int current_bucket;
   LinkedListIterator list_iterator;
};
typedef struct MapIterator MapIterator;

/* Public: Allocate a new HashMap with the given capacity and return a pointer
 * to it.
 * You're in charge of the map's memory now, so make sure to call
 * emhashmap_destroy(HashMap*).
 *
 * capacity - the fixed capacity for the new map.
 *
 * Returns a pointer to a new HashMap, or NULL if one could not be allocated.
 */
HashMap* emhashmap_create(int capacity);

/* Public: Free the memory associated with a map previously created on the heap.
 *
 * This will *not* free the memory associated with any values stored in the map
 * - only the map and its map entry objects.
 */
void emhashmap_destroy(HashMap* map);

/* Public: Initialize a map with the given capacity.
 *
 * This allocates memory for the buckets to serve the capacity, so make sure to
 * call emhashmap_destroy(HashMap*) after done with this map.
 *
 * map - a pointer to the map to initialize. It must already be allocated on the
 *      stack or heap.
 * capacity - the initial capacity for the map.
 *
 * Returns true if the map was initialize successfully, false if space could not
 * be allocated for the buckets.
 */
bool emhashmap_initialize(HashMap* map, int capacity);

/* Public: De-initialize a map, freeing memory for the buckets.
 *
 * This will *not* free the memory associated with any values stored in the map
 * - only the map and its map entry objects.
 *
 * map - a pointer to the map to deinitialize. It must already be allocated on
 *      the stack or heap.
 */
void emhashmap_deinitialize(HashMap* map);

/* Public: Retrive the value for a given key from the map.
 *
 * map - the map to retrive the value.
 * key - the key for this value.
 *
 * Returns the value if found, otherwise NULL.
 */
void* emhashmap_get(HashMap* map, int key);

/* Public: Check if the given key is in the map.
 *
 * map - the map to query.
 * key - the key to check for membership.
 *
 * Returns true if the key is in the map.
 */
bool emhashmap_contains(HashMap* map, int key);

/* Public: Put the value in the map with the given key.
 *
 * If the key already exists in the map, its value will be overridden (so make
 * sure you've freed the memory associated with the existing value).
 */
bool emhashmap_put(HashMap* map, int key, void* value);

/* Public: Remove a value with the given key from the map.
 *
 * map - the map to query.
 * key - the key to remove.
 *
 * Returns the value pointer if found in the map and removed - the map user is
 * responsible for freeing any memory associated with that pointer.
 * Returns NULL if the key was not in the map.
 */
void* emhashmap_remove(HashMap* map, int key);

/* Public: Get the number of keys in the map.
 *
 * map - the map to query.
 *
 * Returns the total number of keys in the map.
 */
int emhashmap_size(HashMap* map);

/* Public: Check if a map is empty.
 *
 * map - the map to query.
 *
 * Returns true if there are no entries in the map.
 */
bool emhashmap_is_empty(HashMap* map);

/* Public: Calculate the current load factor of the map.
 *
 * The load factor is the number of entries / number of buckets.
 *
 * map - the map to query.
 *
 * Returns the current load factor.
 */
float emhashmap_load_factor(HashMap* map);

MapIterator emhashmap_iterator(HashMap* map);

MapEntry* emhashmap_iterator_next(MapIterator* iterator);

#ifdef __cplusplus
}
#endif

#endif // _EMHASHMAP_H_
