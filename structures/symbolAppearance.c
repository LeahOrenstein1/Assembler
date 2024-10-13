#include "symbolAppearance.h"


ptrSymbolAppearance createSymbolAppearance(int position, int lineNum)
{
    ptrSymbolAppearance newSymbolAppearance = (ptrSymbolAppearance)malloc(sizeof(symbolAppearance));
    if (newSymbolAppearance == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        safeExit(1);
    }
    newSymbolAppearance->position = position;
    newSymbolAppearance->lineNum = lineNum;
    return newSymbolAppearance;
}

void freeSymbolAppearance(void* ptr)
{
    free((ptrSymbolAppearance)ptr);
}

void printSymbolAppearance(void* ptr)
{
    printf("position: %d\n", ((ptrSymbolAppearance)ptr)->position);
}





