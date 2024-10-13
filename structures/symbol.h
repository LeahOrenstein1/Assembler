#ifndef SYMBOL_H
#define SYMBOL_H

#include <string.h>
#include "mainAssembler/freeingAllocationsFunc.h"

/**
 * @enum symbolType
 * @brief Defines the different types of symbols.
 */
typedef enum {
    SYMBOL_TYPE_CODE,       /**< Symbol represents code. */
    SYMBOL_TYPE_DATA,       /**< Symbol represents data. */
    SYMBOL_TYPE_ENTRY,      /**< Symbol is an entry point. */
    SYMBOL_TYPE_EXTERN,     /**< Symbol is external. */
    SYMBOL_TYPE_BEFORE_EX_EN /**< Symbol is defined before .extern or .entry directive. */
} symbolType;

/**
 * @struct symbol
 * @brief Represents a symbol in the assembly code.
 */
typedef struct 
{
    int position;     /**< The position of the symbol in memory. */
    symbolType type;  /**< The type of the symbol. */
    int lineNum;      /**< The line number where the symbol is defined. */
} symbol;

/** Pointer to a symbol structure. */
typedef symbol *ptrSymbol;

/**
 * @brief Creates a new symbol.
 * 
 * @param position The position of the symbol in memory.
 * @param type The type of the symbol.
 * @param lineNumber The line number where the symbol is defined.
 * @return ptrSymbol A pointer to the newly created symbol.
 */
ptrSymbol createSymbol(int position, symbolType type, int lineNumber);

/**
 * @brief Prints the details of a symbol.
 * 
 * @param symbol A void pointer to the symbol to be printed.
 */
void printSymbol(void* symbol);

/**
 * @brief Frees the memory allocated for a symbol.
 * 
 * @param ptr A void pointer to the symbol to be freed.
 */
void freeSymbol(void *ptr);

#endif /* SYMBOL_H */