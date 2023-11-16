#ifndef HASHMAP_H
#define HASHMAP_H

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

HashMap* createHashmap(int size);
void freeHashMap(HashMap* map);
int hashFunction(HashMap* map, char* key);
void insertHashmap(HashMap* map, char* key, void* value, size_t key_size, size_t value_size);
void* getHashmap(HashMap* map, char* key);
void deleteHashmap(HashMap* map, char* key);

void insertWithCustomIndexHashmap(HashMap* map, int index, void* key, void* value, size_t key_size, size_t value_size);
void deleteWithCustomIndexHashmap(HashMap* map,int indexToDelete, void* key);

#endif // HASHMAP_H