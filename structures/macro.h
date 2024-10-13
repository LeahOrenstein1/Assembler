#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>

#include "structures/tableStructure/list.h"
#include "command.h"

/**
 * @struct macro
 * @brief Represents a macro definition.
 *
 * This structure holds a list of commands that make up a macro definition.
 */
typedef struct 
{
    ptrNode commandList; /**< Pointer to the list of commands in the macro. */
} macro;

/** Pointer to a macro structure. */
typedef macro* ptrMacro;

/**
 * @brief Prints the commands of a macro.
 *
 * This function prints all the commands stored in a macro's command list.
 *
 * @param ptr Pointer to the macro structure whose commands are to be printed.
 */
void printMacroCommands(void* ptr);

/**
 * @brief Frees the memory allocated for a macro.
 *
 * This function frees the memory allocated for a macro structure,
 * including its command list.
 *
 * @param ptr Pointer to the macro structure to be freed.
 */
void freeMacro(void* ptr);

#endif /* MACRO_H */