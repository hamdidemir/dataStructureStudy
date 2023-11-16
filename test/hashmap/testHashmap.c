#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/testHashmap.h"
#include "include/hashmap.h"

void assertCreateHashmap()
{
    int size = 50;
    HashMap* map = createHashmap(size);
    int passes = 0;
    int failures = 0;

    // Test 1: Check if hashmap is not null.
    if(map == NULL)
    {
        printf("✗ Test 1 FAILED: Hashmap is NULL.\n");
        failures++;
    }
    else
    {
        printf("✓ Test 1 passed. Hashmap is initialized.\n");
        passes++;
    }

    // Test 2: Check if the capacity of the created hashmap matches the expected capacity
    if (map->size != size) 
    {
        printf("✗ Test 2 FAILED: Unexpected hashmap size\n");
        failures++;
    }
    else
    {
        printf("✓ Test 2 passed. Hashmap have the expected size.\n");
        passes++;
    }

    if (failures == 0) 
    {
        printf("# 'createHashmap' function passed %d test(s) successfully.\n", passes);
    } 
    else 
    {
        printf("# 'createHashmap' function failed %d of %d test(s).\n", failures, failures+passes);
    }

    // Clean up
    freeHashMap(map);
}

void assertInsertHashMap()
{
    int size = 50;
    HashMap* map = createHashmap(size);
    int passes = 0;
    int failures = 0;

    // Test 3: Insert integer value with an integer key.
    int intValue = 42;
    char *intKey = "123";

    insertHashmap(map, intKey, &intValue, sizeof(intKey), sizeof(intValue)); 
    int* retrievedIntValue = (int*)map->buckets[hashFunction(map, intKey)]->value;
    if (retrievedIntValue != NULL && *retrievedIntValue == intValue)
    {
        printf("✓ Test 3 passed. Inserted and retrieved an integer value.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 3 FAILED: Failed to insert or retrieve an integer value.\n");
        printf("   Expected: %d\n", intValue);
        printf("   Found: %d\n", (retrievedIntValue != NULL) ? *retrievedIntValue : -1);
        failures++;
    }

    // Test 4: Insert a string value with a string key.
    char* stringValue = "Hello, World!";
    char* stringKey = "greeting";
    insertHashmap(map, stringKey, (void*)stringValue, strlen(stringKey)+1, strlen(stringValue)+1); 
    char* retrievedStringValue = (char*)map->buckets[hashFunction(map, stringKey)]->value;
    if (retrievedStringValue != NULL && strcmp(retrievedStringValue, stringValue) == 0)
    {
        printf("✓ Test 4 passed. Inserted and retrieved a string value.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 4 FAILED: Failed to insert or retrieve a string value.\n");
        printf("   Expected: %s\n", stringValue);
        printf("   Found: %s\n", (retrievedStringValue != NULL) ? retrievedStringValue : "NULL");
        failures++;
    }

    // Test 5: Insert a double value with a string key.
    double doubleValue = 3.141592653589793;
    char* doubleKey = "pi";
    insertHashmap(map, doubleKey, (void*)&doubleValue, sizeof(doubleKey), sizeof(doubleValue)); // Pass the correct key_size and value_size
    double* retrievedDoubleValue = (double*)map->buckets[hashFunction(map, doubleKey)]->value;
    if (retrievedDoubleValue != NULL && *retrievedDoubleValue == doubleValue)
    {
        printf("✓ Test 5 passed. Inserted and retrieved a double value.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 5 FAILED: Failed to insert or retrieve a double value.\n");
        printf("   Expected: %lf\n", doubleValue);
        printf("   Found: %lf\n", (retrievedDoubleValue != NULL) ? *retrievedDoubleValue : -1.0);
        failures++;
    }

    // Test 6: Insert a custom struct as value with an integer key.
    // Define your custom struct and create an instance to insert and retrieve.
    // Define your custom struct
    typedef struct CustomStruct 
    {
        int field1;
        double field2;
        // Add more fields 
    } CustomStruct;

    CustomStruct customValue;
    customValue.field1 = 10;
    customValue.field2 = 3.14;
    char *customKey = "789";
    insertHashmap(map, customKey, (void *)&customValue, strlen(customKey)+1, sizeof(customValue));

    CustomStruct* retrievedCustomValue = (CustomStruct*)map->buckets[hashFunction(map, customKey)]->value;
    if (retrievedCustomValue != NULL &&
        retrievedCustomValue->field1 == customValue.field1 &&
        retrievedCustomValue->field2 == customValue.field2)
    {
        printf("✓ Test 6 passed. Inserted and retrieved a custom struct value.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 6 FAILED: Failed to insert or retrieve a custom struct value.\n");
        printf("   Expected: field1=%d, field2=%lf\n", customValue.field1, customValue.field2);
        if (retrievedCustomValue != NULL) 
        {
            printf("   Found: field1=%d, field2=%lf\n", retrievedCustomValue->field1, retrievedCustomValue->field2);
        } 
        else 
        {
            printf("   Found: NULL\n");
        }
        failures++;
    }

    // Test 7: Insert a float value with a string key.
    float floatValue = 2.71828;
    char* floatKey = "e";
    insertHashmap(map, floatKey, (void*)&floatValue, sizeof(floatKey), sizeof(floatValue)); 
    float* retrievedFloatValue = (float*)map->buckets[hashFunction(map, floatKey)]->value;
    if (retrievedFloatValue != NULL && *retrievedFloatValue == floatValue)
    {
        printf("✓ Test 7 passed. Inserted and retrieved a float value.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 7 FAILED: Failed to insert or retrieve a float value.\n");
        printf("   Expected: %f\n", floatValue);
        printf("   Found: %f\n", (retrievedFloatValue != NULL) ? *retrievedFloatValue : -1.0f);
        failures++;
    }

    // Test 8: insert 3 values into the same bucket and test if they are connected correctly
    HashMap* newmap = createHashmap(size);
    int seriesvalue1 = 21;
    int seriesvalue2 = 22;
    int seriesvalue3 = 23;

    int serieskey1 = 1;
    int serieskey2 = 2;
    int serieskey3 = 3;

    int customindex = 10;
    insertWithCustomIndexHashmap(newmap, customindex, (void*)&serieskey1, (void*)&seriesvalue1, sizeof(serieskey1), sizeof(seriesvalue1)); // Pass the correct key_size and value_size
    insertWithCustomIndexHashmap(newmap, customindex, (void*)&serieskey2, (void*)&seriesvalue2, sizeof(serieskey2), sizeof(seriesvalue2)); // Pass the correct key_size and value_size
    insertWithCustomIndexHashmap(newmap, customindex, (void*)&serieskey3, (void*)&seriesvalue3, sizeof(serieskey3), sizeof(seriesvalue3)); // Pass the correct key_size and value_size

    int* retrievedIntValue1 = (int*)newmap->buckets[customindex]->value;
    int* retrievedIntValue2 = (int*)newmap->buckets[customindex]->next->value;
    int* retrievedIntValue3 = (int*)newmap->buckets[customindex]->next->next->value;
    if (retrievedIntValue1 != NULL && *retrievedIntValue1 == seriesvalue1 && retrievedIntValue2 != NULL && *retrievedIntValue2 == seriesvalue2 && retrievedIntValue3 != NULL && *retrievedIntValue3 == seriesvalue3)
    {
        printf("✓ Test 8 passed. Inserted and retrieved three integer values to the same bucket in the correct order.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 8 FAILED: Failed to insert three integer values to the same bucket in the correct order.\n");
        printf("   Expected: %d, %d, %d\n", seriesvalue1, seriesvalue2, seriesvalue3);
        printf("   Found: %d, %d, %d\n", (retrievedIntValue1 != NULL) ? *retrievedIntValue1 : -1, (retrievedIntValue2 != NULL) ? *retrievedIntValue2 : -1, (retrievedIntValue3 != NULL) ? *retrievedIntValue3 : -1);
        failures++;
    }

    if (failures == 0)
    {
        printf("# 'insertHashMap' function passed %d test(s) successfully.\n", passes);
    }
    else
    {
        printf("# 'insertHashMap' function failed %d of %d test(s).\n", failures, failures + passes);
    }

    // Clean up
    freeHashMap(map);
    freeHashMap(newmap);
}



