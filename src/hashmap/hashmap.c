#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashNode
{
    char* key;
    void* value;
    struct HashNode* next;
} HashNode;

typedef struct HashMap
{
    int size;
    HashNode** buckets;
} HashMap;


HashMap* createHashmap(int size)
{
    HashMap* map = (HashMap*) malloc(sizeof(HashMap));
    map->size = size;
    map->buckets = (HashNode**) malloc(sizeof(HashNode *) * size);

    for(int i=0 ;i < size; i++)
    {
        map->buckets[i] = NULL;
    }

    return map;
}


int hashFunction(HashMap* map, char* key)
{
    int index = 0;
    
    // Calculate the sum of ASCII values of characters in the key
    for (int i = 0; key[i] != '\0'; i++)
    {
        index += (int)key[i];
    }
    
    return index % map->size;
}


void insertHashmap(HashMap* map, char* key, void* value, size_t key_size, size_t value_size)
{
    // Step 1: Calculate the hash value for the key.
    int index = hashFunction(map, key);

    // Step 2: Create a new HashNode.
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode) 
    {
        printf("Memory allocation for HashNode failed when inserting\n");
        return;
    }

    newNode->key = malloc(key_size);      // Allocate memory based on the size of the data pointed to by key
    newNode->value = malloc(value_size);  // Allocate memory based on the size of the data pointed to by value

    if (!newNode->key || !newNode->value) 
    {
        printf("Memory allocations for key-value pair failed when inserting\n");
        free(newNode->key); // Free allocated memory before exiting
        free(newNode->value);
        free(newNode);
        return;
    }

    memcpy(newNode->key, key, key_size);
    memcpy(newNode->value, value, value_size);
    newNode->next = NULL;

    // Step 3: Insert the new HashNode into the appropriate bucket.
    if (map->buckets[index] == NULL)
    {
        // The bucket is empty, so create a new linked list.
        map->buckets[index] = newNode;
    }
    else
    {
        // There's already a linked list in this bucket.
        // Traverse the linked list to find the last node.
        HashNode* current = map->buckets[index];
        while (current->next != NULL)
        {
            current = current->next;
        }

        // Add the new HashNode at the end of the list.
        current->next = newNode;
    }
}

// Insert values to hashmap with custom hash(index) values insead of generating it with hashfunction for testing purposes.
void insertWithCustomIndexHashmap(HashMap* map, int index, void* key, void* value, size_t key_size, size_t value_size)
{
    index = index % map->size;

    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode) 
    {
        printf("Memory allocation for HashNode failed when inserting\n");
        return;
    }

    newNode->key = malloc(sizeof(key_size));      // Allocate memory based on the size of the data pointed to by key
    newNode->value = malloc(sizeof(value_size));  // Allocate memory based on the size of the data pointed to by value

    if (!newNode->key || !newNode->value) 
    {
        printf("Memory allocations for key-value pair failed when inserting\n");
        free(newNode->key); // Free allocated memory before exiting
        free(newNode->value);
        free(newNode);
        return;
    }

    memcpy(newNode->key, key, sizeof(key_size));
    memcpy(newNode->value, value, sizeof(value_size));
    newNode->next = NULL;

    // Insert the new HashNode into the appropriate bucket.
    if(map->buckets[index] == NULL)
    {
        // The bucket is empty, so create a new linked list.
        map->buckets[index] = newNode;
    }
    else
    {
        // There's already a linked list in this bucket.
        // Traverse the linked list to find the last node.
        HashNode* current = map->buckets[index];
        while (current->next != NULL)
        {
            current = current->next;
        }

        // Add the new HashNode at the end of the list.
        current->next = newNode;
    }
}



void* getHashmap(HashMap* map, char* key)
{
    // Step 1: Calculate the hash value for the key.
    int hash = hashFunction(map, key);

    if(map != NULL)
    {
        // Step 2: Traverse the linked list in the appropriate bucket.
        if(map->buckets != NULL)
        {
            HashNode* current = map->buckets[hash];

            while (current != NULL)
            {
                // Step 3: Compare keys.
                if (strcmp(current->key, key) == 0)
                {
                    // Found the key, return the associated value.
                    return current->value;
                }
                current = current->next;
            }
        }
        else
        {
            printf("The hashnodes in hashmap does not exist\n");
            return NULL;
        }
    }
    else
    {
        printf("The hashmap does not exist\n");
        return NULL;
    }
    // Key not found in the hashmap.
    printf("Key %s not found in the hashmap.\n", key);
    return NULL;
}



void deleteHashmap(HashMap* map, char* key)
{
    int indexToDelete = hashFunction(map, key);

    HashNode* current = map->buckets[indexToDelete];
    HashNode* prev = NULL;

    while (current != NULL)
    {
        if (strcmp((const char*)current->key, (const char*)key) == 0)
        {
            // Found the key, remove the associated key-value pair.

            if (prev == NULL)
            {
                // Key is at the beginning of the list.
                map->buckets[indexToDelete] = current->next;
            }
            else
            {
                // Key is in the middle or end of the list.
                prev->next = current->next;
            }

            // Free the memory for the key and the HashNode.
            free(current);
            return; // Key removed, exit the function.
        }

        prev = current;
        current = current->next;
    }
}

// Delete values to hashmap with custom hash(index) values insead of generating it with hashfunction for testing purposes.
void deleteWithCustomIndexHashmap(HashMap* map, int indexToDelete, char* key)
{
    HashNode* current = map->buckets[indexToDelete];
    HashNode* prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            // Found the key, remove the associated key-value pair.

            if (prev == NULL)
            {
                // Key is at the beginning of the list.
                map->buckets[indexToDelete] = current->next;
            }
            else
            {
                // Key is in the middle or end of the list.
                prev->next = current->next;
            }

            // Free the memory for the key and the HashNode.
            free(current);
            return; // Key removed, exit the function.
        }

        prev = current;
        current = current->next;
    }
}


void freeHashMap(HashMap* map)
{
    for(int i = 0; i < map->size; i++)
    {
        HashNode* current = map->buckets[i];
        while(current != NULL)
        {
            HashNode* temp = current;
            current = (HashNode *)current->next;            
            free(temp->key);
            temp->key = NULL;
            free(temp->value);
            temp->value = NULL;
            free(temp);        
            temp = NULL;
        }
    }
    free(map->buckets);
    map->buckets = NULL;
    free(map);
    map = NULL;
}

