#include "macro.h"


/*Functions for handling a macro*/

/*Function for printing macro's commans*/
void printMacroCommands(void* ptr)
{

    /*Print command for each command in the list (By sending the print function of the command structure)*/
    printValues(((ptrMacro)ptr)->commandList, printCommand);

}

/*Function for freeing a macro*/
void freeMacro(void* ptr)
{
    ptrMacro macro = (ptrMacro)ptr;

    if (macro->commandList != NULL)
    {
        freeList((&macro->commandList), freeCommand);
    }

    free((ptrMacro)ptr);
}