void assertGetHashMap()
{
    int size = 50;
    HashMap* map = createHashmap(size);
    int passes = 0;
    int failures = 0;

    // Test 9: Insert integer value and retrieve it.
    int intValue = 42;
    char *intKey = "123";
    insertHashmap(map, intKey, (void *)&intValue, sizeof(intKey), sizeof(intValue));
    int* retrievedIntValue = (int*)getHashmap(map, intKey);
    if (retrievedIntValue != NULL && *retrievedIntValue == intValue)
    {
        printf("✓ Test 9 passed. Inserted and retrieved an integer value.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 9 FAILED: Failed to retrieve an integer value.\n");
        printf("   Expected: %d\n", intValue);
        printf("   Found: %d\n", (retrievedIntValue != NULL) ? *retrievedIntValue : -1);
        failures++;
    }

    // Test 10: Insert a string value with a string key and retrieve it.
    char* stringValue = "Hello, World!";
    char* stringKey = "greeting";
    insertHashmap(map, stringKey, (void*)stringValue, strlen(stringKey)+1, strlen(stringValue)+1);
    char* retrievedStringValue = (char*)getHashmap(map, stringKey);
    if (retrievedStringValue != NULL && strcmp(retrievedStringValue, stringValue) == 0)
    {
        printf("✓ Test 10 passed. Inserted and retrieved a string value.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 10 FAILED: Failed to retrieve a string value.\n");
        printf("   Expected: %s\n", stringValue);
        printf("   Found: %s\n", (retrievedStringValue != NULL) ? retrievedStringValue : "NULL");
        failures++;
    }

    // Test 11: Retrieve a value that doesn't exist in the hashmap.
    const char* nonExistentKey = "nonexistent";
    void* nonExistentValue = getHashmap(map, (void *)nonExistentKey);
    if (nonExistentValue == NULL)
    {
        printf("✓ Test 11 passed. Retrieved NULL for a non-existent key.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 11 FAILED: Retrieved a value for a non-existent key.\n");
        printf("   Expected: NULL\n");
        printf("   Found: %p\n", nonExistentValue);
        failures++;
    }

    if (failures == 0)
    {
        printf("# 'getHashMap' function passed %d test(s) successfully.\n", passes);
    }
    else
    {
        printf("# 'getHashMap' function failed %d of %d test(s).\n", failures, failures + passes);
    }

    // Clean up
    freeHashMap(map);
}


