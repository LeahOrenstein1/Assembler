#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>

#include "mainAssembler/freeingAllocationsFunc.h"

/**
 * @struct command
 * @brief Represents a single command line.
 *
 * This structure holds a single command line as a string.
 */
typedef struct
{
    char comLine[80]; /**< The command line string, limited to 80 characters. */
} command;

/** Pointer to a command structure. */
typedef command* ptrCommand;

/**
 * @brief Prints a command.
 *
 * This function prints the command line stored in the command structure.
 *
 * @param ptr Pointer to the command structure to be printed.
 */
void printCommand(void* ptr);

/**
 * @brief Frees the memory allocated for a command.
 *
 * This function frees the memory allocated for a command structure.
 *
 * @param ptr Pointer to the command structure to be freed.
 */
void freeCommand(void* ptr);

#endif /* COMMAND_H */