#include "list.h"


/*Function for creating a new node*/
ptrNode createNode(char key[], void* val) 
{
    /* Allocate memory for a new node */
    ptrNode newNode = (ptrNode)malloc(sizeof(struct node));

    /* Check if memory allocation was successful */
    if (newNode == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        safeExit(1);
    }

    /* Copy the key into the new node */
    strcpy(newNode->key, key);

    /* Set the value pointer of the new node */
    newNode->ptrVal = val;

    /* Initialize the next pointer to NULL */
    newNode->next = NULL;

    /* Return the pointer to the new node */
    return newNode;
}


/*Function for adding a new node to a table, gets value and pointer to the table and returns 1 if succeeded, 0 otherwise.*/
void addNodeAtBeginning(ptrNode* head, char key[], void* val)
{
    /* Create a new node with the given key and value */
    ptrNode newNode = createNode(key, val);

    /* Set the next pointer of the new node to the current head */
    newNode->next = *head;

    /* Update the head to point to the new node */
    *head = newNode;
}

/*Function for adding a node to the list in the end*/
void addNodeAtEnd(ptrNode* head, char key[], void* val)
{
    ptrNode newNode = createNode(key, val);
    ptrNode current = *head;

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

/*Function for adding a node to the end of the list by its pointer*/
void appendNode(ptrNode* head, ptrNode nodeToAppend) 
{
    ptrNode current;

    if (*head == NULL) 
    {
        *head = nodeToAppend;
        return;
    }

    current = *head;
    while (current->next != NULL) 
    {
        current = current->next;
    }

    current->next = nodeToAppend;
}


/*Function for searching a node in a table by key, returns a pointer to the node if found, otherwise NULL*/
ptrNode searchKey(ptrNode head, char key[]) 
{
    ptrNode current = head;  /* Pointer for traversing the list */

    /* Iterate through the list */
    while (current != NULL) 
    {
        /* Compare the current node's key with the search key */
        if (strcmp(current->key, key) == 0) 
        {
            return current;  /* Return the node if a match is found */
        }
        current = current->next;  /* Move to the next node */
    }

    return NULL;  /* Return NULL if the key is not found in the list */
}


/*Fubction for printing the list's keys*/
void printKeys(ptrNode head) 
{
    ptrNode current = head;  /* Pointer to the current node in the list */
    
    /* Check if the list is empty */
    if (current == NULL) 
    {
        printf("The list is empty.\n");
        return;
    }
    
    /* Print header for the list of keys */
    printf("Keys in the list:\n");

    /* Iterate through all nodes in the list */
    while (current != NULL) 
    {
        /* Print the key of the current node followed by an arrow */
        printf("%s -> ", current->key);

        /* Move to the next node */
        current = current->next;
    }
    
    /* Print "NULL" to indicate the end of the list */
    printf("NULL\n");
}


/*Function to print the list's values by using the accurate print function of the current struct value*/
void printValues(ptrNode head, void (*ptrPrintFunc)(void*))
{
    ptrNode current = head;  /* Pointer to the current node in the list */
    
    /* Check if the list is empty */
    if (current == NULL) 
    {
        printf("The list is empty.\n");
        return;
    }
    
    /* Iterate through all nodes in the list */
    while (current != NULL) 
    {
        /* Print the value of the current node using the provided print function */
        ptrPrintFunc(current->ptrVal);
        
        /* Move to the next node */
        current = current->next;
        
        /* Print a new line after each value */
        printf("\n");
    }
}


/* Function to free a list and its values */
void freeList(ptrNode* head, void (*freeValue)(void*))
{
    ptrNode current = *head;
    ptrNode next;

    if (head == NULL || *head == NULL) {
        return;
    }

    while (current != NULL)
    {
        next = current->next;
        
        /* Free the value if a free function was provided */
        if (freeValue != NULL && current->ptrVal != NULL)
        {
            freeValue(current->ptrVal);
        }
        
        /* Free the node itself */
        free(current);
        
        current = next;
    }

    /* Set the head to NULL as the list is now empty */
    *head = NULL;

}


/*Function for debuging*/
void printListStructureAndVal(ptrNode head, void (*ptrPrintFunc)(void*)) 
{
    ptrNode current = head;
    int count = 0;
    printf("Printing list structure:\n");

    while (current != NULL) 
    {
        printf("Node %d: Key = %s\n", count++, current->key);
        ptrPrintFunc(current->ptrVal);
        current = current->next;
    }

    printf("Total nodes: %d\n", count);
}


/*Function for debuging*/
void printListStructure(ptrNode head) 
{
    ptrNode current = head;
    int count = 0;
    printf("Printing list structure:\n");

    while (current != NULL) 
    {
        printf("Node %d: Key = %s\n", count++, current->key);
        current = current->next;
    }

    printf("Total nodes: %d\n", count);
}

void printEntryList(ptrNode entryList) 
{
    ptrNode current = entryList;
    int count = 0;
    while (current != NULL) {
        printf("Entry %d: Key: %s, Value address: %p\n", 
               count++, current->key, current->ptrVal);
        current = current->next;
    }
}