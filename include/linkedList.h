#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

// Struct definition for a linked list node
typedef struct linkedListNode {
    void* value;
    struct linkedListNode* next;
} linkedListNode;

// Struct definition for a linked list
typedef struct linkedList {
    linkedListNode* head;
    size_t size;
} linkedList;

// Function declarations

// Function to create an empty linked list
linkedList* create_LinkedList();

// Function to add a new node to the end of the linked list
void add_linkedList(linkedList* list, void* value);

// Function to delete the head of the linked list
void deleteHead_LinkedList(linkedList* list);

// Function to delete the first occurrence of a value from the linked list
void deleteFirstOccurrence_LinkedList(linkedList* list, void* value);

// Function to print the linked list
void print_LinkedList(linkedList* list);

// Function to free the memory used by the linked list
void free_LinkedList(linkedList* list);

#endif // LINKEDLIST_H
