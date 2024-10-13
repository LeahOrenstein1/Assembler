#include "secondPass.h"


/*For each symbol, if data symbol - increase the position*/
int symbolPositionUpdate(ptrNode symbolList, int IC)
{
    ptrSymbol symbol = NULL;

    /*For each data symbol, updates the location with the final IC*/
    while (symbolList != NULL)
    {
        symbol = (ptrSymbol)(symbolList->ptrVal);

        if (symbol->type == SYMBOL_TYPE_DATA)  /*Data symbol found*/
        {
            symbol->position += IC;
        }

        symbolList = symbolList->next;
    }

    /*Success*/
    return true;
}

/*For each entry symbol, updates the adress according to its value in the symbolList*/
int updateEnSymbolsAdress(ptrNode symbolList, ptrNode entryList)
{
    ptrSymbol symbol = NULL;
    ptrNode tempNode = NULL;

    while (entryList != NULL)
    {
        tempNode = searchKey(symbolList, entryList->key);

        if (tempNode == NULL)  /*If the symbol is defined in the symbol list*/
        {
            return false;
        }

        symbol = (ptrSymbol)(tempNode->ptrVal);
        symbol->type = ENTRY;
        ((ptrSymbol)entryList->ptrVal)->position = symbol->position; /*Update the entry list with the symbol and its adress*/

        entryList = entryList->next;
    }

    /*Success*/
    return true;
}

/*Create the .ext file*/
int createExFile(char* outputFileName, ptrNode symbolList, ptrNode symbolAppearance)
{
    FILE* externFile = NULL;
    ptrSymbol symbol = NULL;
    ptrSymbolAppearance symbolMemoryAdress = NULL;
    ptrNode symbolsMemList = symbolAppearance;

    /*Open the extern file for writing*/
    externFile = fopen(outputFileName, "w");
    if (externFile == NULL)
    {
        fprintf(stderr, "Error:%s: Could not create extern file.\n", outputFileName);
        safeExit(1);
    }

    /*Update the global pointer*/
    EXT_FILE = externFile;
    
    while (symbolList != NULL)
    {
        symbol = (ptrSymbol)(symbolList->ptrVal);

        if (symbol->type == SYMBOL_TYPE_EXTERN)  /*If the symbol is external*/
        {
            /*Look for the symbol in the symbol appearance list*/
            while (symbolsMemList != NULL)
            {
                /*Found appearance of the external symbol*/
                if (strcmp(symbolsMemList->key, symbolList->key) == 0)
                {
                    symbolMemoryAdress = (ptrSymbolAppearance)(symbolsMemList->ptrVal);
                    fprintf(externFile, "%s %04d\n", symbolList->key, symbolMemoryAdress->position);
                }
                symbolsMemList = symbolsMemList->next;
            } 

            /*Initiallize the symbol appearanc list pointer*/
            symbolsMemList = symbolAppearance;
        }

        symbolList = symbolList->next;
    }

    /*Success*/
    return true;
}

/*Create the .ent file*/
int createEnFile(char* outputFileName, ptrNode symbolList, ptrNode entryList)
{
    FILE* entryFile = NULL;
    
    /*Open the entry file for writing*/
    entryFile = fopen(outputFileName, "w");
    if (entryFile == NULL)
    {
        fprintf(stderr, "Error:%s: Could not create entry file.\n", outputFileName);
        safeExit(1);
    }

    /*Update the global pointer*/
    ENT_FILE = entryFile;

    /*For each entry symbol - prints it and its adress to the .ent file*/
    while (entryList != NULL)
    {
        fprintf(entryFile, "%s %04d\n", entryList->key, ((ptrSymbol)(entryList->ptrVal))->position);
        entryList = entryList->next;
    }

    /*Success*/
    return true;
}

