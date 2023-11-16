#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

// Structure definition for the dynamic array
typedef struct dynamicArray
{
    void** data;       // Array of void pointers
    size_t length;     // Current length of the array
    size_t capacity;   // Capacity of the array
} dynamicArray;

// Function declarations
dynamicArray* create_dynamicArray(size_t initialCapacity);
void add_dynamicArray(dynamicArray* arr, void* data);
void deleteAtIndex_dynamicArray(dynamicArray* arr, size_t index);
void insertAtIndex_dynamicArray(dynamicArray* arr, size_t index, void* data);
void* get_dynamicArray(dynamicArray* arr, size_t index);
void print_dynamicArray(dynamicArray* arr);
void free_dynamicArray(dynamicArray* arr);

#endif /* DYNAMIC_ARRAY_H */