void assertDeleteHashMap()
{
    int size = 50;
    HashMap* map = createHashmap(size);
    int passes = 0;
    int failures = 0;

    // Test 12: Insert integer value with an integer key, delete it, and check if it's deleted.
    int intValue = 42;
    char *intKey = "123";
    
    insertHashmap(map, intKey, (void *)&intValue, sizeof(intKey), sizeof(intValue));
    deleteHashmap(map, intKey);
    int* deletedIntValue = (int*)getHashmap(map, intKey);
    if (deletedIntValue == NULL)
    {
        printf("✓ Test 12 passed. Inserted and deleted an integer value.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 12 FAILED: Failed to delete an integer value.\n");
        printf("   Found: %p\n", deletedIntValue);
        failures++;
    }

    // Test 13: Insert a string value with a string key, delete it, and check if it's deleted.
    const char* stringValue = "Hello, World!";
    const char* stringKey = "greeting";
    insertHashmap(map, (char*)stringKey, (void*)stringValue, sizeof(stringKey), sizeof(stringValue));
    deleteHashmap(map, (char*)stringKey);
    const char* deletedStringValue = (const char*)getHashmap(map, (char*)stringKey);
    if (deletedStringValue == NULL)
    {
        printf("✓ Test 13 passed. Inserted and deleted a string value.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 13 FAILED: Failed to delete a string value.\n");
        printf("   Found: %p\n", deletedStringValue);
        failures++;
    }

    // Test 14: Try to delete a key that does not exist in the hashmap.
    const char* nonExistentKey = "nonexistent";
    deleteHashmap(map, (void *)nonExistentKey);
    // Check if the non-existent key does not crash the program.
    printf("✓ Test 14 passed. Attempted to delete a non-existent key.\n");
    passes++;
    // In case of failure, the program should crash.


    // Test 15: insert 3 values to same bucket and delete the middle one to test if the connection between first and third is established correctly.
    HashMap* newmap = createHashmap(size);
    int intValue1 = 42;
    int intValue2 = 55;
    int intValue3 = 67;
    int intKey1 = 123;
    int intKey2 = 124;
    int intKey3 = 125;
    
    // Set the custom hash (index) values to ensure they are in the same bucket (index < 50).
    int customHash = 10;

    // Insert three values into the same bucket with custom hash values.
    insertWithCustomIndexHashmap(newmap, customHash, &intKey1, &intValue1, sizeof(intKey1), sizeof(intValue1));
    insertWithCustomIndexHashmap(newmap, customHash, &intKey2, &intValue2, sizeof(intKey1), sizeof(intValue1));
    insertWithCustomIndexHashmap(newmap, customHash, &intKey3, &intValue3, sizeof(intKey1), sizeof(intValue1));

    // Delete the middle one.
    deleteWithCustomIndexHashmap(newmap, customHash, &intKey2);

    // Check if the first one is connected to the third one.
    HashNode* bucket = newmap->buckets[customHash];  // Use the correct custom hash value.
    if (bucket != NULL && bucket->next != NULL)
    {               
        int* value1 = (int*)bucket->value;
        int* value3 = (int*)bucket->next->value;

        if (value1 != NULL && value3 != NULL && *value1 == intValue1 && *value3 == intValue3)
        {
            printf("✓ Test 15 passed. Deleted the middle value, and the first value is connected to the third one.\n");
            passes++;
        }
        else
        {
            printf("✗ Test 15 FAILED: Incorrect connection after deleting the middle value.\n");
            printf("   Expected: %d, %d\n", intValue1, intValue3);
            printf("   Found: %d, %d\n", (value1 != NULL) ? *value1 : -1, (value3 != NULL) ? *value3 : -1);
            failures++;
        }
    }
    else
    {
        printf("✗ Test 15 FAILED: Bucket is empty or missing the next node after deletion.\n");
        failures++;
    }


    if (failures == 0)
    {
        printf("# 'deleteHashMap' function passed %d test(s) successfully.\n", passes);
    }
    else
    {
        printf("# 'deleteHashMap' function failed %d of %d test(s).\n", failures, failures + passes);
    }

    // Clean up
    freeHashMap(map);
}


