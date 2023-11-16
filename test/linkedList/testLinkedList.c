#include "include/unity.h"
#include "include/linkedlist.h"

// Set up function that will be called before each test
void setUp(void) 
{
    // Initialization code, if needed
}

// Tear down function that will be called after each test
void tearDown(void) 
{
    // Clean-up code, if needed
}


// Test create_LinkedList function
void test_create_LinkedList() 
{
    linkedList* list = create_LinkedList();
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_EQUAL_UINT(0, list->size);
    free_LinkedList(list);
}

// Test add_linkedList function
void test_add_linkedList() 
{
    linkedList* list = create_LinkedList();

    int element1 = 42;
    int element2 = 55;

    add_linkedList(list, &element1);
    TEST_ASSERT_NOT_NULL(list->head);
    TEST_ASSERT_EQUAL_PTR(&element1, list->head->value);
    TEST_ASSERT_EQUAL_UINT(1, list->size);

    add_linkedList(list, &element2);
    TEST_ASSERT_EQUAL_PTR(&element2, list->head->next->value);
    TEST_ASSERT_EQUAL_UINT(2, list->size);

    free_LinkedList(list);
}

// Test deleteHead_LinkedList function
void test_deleteHead_LinkedList() 
{
    linkedList* list = create_LinkedList();

    int element1 = 42;
    int element2 = 55;

    add_linkedList(list, &element1);
    add_linkedList(list, &element2);

    deleteHead_LinkedList(list);
    TEST_ASSERT_EQUAL_PTR(&element2, list->head->value);
    TEST_ASSERT_EQUAL_UINT(1, list->size);

    deleteHead_LinkedList(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_EQUAL_UINT(0, list->size);

    free_LinkedList(list);
}

// Test deleteFirstOccurrence_LinkedList function
void test_deleteFirstOccurrence_LinkedList() 
{
    linkedList* list = create_LinkedList();

    int element1 = 42;
    int element2 = 55;
    int element3 = 78;

    add_linkedList(list, &element1);
    add_linkedList(list, &element2);
    add_linkedList(list, &element3);

    // Delete the first occurrence of value 55
    deleteFirstOccurrence_LinkedList(list, &element2);
    TEST_ASSERT_EQUAL_PTR(&element1, list->head->value);
    TEST_ASSERT_EQUAL_PTR(&element3, list->head->next->value);
    TEST_ASSERT_EQUAL_UINT(2, list->size);

    free_LinkedList(list);
}


// Test correctness of size
void test_findSize_LinkedList() 
{
    linkedList* list = create_LinkedList();

    int elements[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    // Calculate the number of elements in the array
    int arrayLength = sizeof(elements) / sizeof(elements[0]);

    // Insert 10 values
    for (int i = 0; i < arrayLength; i++) 
    {
        add_linkedList(list, &elements[i]);
    }

    TEST_ASSERT_EQUAL_UINT(arrayLength, list->size);

    // print_LinkedList(list);

    // Delete 2 values
    deleteFirstOccurrence_LinkedList(list, &elements[3]); // Deleting value 40
    deleteFirstOccurrence_LinkedList(list, &elements[7]); // Deleting value 80
    deleteHead_LinkedList(list); // Deleting the first element

    size_t calculatedSize = 0;
    linkedListNode* current = list->head;

    while (current != NULL) 
    {
        calculatedSize++;
        current = current->next;
    }

    // Verify the size after deleting 2 values
    TEST_ASSERT_EQUAL_UINT(calculatedSize, list->size);

    // print_LinkedList(list);

    free_LinkedList(list);
}
