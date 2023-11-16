// dynamicArray_test
#include "include/testDynamicArray.h"

void test_create_dynamicArray() 
{
    size_t initialCapacity = 5;
    dynamicArray* arr = create_dynamicArray(initialCapacity);

    TEST_ASSERT_NOT_NULL(arr);
    TEST_ASSERT_NOT_NULL(arr->data);
    TEST_ASSERT_EQUAL(initialCapacity, arr->capacity);
    TEST_ASSERT_EQUAL(0, arr->length);

    free_dynamicArray(arr);
}

void test_add_dynamicArray() 
{
    dynamicArray* arr = create_dynamicArray(5);

    int data = 42;
    add_dynamicArray(arr, &data);

    TEST_ASSERT_EQUAL(1, arr->length);
    TEST_ASSERT_EQUAL(&data, arr->data[0]);

    free_dynamicArray(arr);
}

void test_deleteAtIndex_dynamicArray() 
{
    dynamicArray* arr = create_dynamicArray(5);

    int data1 = 1, data2 = 2, data3 = 3;
    add_dynamicArray(arr, &data1);
    add_dynamicArray(arr, &data2);
    add_dynamicArray(arr, &data3);

    deleteAtIndex_dynamicArray(arr, 1); // Delete at index 1

    TEST_ASSERT_EQUAL(2, arr->length);
    TEST_ASSERT_EQUAL(&data1, arr->data[0]);
    TEST_ASSERT_EQUAL(&data3, arr->data[1]);

    free_dynamicArray(arr);
}

void test_insertAtIndex_dynamicArray() 
{
    dynamicArray* arr = create_dynamicArray(5);

    int data1 = 1, data3 = 3;
    add_dynamicArray(arr, &data1);
    add_dynamicArray(arr, &data3);

    int newData = 2;
    insertAtIndex_dynamicArray(arr, 1, &newData); // Insert at index 1

    TEST_ASSERT_EQUAL(3, arr->length);
    TEST_ASSERT_EQUAL(&data1, arr->data[0]);
    TEST_ASSERT_EQUAL(&newData, arr->data[1]);
    TEST_ASSERT_EQUAL(&data3, arr->data[2]);

    free_dynamicArray(arr);
}

void test_get_dynamicArray() 
{
    dynamicArray* arr = create_dynamicArray(5);

    int data = 42;
    add_dynamicArray(arr, &data);

    void* retrievedData = get_dynamicArray(arr, 0);

    TEST_ASSERT_EQUAL(&data, retrievedData);

    free_dynamicArray(arr);
}


void test_capacityIncrease_dynamicArray() 
{
    dynamicArray* arr = create_dynamicArray(2); // Initial capacity set to 2

    int dataArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Add elements until the capacity is increased
    for (int i = 0; i < 10; i++) 
    {
        add_dynamicArray(arr, &dataArray[i]);
    }

    print_dynamicArray(arr);

    TEST_ASSERT_EQUAL(10, arr->length);
        
    // Check if the capacity is increased 
    TEST_ASSERT_LESS_OR_EQUAL(arr->capacity, 10);

    free_dynamicArray(arr);
}
