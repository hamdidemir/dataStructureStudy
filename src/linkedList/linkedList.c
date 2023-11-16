#include "include/linkedList.h"

// This code defines a simple implementation of a singly linked list in C.
// The linked list consists of nodes, each containing a value and a pointer to the next node.
// The linked list itself is represented by a struct that includes a pointer to the head node and the size of the list.

/* 
// These struct definitions are in the header file as well.
typedef struct linkedListNode 
{
    void* value;                   // Value stored in the node (can be of any data type using void pointer)
    struct linkedListNode* next;   // Pointer to the next node in the linked list
} linkedListNode;

typedef struct linkedList 
{
    linkedListNode* head;   // Pointer to the first node in the linked list
    size_t size;            // Size of the linked list, i.e., the number of nodes
} linkedList;
*/

// Function to create an empty linked list
linkedList* create_LinkedList() 
{
    linkedList* list = (linkedList*)malloc(sizeof(linkedList));
    list->size = 0;
    list->head = NULL;

    return list;
}

// Function to add a new node to the end of the linked list
void add_linkedList(linkedList* list, void* value) 
{
    linkedListNode* newNode = (linkedListNode*)malloc(sizeof(linkedListNode));
    newNode->value = value;
    newNode->next = NULL;

    if(list->head == NULL) 
    {
        // If the list is empty, make the new node the head
        list->head = newNode;
    } 
    else 
    {
        // Traverse to the end of the list and add the new node
        linkedListNode* current = list->head;
        while(current->next != NULL) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Function to delete the head of the linked list
void deleteHead_LinkedList(linkedList* list) 
{
    if (list->head != NULL) 
    {
        linkedListNode* newHead = list->head->next;
        free(list->head);
        list->head = newHead;
        list->size--;
    }
}

// Function to delete the first occurrence of a value from the linked list
void deleteFirstOccurrence_LinkedList(linkedList* list, void* value) 
{
    linkedListNode* current = list->head;
    linkedListNode* previous = NULL;

    // Search for the first occurrence of the value
    while (current != NULL && current->value != value) 
    {
        previous = current;
        current = current->next;
    }

    // If the value is found, update the pointers to skip the node
    if (current != NULL) 
    {
        if (previous != NULL) 
        {
            previous->next = current->next;
        } 
        else 
        {
            // If the head is the node to be deleted, update the head
            list->head = current->next;
        }

        free(current);
        list->size--;
    }
}

// Function to print the linked list
void print_LinkedList(linkedList* list) 
{
    linkedListNode* current = list->head;
    while (current != NULL) 
    {
        printf("%d->", *(int *)current->value);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to free the memory used by the linked list
void free_LinkedList(linkedList* list) 
{
    linkedListNode* current = list->head;
    while (current != NULL) 
    {
        linkedListNode* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}