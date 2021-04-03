#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key))
{
    size_t i;
    hashmap_t* hashmap = malloc(sizeof(hashmap_t));
    hashmap->length = length;
    hashmap->plist = malloc(sizeof(node_t*) * length);
    hashmap->hash_func = p_hash_func;

    for (i = 0; i < length; i++) {
        hashmap->plist[i] = NULL;
    }

    return hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    size_t hash_id;
    size_t start_index;
    size_t key_length;
    node_t* tmp_node;
    node_t* curr_node;
    node_t* prior_node;
    char* tmp_key;
    
    
    hash_id = hashmap->hash_func(key);
    start_index = hash_id % hashmap->length;
    curr_node = hashmap->plist[start_index];
    key_length = strlen(key);

    if (curr_node == NULL) {
        tmp_node = malloc(sizeof(node_t));
        tmp_node->value = value;
        tmp_key = malloc(key_length + 1);
        strcpy(tmp_key, key);
        tmp_key[key_length] = '\0';
        tmp_node->key = tmp_key;
        tmp_node->next = NULL;
        hashmap->plist[start_index] = tmp_node;
        return TRUE;
    }
    
    while (curr_node != NULL) {
        if (strcmp(curr_node->key, key) == 0) {
            return FALSE;
        }
        prior_node = curr_node;
        curr_node = curr_node->next;
    }
    tmp_node = malloc(sizeof(node_t));
    tmp_node->value = value;
    tmp_key = malloc(key_length);
    strcpy(tmp_key, key);
    tmp_key[key_length] = '\0';
    tmp_node->key = tmp_key;
    tmp_node->next = NULL;
    prior_node->next = tmp_node;

    return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    size_t start_index;
    size_t hash_id;
    node_t* curr_node;

    hash_id = hashmap->hash_func(key);
    start_index = hash_id % hashmap->length;
    curr_node = hashmap->plist[start_index];

    if (curr_node == NULL) {
        return -1;
    } else {
        while (curr_node != NULL) {
            if (strcmp(curr_node->key, key) == 0) {
                return curr_node->value;
            }
            curr_node = curr_node->next;
        }
    }
    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    size_t start_index;
    size_t hash_id;
    node_t* curr_node;

    hash_id = hashmap->hash_func(key);
    start_index = hash_id % hashmap->length;
    curr_node = hashmap->plist[start_index];

    while (curr_node != NULL) {
        if (strcmp(curr_node->key, key) == 0) {
            curr_node->value = value;
            return TRUE;
        }
        curr_node = curr_node->next;
    }

    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    size_t start_index;
    size_t hash_id;
    node_t* curr_node;
    node_t* prior_node;

    hash_id = hashmap->hash_func(key);
    start_index = hash_id % hashmap->length;
    curr_node = hashmap->plist[start_index];

    if (curr_node == NULL) {
        return FALSE;
    }

    if (strcmp(curr_node->key, key) == 0) {
        hashmap->plist[start_index] = curr_node->next;
        free(curr_node->key);
        free(curr_node);
        return TRUE;
    }

    while (curr_node != NULL) {
        if (strcmp(curr_node->key, key) == 0) {
            prior_node->next = curr_node->next;
            free(curr_node->key);
            free(curr_node);
            return TRUE;
        }
        prior_node = curr_node;
        curr_node = curr_node->next;
    }
    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    size_t i;
    size_t length = hashmap->length;
    node_t* curr_node;
    node_t* tmp_node;

    if (hashmap == NULL) {
        return;
    }

    if (hashmap->plist == NULL) {
        return;
    }

    for (i = 0; i < length; i++) {
        curr_node = hashmap->plist[i];
        while (curr_node != NULL) {
            tmp_node = curr_node;
            curr_node = curr_node->next;
            free(tmp_node->key);
            tmp_node->key = NULL;
            free(tmp_node);
            tmp_node = NULL;
        }
    }
    free(hashmap->plist);
    hashmap->plist = NULL;
    free(hashmap);
    hashmap = NULL;
}