void assertFreeHashMap()
{
    int size = 50;
    HashMap* map = createHashmap(size);
    int passes = 0;
    int failures = 0;

    int intValue1 = 42;
    int intValue2 = 55;
    char* intKey1 = "123";
    char* intKey2 = "124";
    insertHashmap(map, intKey1, &intValue1, strlen(intKey1)+1, sizeof(int));
    insertHashmap(map, intKey2, &intValue2, strlen(intKey2)+1, sizeof(int));
    // Test 15: Free the hashmap and check if it's successfully freed.
    freeHashMap(map);
    // Attempt to access the map after freeing it.
    // This should result in a segmentation fault if it's not freed correctly.
    int* accessedValue1 = (int *)getHashmap(map, intKey1);
    int* accessedValue2 = (int *)getHashmap(map, intKey2);
    if (accessedValue1 == NULL && accessedValue2 == NULL)
    {
        printf("✓ Test 15 passed. HashMap freed successfully.\n");
        passes++;
    }
    else
    {
        printf("✗ Test 15 FAILED: HashMap not freed correctly.\n");
        printf("   Expected: NULL\n");
        printf("   Found: %d, %d\n", *accessedValue1, *accessedValue2);
        failures++;
    }

    if (failures == 0)
    {
        printf("# 'freeHashMap' function passed %d test(s) successfully.\n", passes);
    }
    else
    {
        printf("# 'freeHashMap' function failed %d of %d test(s).\n", failures, failures + passes);
    }
}


