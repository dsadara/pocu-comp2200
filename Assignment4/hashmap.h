#ifndef HASHMAP_H
#define HASHMAP_H

#define TRUE (1)
#define FALSE (0)

#include <string.h>
#include <stdlib.h>
#include "node.h"

typedef struct hashmap {
    size_t (*hash_func)(const char* key);
    node_t** plist;
    size_t length;
} hashmap_t;

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key));

int add_key(hashmap_t* hashmap, const char* key, const int value);

int get_value(const hashmap_t* hashmap, const char* key);

int update_value(hashmap_t* hashmap, const char* key, int value);

int remove_key(hashmap_t* hashmap, const char* key);

void destroy(hashmap_t* hashmap);

#endif /* HASHMAP_H */
