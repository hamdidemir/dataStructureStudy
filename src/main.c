#include <stdio.h>
#include <stdlib.h>
#include "include/unity.h"
#include "include/testHashmap.h"
#include "include/testBPlusTree.h"
#include "include/testLinkedList.h"
#include "include/testDynamicArray.h"

int main()
{
    UNITY_BEGIN();
    int choice = 0;

    while (choice != 5) 
    {
        printf("Menu:\n");
        printf("1. Test your dynamic array structure\n");
        printf("2. Test your hashmap structure\n");
        printf("3. Test your b+ tree structure\n");
        printf("4. Test your linked list structure\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) 
        {
            case 1:   
                RUN_TEST(test_create_dynamicArray);
                RUN_TEST(test_add_dynamicArray);
                RUN_TEST(test_deleteAtIndex_dynamicArray);
                RUN_TEST(test_insertAtIndex_dynamicArray);
                RUN_TEST(test_get_dynamicArray);
                RUN_TEST(test_capacityIncrease_dynamicArray);
                break;           
            case 2:           
                printf("----------------------------------------------------------------------\n");
                printf("# TESTING createHashmap function:\n");
                assertCreateHashmap();         
                printf("----------------------------------------------------------------------\n");
                printf("# TESTING insertHashmap function:\n"); 
                assertInsertHashMap();
                printf("----------------------------------------------------------------------\n");
                printf("# TESTING getHashmap function:\n"); 
                assertGetHashMap();
                printf("----------------------------------------------------------------------\n");
                printf("# TESTING deleteHashmap function:\n"); 
                assertDeleteHashMap();
                printf("----------------------------------------------------------------------\n");
                printf("# TESTING freeHashmap function:\n"); 
                assertFreeHashMap();
                printf("----------------------------------------------------------------------\n");
                break;
            case 3:
                printf("----------------------------------------------------------------------\n");
                printf("# TESTING createBPlusTree and createNode functions:\n");
                assertCreateBPlusTree();    
                printf("----------------------------------------------------------------------\n");
                printf("# TESTING insert functionality of B+ Tree:\n");
                assertInsert();
                printf("----------------------------------------------------------------------\n");
                printf("# TESTING finding record functionality of B+ Tree:\n");
                assertFindRecord();
                printf("----------------------------------------------------------------------\n");
                printf("# TESTING delete functionlity of B+ Tree:\n");
                assertDelete();
                printf("----------------------------------------------------------------------\n");
                break;
            case 4:
                RUN_TEST(test_create_LinkedList);
                RUN_TEST(test_add_linkedList);
                RUN_TEST(test_deleteHead_LinkedList);
                RUN_TEST(test_deleteFirstOccurrence_LinkedList);
                RUN_TEST(test_findSize_LinkedList);
                break;
            case 5:
                break;
            case 9:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n"); 
                break;
        }
    }

    return UNITY_END();
}
