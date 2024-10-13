#ifndef NODE_H
#define NODE_H

/**
 * @struct node
 * @brief Represents a node in a linked list.
 *
 * This structure is used to create nodes for a linked list implementation.
 * It contains a key, a pointer to a value, and a pointer to the next node.
 */
struct node {
    char key[80];    /**< The key of the node, limited to 80 characters. */
    void *ptrVal;    /**< A pointer to the value stored in the node. */
    struct node *next; /**< A pointer to the next node in the list. */
};

/** Typedef for a pointer to a node structure. */
typedef struct node* ptrNode;

#endif /* NODE_H */