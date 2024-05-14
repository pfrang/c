/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <limits.h>
#include <stdlib.h>
typedef struct {
    int key;
    int val;
} HashItem;

typedef struct {
    HashItem *items;
    int size;
} HashTable;

unsigned int hashFunction(int key, int size) {
    unsigned int hash = (key < 0 ? -key : key) % size;
    return hash;
}

HashTable *createHashTable(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->size = size;
    table->items = calloc(table->size, sizeof(HashItem));
    for (int i = 0; i < size; i++) {
        table->items[i].key = INT_MIN; // Using INT_MIN to signify empty slots
    }
    return table;
}

void freeHashTable(HashTable *table) {
    free(table->items);
    free(table);
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    int *result = malloc(2 * sizeof(int));
    *returnSize = 2;

    HashTable *hashTable =
        createHashTable(numsSize * 2); // Create a hash table double the size of numsSize to reduce collisions

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int complement = target - num;
        unsigned int hashIndex = hashFunction(complement, hashTable->size);

        // Check if the complement exists in the hash table
        while (hashTable->items[hashIndex].key != INT_MIN) {
            if (hashTable->items[hashIndex].key == complement) {
                result[0] = hashTable->items[hashIndex].val;
                result[1] = i;
                freeHashTable(hashTable);
                return result;
            }
            hashIndex = (hashIndex + 1) % hashTable->size; // Linear probing
        }

        // Insert the current number in the hash table
        hashIndex = hashFunction(num, hashTable->size);
        while (hashTable->items[hashIndex].key != INT_MIN) {
            hashIndex = (hashIndex + 1) % hashTable->size; // Handle collisions with linear probing
        }
        hashTable->items[hashIndex].key = num;
        hashTable->items[hashIndex].val = i;
    }

    freeHashTable(hashTable);
    return result;
}
