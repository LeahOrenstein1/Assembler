#include "symbol.h"


/*Creating a symbol from the given values*/
ptrSymbol createSymbol(int position, symbolType type, int lineNumber)
{
    /*Initializing the values*/
    ptrSymbol ptr = malloc(sizeof(symbol));
    if (ptr == NULL)
    {
        fprintf(stderr, "Error: can not allocate memory for a new symbol\n");
        safeExit(1);
    }

    /*Updating relevant values*/
    ptr->position = position;
    ptr->type = type;
    ptr->lineNum = lineNumber;

    return ptr;
}

/*Function to print a symbol*/
void printSymbol(void* symbol)
{
    printf("position: %d, type: %d\n", ((ptrSymbol)symbol)->position, ((ptrSymbol) symbol)->type);
}

/*Function to free a symbol*/
void freeSymbol(void* ptr)
{   
    free((ptrSymbol)ptr);
}