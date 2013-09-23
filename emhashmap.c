#include "emhashmap.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* Private: Short and sweet hash function - the key mod capacity. The key type
 * is restricted to int right now.
 */
LinkedList* find_bucket(HashMap* map, int key) {
    return &map->buckets[key % map->capacity];
}

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
    bool result = true;
    for(int i = 0; i < map->capacity; i++) {
        emlist_initialize(&map->buckets[i]);
    }
    return map->buckets != NULL;
}

void* emhashmap_get(HashMap* map, int key) {
    LinkedListIterator iterator = emlist_iterator(find_bucket(map, key));
    LinkedListElement* element = NULL;

    while((element = emlist_iterator_next(&iterator)) != NULL) {
       MapEntry* entry  = (MapEntry*) element->value;
       if(entry->key == key) {
           return entry->value;
       }
    }
    return NULL;
}

bool emhashmap_contains(HashMap* map, int key) {
    return emhashmap_get(map, key) != NULL;
}

bool emhashmap_put(HashMap* map, int key, void* value) {
    LinkedList* bucket = find_bucket(map, key);
    LinkedListIterator iterator = emlist_iterator(bucket);
    LinkedListElement* element = NULL;

    MapEntry* matching_entry = NULL;
    while((element = emlist_iterator_next(&iterator)) != NULL) {
       MapEntry* entry  = (MapEntry*) element->value;
       if(entry->key == key) {
           matching_entry = entry;
           break;
       }
    }

    bool result = true;
    if(matching_entry != NULL) {
        matching_entry->value = value;
    } else {
        MapEntry* new_entry = (MapEntry*) malloc(sizeof(MapEntry));
        if(new_entry == NULL) {
            result = false;
        } else {
            new_entry->key = key;
            new_entry->value = value;
            result &= emlist_insert(bucket, new_entry);
        }
    }
    return true;
}

void* emhashmap_remove(HashMap* map, int key) {
    LinkedList* bucket = find_bucket(map, key);
    LinkedListIterator iterator = emlist_iterator(bucket);
    LinkedListElement* element = NULL;

    MapEntry* matching_entry = NULL;
    while((element = emlist_iterator_next(&iterator)) != NULL) {
       MapEntry* entry  = (MapEntry*) element->value;
       if(entry->key == key) {
           matching_entry = entry;
           break;
       }
    }

    void* value = NULL;
    if(matching_entry != NULL) {
        emlist_remove(bucket, matching_entry);
        value = matching_entry->value;
        free(matching_entry);
    }
    return value;
}

int emhashmap_size(HashMap* map) {
    int size = 0;
    for(int i = 0; i < map->capacity; i++) {
        size += emlist_size(&map->buckets[i]);
    }
    return size;
}

bool emhashmap_is_empty(HashMap* map) {
    return emhashmap_size(map) == 0;
}
