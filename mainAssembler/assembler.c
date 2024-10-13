/**

# Assembler Program

Author: Leah Orenstein
August 2024 

This program implements a two-pass assembler for a custom assembly language. It processes assembly language source files and generates machine code output.

## Key Components:

1. **Pre-assembler**: Handles macro expansions in the source code.
2. **First Pass**: 
   - Builds the symbol table
   - Processes assembly instructions and data directives
   - Performs initial error checking
3. **Second Pass**:
   - Resolves symbol addresses
   - Generates final machine code
   - Creates output files (.ob, .ext, .ent)

## Main Function Flow:

1. Processes command line arguments to get input file names
2. For each input file:
   - Runs the pre-assembler
   - Performs the first pass
   - If no errors, performs the second pass
   - Generates output files
3. Handles memory allocation and deallocation
4. Provides error reporting and management

This assembler is designed to be modular and extensible, with separate components handling different aspects of the assembly process.

## Note on Debugging Functions:
This program includes several print functions that were used for debugging during development. These functions are currently not in use in the main program flow but have been left in the code for potential future debugging needs or enhancements.

*/







#include "definitions/definitions.h"
#include "structures/tableStructure/list.h"
#include "structures/command.h"
#include "structures/macro.h"
#include "process/preAssembler.h"
#include "process/firstPass.h"
#include "process/processingFunctions/processingLineFunct.h"
#include "process/secondPass.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    int i, j;
    int DC = 0;
    int IC = 100;

    int suffix[] = {3, 0, 3, 3, 4, 4};
    char* fileNames[6];

    ptrNode macroList = NULL;
    ptrNode memoryImage = NULL;
    ptrNode symbolList = NULL;
    ptrNode entryList = NULL;

    /*A list for storing the memory words that uses symbols*/
    ptrNode symAppearMem = NULL;  

    /*A flag for checking if any error found and we shalln't create the .ob .ext .ent files*/
    boolean errorFound = false;

    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        safeExit(1);
    }

    /*Updating the global pointers for freeing case*/
    MACRO_LIST_PTR = &macroList;
    SYMBOL_LIST_PTR = &symbolList;
    ENTRY_LIST_PTR = &entryList;
    MEM_IMAGE_PTR = &memoryImage;
    SYM_APPEAR_MEM_PTR = &symAppearMem;


    for (i = 1; i < argc; i++) 
    {
        /*Update the counters*/
        IC = 100;
        DC = 0;

        /*Allocating memory and initializing the file names variables*/
        for (j = 0; j < 6; j++)
        {
            fileNames[j] = AllocateMemFileName(argv[i], strlen(argv[i]) + suffix[j]);
        }

        /*Updating the errorFound flag to false, no error*/
        errorFound = false;

        /*Generate output file names*/
        sprintf(fileNames[inputFileName], "%s.as", fileNames[baseName]);
        sprintf(fileNames[amFile], "%s.am", fileNames[baseName]);
        sprintf(fileNames[obFile], "%s.ob", fileNames[baseName]);
        sprintf(fileNames[entFile], "%s.ent", fileNames[baseName]);
        sprintf(fileNames[extFile], "%s.ext", fileNames[baseName]);

        /*Updating the global pointers for freeing case*/
        MACRO_LIST_PTR = &macroList;
        SYMBOL_LIST_PTR = &symbolList;
        ENTRY_LIST_PTR = &entryList;
        MEM_IMAGE_PTR = &memoryImage;
        SYM_APPEAR_MEM_PTR = &symAppearMem;
        
        /* Step 1: Pre-assembler (macro expansion)*/
        if (!preprocessFile(fileNames[inputFileName], fileNames[amFile], &macroList)) 
        {
            fprintf(stderr, "Error in pre-processor stage for file %s\n", fileNames[inputFileName]);

            /*Freeing memory and closing files safely*/
            freeAllResources();
            closeFiles();

            continue;
        }

        /* Step 2: First pass */
        if (!firstPass(fileNames[amFile], &memoryImage, &symbolList, &symAppearMem, &entryList, &IC, &DC)) 
        {
            errorFound = true;
        }

        /*Check if there is a memory overflow*/
        if (IC + DC > MAX_MEMORY_SIZE)
        {
            fprintf(stderr, "Error: Memory overflow.\n");
            errorFound = true; 
        }

        /* Step 3: Second pass */
        if (!secondPass(fileNames, memoryImage, symbolList, entryList, symAppearMem, IC, DC, errorFound)) 
        {
            /*Freeing memory and closing files safely*/
            freeAllResources();
            closeFiles();

            continue;
        }
        
        /*Updating the lists pointers to null*/

        /* Free allocated memory and update the global pointers*/
        freeAllResources();
        closeFiles();

    }

    return 0;
}
