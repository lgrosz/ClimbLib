#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashNode {
	void *key;
	void *value;
	struct HashNode *next;
} HashNode;

typedef struct HashTable {
	size_t size;
	HashNode **buckets;
} HashTable;

static unsigned long hash(void *key) {
	return (unsigned long)key >> 3;
}

HashTable* HashTable_create(size_t size) {
	HashTable *table = malloc(sizeof(HashTable));

	table->size = size;
	table->buckets = calloc(table->size, sizeof(HashNode *));

	return table;
}

void HashTable_insert(HashTable *table, void *key, void *value) {
	unsigned long index = hash(key) % table->size;
	HashNode *new_node = malloc(sizeof(HashNode));

	new_node->key = key;
	new_node->value = value;
	new_node->next = table->buckets[index];

	table->buckets[index] = new_node;
}

void *HashTable_search(HashTable *table, const void *key) {
	unsigned long index = hash((void*)key) % table->size;
	HashNode *node = table->buckets[index];

	while (node) {
		if (node->key == key) {
			return node->value;
		}
		node = node->next;
	}

	return NULL;
}

void *HashTable_remove(HashTable *table, void *key) {
	unsigned long index = hash(key) % table->size;
	HashNode *node = table->buckets[index];
	HashNode *prev = NULL;
	while (node) {
		if (node->key == key) {
			if (prev) {
				prev->next = node->next;
			} else {
				table->buckets[index] = node->next;
			}

			void *value = node->value;
			free(node);
			return value;
		}

		prev = node;
		node = node->next;
	}

	return NULL;
}

void HashTable_free(HashTable *table) {
	for (size_t i = 0; i < table->size; i++) {
		HashNode *node = table->buckets[i];
		while (node) {
			HashNode *tmp = node;
			node = node->next;
			free(tmp);
		}
	}

	free(table->buckets);
	free(table);
}

void **HashTable_keys(HashTable *table, size_t *count) {
    size_t capacity = 10;
    void **keys = malloc(capacity * sizeof(void *));
    *count = 0;

    for (size_t i = 0; i < table->size; i++) {
        HashNode *node = table->buckets[i];

        while (node) {
            if (*count >= capacity) {
                capacity *= 2;
                keys = realloc(keys, capacity * sizeof(void *));
            }

            keys[*count] = node->key;
            (*count)++;
            node = node->next;
        }
    }

    return keys;
}
