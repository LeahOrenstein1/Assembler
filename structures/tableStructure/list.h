#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "mainAssembler/freeingAllocationsFunc.h"

/**
 * @brief Creates a new node with the given key and value.
 * @param key The key for the new node.
 * @param val A pointer to the value to be stored in the node.
 * @return A pointer to the newly created node.
 */
ptrNode createNode(char key[], void* val);

/**
 * @brief Adds a new node at the beginning of the list.
 * @param head A pointer to the pointer of the head of the list.
 * @param key The key for the new node.
 * @param val A pointer to the value to be stored in the node.
 */
void addNodeAtBeginning(ptrNode* head, char key[], void* val);

/**
 * @brief Adds a new node at the end of the list.
 * @param head A pointer to the pointer of the head of the list.
 * @param key The key for the new node.
 * @param val A pointer to the value to be stored in the node.
 */
void addNodeAtEnd(ptrNode* head, char key[], void* val);

/**
 * @brief Appends an existing node to the end of the list.
 * @param head A pointer to the pointer of the head of the list.
 * @param nodeToAppend The node to append to the list.
 */
void appendNode(ptrNode* head, ptrNode nodeToAppend);

/**
 * @brief Searches for a node with the given key in the list.
 * @param head A pointer to the head of the list.
 * @param key The key to search for.
 * @return A pointer to the found node, or NULL if not found.
 */
ptrNode searchKey(ptrNode head, char key[]);

/**
 * @brief Prints the keys of all nodes in the list.
 * @param head A pointer to the head of the list.
 */
void printKeys(ptrNode head);

/**
 * @brief Prints the values of all nodes in the list using a provided print function.
 * @param head A pointer to the head of the list.
 * @param ptrPrintFunc A pointer to a function that prints a single value.
 */
void printValues(ptrNode head, void (*ptrPrintFunc)(void*));

/**
 * @brief Frees all nodes in the list and their values if a free function is provided.
 * @param head A pointer to the pointer of the head of the list.
 * @param freeValue A pointer to a function that frees a single value.
 */
void freeList(ptrNode* head, void (*freeValue)(void*));

/**
 * @brief Prints the structure of the list and its values using a provided print function.
 * @param head A pointer to the head of the list.
 * @param ptrPrintFunc A pointer to a function that prints a single value.
 */
void printListStructureAndVal(ptrNode head, void (*ptrPrintFunc)(void*));

/**
 * @brief Prints the structure of the list.
 * @param head A pointer to the head of the list.
 */
void printListStructure(ptrNode head);

/**
 * @brief Prints the entry list.
 * @param entryList A pointer to the head of the entry list.
 */
void printEntryList(ptrNode entryList);

#endif /* TABLE_H */