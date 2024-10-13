#include "command.h"

/*Functions for handling with a command.*/

/*Function for printing a command*/
void printCommand(void* ptr)
{
    printf("%s",((ptrCommand)ptr)->comLine);
}

/*Function to free a command*/
void freeCommand(void* ptr)
{   
    free((ptrCommand)ptr);
}