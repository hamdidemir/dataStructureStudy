#include "include/dynamicArray.h"

/*
// Structure definition for the dynamic array
typedef struct dynamicArray
{
    void** data;       // Array of void pointers
    size_t length;     // Current length of the array
    size_t capacity;   // Capacity of the array
} dynamicArray;
*/


// Function to create a dynamic array with the specified initial capacity
dynamicArray* create_dynamicArray(size_t initialCapacity)
{
    dynamicArray* arr = (dynamicArray *)malloc(sizeof(dynamicArray));
    arr->length = 0;   // Initialize length to 0
    arr->capacity = initialCapacity;
    arr->data = (void **)malloc(initialCapacity * sizeof(void *));

    return arr;
}

// Function to add an element to the dynamic array
void add_dynamicArray(dynamicArray* arr, void* data)
{
    // Check if the array needs to be resized
    if (arr->length >= arr->capacity)
    {
        // Double the capacity
        arr->capacity *= 2; 
        // Reallocate memory for the array with the updated capacity
        arr->data = (void **)realloc(arr->data, arr->capacity * sizeof(void *));
    }

    // Add the new element to the array
    arr->data[arr->length] = data;
    // Increment the length of the array
    arr->length++;
}

void deleteAtIndex_dynamicArray(dynamicArray* arr, size_t index)
{
    // Check if the index is valid
    if (index >= arr->length) 
    {
        printf("Error: Index out of bounds.\n");
        return;
    }

    // Shift elements to fill the gap created by removing the element at the specified index
    for (size_t i = index; i < arr->length - 1; i++) 
    {
        arr->data[i] = arr->data[i + 1];
    }

    // Decrement the length of the array
    arr->length--;

    // Check if the array should be resized to reduce capacity
    if (arr->length <= arr->capacity / 2) 
    {
        // Reduce the capacity (you can adjust the condition as needed)
        arr->capacity /= 2;
        // Reallocate memory for the array with the updated capacity
        arr->data = (void **)realloc(arr->data, arr->capacity * sizeof(void *));
    }
}

void insertAtIndex_dynamicArray(dynamicArray* arr, size_t index, void* data)
{
    // Check if the index is valid
    if (index > arr->length) 
    {
        printf("Error: Index out of bounds.\n");
        return;
    }

    // Check if the array needs to be resized
    if (arr->length >= arr->capacity)
    {
        // Double the capacity
        arr->capacity *= 2;
        // Reallocate memory for the array with the updated capacity
        arr->data = (void **)realloc(arr->data, arr->capacity * sizeof(void *));
    }

    // Shift elements to make room for the new element
    for (size_t i = arr->length; i > index; i--) 
    {
        arr->data[i] = arr->data[i - 1];
    }

    // Insert the new element at the specified index
    arr->data[index] = data;

    // Increment the length of the array
    arr->length++;
}

void* get_dynamicArray(dynamicArray* arr, size_t index)
{
    // Check if the index is valid
    if (index >= arr->length) 
    {
        printf("Error: Index out of bounds.\n");
        return NULL; 
    }

    // Return the data at the specified index
    return arr->data[index];
}

void print_dynamicArray(dynamicArray* arr)
{
    if (arr == NULL) 
    {
        printf("Error: Null dynamicArray.\n");
        return;
    }

    printf("Dynamic Array (Length: %zu, Capacity: %zu): [", arr->length, arr->capacity);

    for (size_t i = 0; i < arr->length; i++) 
    {
        printf("%d", *(int *)arr->data[i]);

        if (i < arr->length - 1) 
        {
            printf(", ");
        }
    }

    printf("]\n");
}


void free_dynamicArray(dynamicArray* arr)
{
    free(arr->data);
    free(arr);
}