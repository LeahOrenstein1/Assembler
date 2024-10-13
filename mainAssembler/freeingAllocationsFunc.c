#include "freeingAllocationsFunc.h"


/*Function for exiting the program safely in an allocation error*/
void safeExit(int status) 
{
    freeAllResources();
    closeFiles();
    exit(status);
}


/*Function for freeing all the allocated resources*/
void freeAllResources() 
{
    int i;

    /*Freeing the file names variables*/
    for (i = 0; i < 6; i++) 
    {
        if (FILE_NAMES_PTR[i] != NULL) 
        {
            free(FILE_NAMES_PTR[i]);
            FILE_NAMES_PTR[i] = NULL;
        }
    }

    /*Freeing the lists*/
    if (SYMBOL_LIST_PTR != NULL) 
    {
        freeList(SYMBOL_LIST_PTR, freeSymbol);
        SYMBOL_LIST_PTR = NULL;
    }
    if (ENTRY_LIST_PTR != NULL) 
    {
        freeList(ENTRY_LIST_PTR, freeSymbol);
        ENTRY_LIST_PTR = NULL;
    }
    if (DATA_IMAGE_PTR != NULL)
    {
        freeList(DATA_IMAGE_PTR, NULL);
        DATA_IMAGE_PTR = NULL;
    }
    if (CODE_IMAGE_PTR != NULL)
    {
        freeList(CODE_IMAGE_PTR, NULL);
        CODE_IMAGE_PTR = NULL;
    }
    if (MEM_IMAGE_PTR != NULL) 
    {
        freeList(MEM_IMAGE_PTR, NULL);
        MEM_IMAGE_PTR = NULL;
    }
    if (SYM_APPEAR_MEM_PTR != NULL) 
    {
        freeList(SYM_APPEAR_MEM_PTR, freeSymbolAppearance);
        SYM_APPEAR_MEM_PTR = NULL;
    }
    if (CODE_IMAGE_PTR != NULL) 
    {
        freeList(CODE_IMAGE_PTR, NULL);
        CODE_IMAGE_PTR = NULL;
    }
    if (DATA_IMAGE_PTR != NULL) 
    {
        freeList(DATA_IMAGE_PTR, NULL);
        DATA_IMAGE_PTR = NULL;
    }
    if (MACRO_LIST_PTR != NULL) 
    {
        freeList(MACRO_LIST_PTR, freeMacro);
        MACRO_LIST_PTR = NULL;
    }
}


/*Function for closing the open files*/
void closeFiles()
{
    if (INPUT_FILE != NULL) 
    {
        fclose(INPUT_FILE);
        INPUT_FILE = NULL;
    }
    if (AM_FILE != NULL) 
    {
        fclose(AM_FILE);
        AM_FILE = NULL;
    }
    if (OB_FILE != NULL) 
    {
        fclose(OB_FILE);
        OB_FILE = NULL;
    }
    if (ENT_FILE != NULL) 
    {
        fclose(ENT_FILE);
        ENT_FILE = NULL;
    }
    if (EXT_FILE != NULL) 
    {
        fclose(EXT_FILE);
        EXT_FILE = NULL;
    }
    if (INTERMEDIATE_FILE != NULL) 
    {
        fclose(INTERMEDIATE_FILE);
        INTERMEDIATE_FILE = NULL;
    }
}
