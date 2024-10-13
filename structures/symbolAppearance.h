#ifndef SYMBOLAPPEARANCE_H
#define SYMBOLAPPEARANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions/definitions.h"
#include "mainAssembler/freeingAllocationsFunc.h"

/**
 * @struct symbolAppearance
 * @brief Represents an appearance of a symbol in memory.
 * 
 * This structure is used to keep track of symbol appearances in the memory
 * words list for use in the second pass of the assembler.
 */
typedef struct 
{
    int position; /**< The position of the symbol appearance in memory. */
    int lineNum;  /**< The line number where the symbol appears. */
} symbolAppearance;

/** Pointer to a symbolAppearance structure. */
typedef symbolAppearance *ptrSymbolAppearance;

/**
 * @brief Creates a new symbolAppearance.
 * 
 * @param position The position of the symbol appearance in memory.
 * @param lineNum The line number where the symbol appears.
 * @return ptrSymbolAppearance A pointer to the newly created symbolAppearance.
 */
ptrSymbolAppearance createSymbolAppearance(int position, int lineNum);

/**
 * @brief Frees the memory allocated for a symbolAppearance.
 * 
 * @param ptr A void pointer to the symbolAppearance to be freed.
 */
void freeSymbolAppearance(void* ptr);

/**
 * @brief Prints the details of a symbolAppearance.
 * 
 * @param ptr A void pointer to the symbolAppearance to be printed.
 */
void printSymbolAppearance(void* ptr);

#endif /* SYMBOLAPPEARANCE_H */