/*Create the .ob file*/
int createObFile(char* outputFileName, ptrNode memoryImage, ptrNode symbolList, ptrNode symAppearanceList, int IC, int DC)
{
    FILE* obFile = NULL;
    int i;
    long int decimalMemoryWord;

    /*Variables for handling with symbol adress memory words*/
    ptrSymbolAppearance symbolAppear = NULL; 
    boolean isLabel = false;
    char labelAdress[MEMORY_WORD_LENGTH + 1] = {0};
    ptrSymbol symbol = NULL;

    /*Temp lists*/
    ptrNode tempSymNode = NULL;
    ptrNode symAppearListPtr = symAppearanceList;

    /*Open the ob file for writing*/
    obFile = fopen(outputFileName, "w");
    if (obFile == NULL)
    {
        fprintf(stderr, "Error:%s: Could not create ob file.\n", outputFileName);
        safeExit(1);
    }

    /*Update the global pointer*/
    OB_FILE = obFile;

    /*Prints the IC & DC counters*/
    fprintf(obFile, "%d %d\n", IC - 100, DC);

    /*For each memory word - prints it to the .ob file with the adress*/
    for (i = 100; i < IC + DC; i++)
    {
        isLabel = false;

        if (memoryImage == NULL)  /*If the memory image list is empty*/
        {
            return true;
        }

        /*If the memory word is soposed to be a label adress*/
        if (strcmp(memoryImage->key, "???????????????") == 0) 
        {
            /*Look for the label name of the current memory adress*/
            while (symAppearListPtr != NULL)
            {
                symbolAppear = (ptrSymbolAppearance)(symAppearListPtr->ptrVal);

                /*If the current symbol appear refers to the current memory adress*/
                if (symbolAppear->position == i)  
                {
                    tempSymNode = searchKey(symbolList, symAppearListPtr->key);
                    symbol = (ptrSymbol)(tempSymNode->ptrVal);

                    /*Create the memory word of the label adress*/
                    intToBinaryString(symbol->position, labelAdress, ARE_FIRST_INDEX);
                    strncpy(labelAdress + ARE_FIRST_INDEX,  symbol->type == SYMBOL_TYPE_EXTERN? E_BINARY : R_BINARY, ARE_LENGTH);
                    
                    decimalMemoryWord = strtol(labelAdress, NULL, 2);

                    /*Print it to the obj file*/
                    fprintf(obFile, "%04d %05o\n", i, (unsigned int)decimalMemoryWord);

                    isLabel = true;  /*Update the isLabel flag*/
                    memoryImage = memoryImage->next;
                    break;
                }
                symAppearListPtr = symAppearListPtr->next;
            }   
            symAppearListPtr = symAppearanceList; /*initiallize the symAppearListPtr pointer*/         
        }

        /*If the current memory word is a label adress - continue to the next memory word, 
        printed already*/
        if (isLabel) continue;

        decimalMemoryWord = strtol(memoryImage->key, NULL, 2);

        fprintf(obFile, "%04d %05o\n", i, (unsigned int)decimalMemoryWord);

        memoryImage = memoryImage->next;
    }

    /*Success*/
    return true;
}

/*Checks the validation of the ex - en symbols and the symbols appearanse*/
int symbolValidation(char* inputFileName, ptrNode symbolList, ptrNode memAppearList, ptrNode entryList)
{
    boolean error = false;
    ptrNode tempNode = NULL;

    /*For each symbol appearance - checks if defined in the file*/
    while (memAppearList != NULL)
    {
        tempNode = searchKey(symbolList, memAppearList->key);
        if (tempNode == NULL)  /*If the symbol is not defined in the file*/
        {
            fprintf(stderr, "Error:%s:%d: Symbol %s used but not defined.\n", inputFileName, ((ptrSymbolAppearance)memAppearList->ptrVal) -> lineNum, memAppearList->key);
            error = true;
        }

        memAppearList = memAppearList->next;
    }

    /*For each entry symbol - checks if defined in the file*/
    while (entryList != NULL)
    {
        tempNode = searchKey(symbolList, entryList->key);
        if (tempNode == NULL)  /*If the symbol is not defined in the file*/
        {
            fprintf(stderr, "Error:%s:%d: Entry symbol %s is not defined in the file.\n", inputFileName, ((ptrSymbol)entryList->ptrVal)->lineNum, entryList->key);
            error = true;
        }
        
        entryList = entryList->next;
    }

    /*Success*/
    return error? false : true;
}

/*The second pass process*/
int secondPass(char* FileNames[6], ptrNode memoryImage, ptrNode symbolList, ptrNode enteryList, ptrNode symAppearMem, int IC, int DC, boolean errorFound)
{
    /*Update the position of the data symbols in the symbol list*/
    if (symbolPositionUpdate(symbolList, IC) == false)  errorFound = true;

    /*Update the entry symbols with the correct adress*/
    if (updateEnSymbolsAdress(symbolList, enteryList) == false)  errorFound = true;

    /*Check if all the symbols in the memory appearance list are defined in the file*/
    if (symbolValidation(FileNames[amFile], symbolList, symAppearMem, enteryList) == false)  errorFound = true;

    /*If there was an error*/
    if (errorFound)
    {
        return false;
    }

    if (enteryList != NULL)  /*If there are entry symbols*/
    {
        /*Create the .ent file*/
        if (createEnFile(FileNames[entFile], symbolList, enteryList) == false)
        {
            fprintf(stderr, "Error:%s: Could not create entry file.\n", FileNames[entFile]);
            return false;
        }
    }

    if (isThereExtern(symbolList) == true)  /*If there are external symbols*/
    {
        /*Create the .ext file*/
        if (createExFile(FileNames[extFile], symbolList, symAppearMem) == false)
        {
            fprintf(stderr, "Error:%s: Could not create extern file.\n", FileNames[extFile]);
            return false;
        }
    }
    
    /*Create the .ob file*/
    if (createObFile(FileNames[obFile], memoryImage, symbolList, symAppearMem, IC, DC) == false)
    {
        fprintf(stderr, "Error:%s: Could not create ob file.\n", FileNames[obFile]);
        return false;
    }

    /*Success*/
    return true;
}

/*Returns true if there is an external label*/
boolean isThereExtern(ptrNode symbolList)
{
    ptrSymbol symbol = NULL;
    
    while (symbolList != NULL)
    {
        symbol = (ptrSymbol)(symbolList->ptrVal);   
        if (symbol->type == SYMBOL_TYPE_EXTERN)  /*If there is an external symbol*/
        {
            return true;
        }
        symbolList = symbolList->next;
    }

    /*No external label*/
    return false;
}