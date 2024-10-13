#include "preAssembler.h"


/*Function for finding all macro definitions*/
int processMacroDefinitions(FILE* inputFile, FILE* outputFile, ptrNode *ptrMacroList, const char *inputFileName) 
{
    /*Declaring variables*/
    char line[MAX_LINE_LENGTH + 1];
    char trimmedLine[MAX_LINE_LENGTH];
    int countLines = 0;
    char currentMacroName[MAX_LABEL_LENGTH] = "";
    ptrNode macroList = NULL;

    /*Creating a macro structure for keeping macros if found*/
    ptrMacro currentMacro = NULL;
    char macroName[MAX_LABEL_LENGTH + 1];

    /*Variable to check if there are extra chars*/
    char* afterMacroName;
    ptrCommand newCommand;

    /*Flags*/
    int errorInMacroDef = false;
    int errorOccurred = false;
    int inMacroDefinition = 0;

    /*for each line in the input file*/
    while (fgets(line, sizeof(line), inputFile) != NULL)
    {
        countLines++;

        /*If it is a note line*/
        if (line[0] == ';')  continue;

        /*If the line is to long, there is an error*/
        if (strcspn(line, "\n") >= MAX_LINE_LENGTH)
        { 
            fprintf(stderr, "Error:%s:%d: Over 80 charecters in line.\n", inputFileName, countLines);
            errorOccurred = true;

            /* Consume the rest of the long line */
            while (strchr(line, '\n') == NULL) 
            {
                if (fgets(line, sizeof(line), inputFile) == NULL) 
                {
                    break;  /* End of file reached */
                }
            }

            continue;
        }

        line[strcspn(line, "\n")] = 0;  /* Remove newline character */
        
        /* Clearing the begining and the end from white chars */
        trimWhitespace(line, trimmedLine, MAX_LINE_LENGTH);

        /*If it is an empty line*/
        if (trimmedLine[0] == '\0') 
        {
            continue;
        }

        /*If there is a macro definition*/
        if (strncmp(trimmedLine, "macr", 4) == 0) 
        {
            inMacroDefinition = true;
            trimWhitespace(trimmedLine + 4, macroName, MAX_LABEL_LENGTH);

            /*Check if there's anything after the macro name */
            afterMacroName = macroName;
            while (*afterMacroName && !isspace(*afterMacroName)) afterMacroName++;
            if (*afterMacroName != '\0') 
            {
                fprintf(stderr, "Error:%s:%d: Invalid characters after macro name\n", inputFileName, countLines);
                errorInMacroDef = true;
                errorOccurred = true;
            }

            /*Check of the macro name is to long*/
            *afterMacroName = '\0';
            if (afterMacroName - macroName > MAX_LABEL_LENGTH)
            {
                fprintf(stderr, "Error:%s:%d: Macro name is too long, over 31 charecters.\n", inputFileName, countLines);
                errorInMacroDef = true;
            }

            /*Check if the macro name is a known word in the assembly language*/
            if(isRegister(macroName) || isCodeLine(macroName) || isExternLine(macroName) || isEntryLine(macroName) || (strncmp(macroName, "macr", 4) == 0 && isSpaceOrEnd(macroName[4])) || (strncmp(macroName, "endmacr", 7) == 0 && isSpaceOrEnd(macroName[7])))
            {
                fprintf(stderr, "Error:%s:%d: Macro name is a known word in the assembly language\n", inputFileName, countLines);
                errorInMacroDef = true;
                errorOccurred = true;
            }

            /*Check if the macro name is already defined*/
            if (searchKey(macroList, macroName) != NULL) 
            {
                fprintf(stderr, "Error:%s:%d: Macro name is already used\n", inputFileName, countLines);
                errorInMacroDef = true;
                errorOccurred = true;
            }

            if (errorInMacroDef) 
            {
                continue;
            }

            /* Copy macro name */
            strncpy(currentMacroName, macroName, MAX_LABEL_LENGTH - 1);
            currentMacroName[MAX_LABEL_LENGTH - 1] = '\0';
            
            /* Allocate memory for new macro */
            currentMacro = (ptrMacro)malloc(sizeof(macro));
            if (currentMacro == NULL) 
            {
                fprintf(stderr, "Memory allocation failed for a macro structure\n");
                safeExit(1);
            }
            currentMacro->commandList = NULL;
        } 
        /* Check if this line ends a macro definition */
        else if (strncmp(trimmedLine, "endmacr", strlen("endmacr")) == 0) 
        {
            /* Check if there's anything after 'endmacr' */
            if (strlen(trimmedLine) > 7) 
            {
                fprintf(stderr, "Error:%s:%d: Invalid characters after 'endmacr'\n", inputFileName, countLines);
                inMacroDefinition = false;
                errorOccurred = true;
                errorInMacroDef = true; 
            }

            if (errorInMacroDef)
            {
                if (currentMacro != NULL) 
                {
                    freeList(&(currentMacro->commandList), freeCommand);
                    free(currentMacro);  
                    currentMacro = NULL;
                }
            }
            else
            {
                /* Add the completed macro to the list */
                addNodeAtEnd(&macroList, currentMacroName, currentMacro);
            }

            inMacroDefinition = 0;
            currentMacro = NULL;
            errorInMacroDef = false; 
        }
        /* If we're inside a macro definition and no errors, add line to macro */
        else if (inMacroDefinition && !errorInMacroDef) 
        {
            /* Allocate memory for new command */
            newCommand = (ptrCommand)malloc(sizeof(command));
            if (newCommand == NULL) 
            {
                fprintf(stderr, "Memory allocation failed for command\n");
                safeExit(1);
            }

            strcpy(newCommand->comLine, line);
            addNodeAtEnd(&(currentMacro->commandList), "", newCommand);
        } 
        else 
        {
            /* If not in a macro definition, write line to output file */
            fprintf(outputFile, "%s\n", line);
        }
    }

    *ptrMacroList = macroList;

    /*Returning 1 for success, 0 if errors were found*/
    return errorOccurred? false : true;
}



/*Function for replacing the calls for macro to the macro's commands*/
int expandMacros(FILE* inputFile, FILE* outputFile, ptrNode macroList, const char* inputFileName)  
{
    char line[MAX_LINE_LENGTH];
    char trimmedLine[MAX_LINE_LENGTH];
    char label[MAX_LINE_LENGTH];
    char tempLabel[MAX_LINE_LENGTH];
    char tempMacAfterLable[MAX_LINE_LENGTH];
    char checkMacAfterLable[MAX_LINE_LENGTH];
    int lineNum = 1;
    ptrNode macroNode;
    ptrMacro macro;
    ptrNode currentCommand;
    ptrCommand cmd;
    boolean error = false;
    int i;

    /*For each line in the input file*/
    while (fgets(line, MAX_LINE_LENGTH, inputFile)) 
    {
        line[strcspn(line, "\n")] = 0;  /* Remove newline character */
        
        /* Clearing the begining and the end from white spaces */
        trimWhitespace(line, trimmedLine, MAX_LINE_LENGTH);

        /*Taking care about macro after a lable definition*/
        i = 0;

        /*Looking for the end of a lable definition. If there is - prints it, and removes it.*/
        while (i < strlen(trimmedLine) && trimmedLine[i] != ':')
        {
            i++;
        }

        if (trimmedLine[i] == ':')
        {
            strncpy(label, trimmedLine, i + 1);
            tempLabel[i + 1] = '\0';

            trimWhitespace(tempLabel, label, MAX_LINE_LENGTH);

            /*Checking if the lable is a macro name*/
            if (searchKey(macroList, label) != NULL)
            {
                fprintf(stderr, "Error:%s:%d: Lable is a macro name.\n", inputFileName, lineNum);
                error = true;
            }

            /*Checking if there is a macro call after the lable*/
            strncpy(tempMacAfterLable, trimmedLine + i + 1, strlen(trimmedLine) - i + 1);

            /*Removing white spaces from possible macro name*/
            trimWhitespace(tempMacAfterLable, checkMacAfterLable, MAX_LINE_LENGTH);
            if (checkMacAfterLable == NULL) 
            {
                fprintf(stderr, "Memory allocation failed while expanding macros\n");
                safeExit(1);
            }

            macroNode = searchKey(macroList, checkMacAfterLable);

            /*If there is a macro call - print the lable and the the macro's commands*/
            if (macroNode != NULL)
            {
                /*Prints the lable*/
                fprintf(outputFile, "%.*s", i+1, trimmedLine);

                /*Prints the macro's commands*/
                macro = (ptrMacro)macroNode->ptrVal;
                currentCommand = macro->commandList;

                /*For each command in the macro, we'll print it to the output file*/
                while (currentCommand != NULL)
                {
                    cmd = (ptrCommand)currentCommand->ptrVal;
                    fprintf(outputFile, "%s\n", cmd->comLine);
                    currentCommand = currentCommand->next;
                }

                macroNode = NULL; 
                lineNum++;
                continue;
            }          
        }


        /*Searching for the current line in the macros' list, to see if it is a macro name*/
        macroNode = searchKey(macroList, trimmedLine);

        /*If the current line is a macro name - replace it with the macro's content*/
        if (macroNode != NULL) 
        {

            macro = (ptrMacro)macroNode->ptrVal;
            currentCommand = macro->commandList;

            /*For each command in the macro, we'll print it to the output file*/
            while (currentCommand != NULL)
            {
                cmd = (ptrCommand)currentCommand->ptrVal;
                fprintf(outputFile, "%s\n", cmd->comLine);
                currentCommand = currentCommand->next;
            }
            
        } 
        else 
        {
            /*The current line is not a macro name, we'll write it to the output file as is*/
            fprintf(outputFile, "%s\n", line);
        }

        lineNum++;
    }

    /*Success*/
    return error? false : true;
}



/*Function for managing the pre assembler*/
int preprocessFile(const char* inputFileName, const char* outputFileName, ptrNode* macroList) 
{
    /*Variable for a temporary file, that will store the file between taking care of definitions and expanding*/
    char intermediateFileName[] = "intermediate_file.tmp";
    FILE *inputFile, *intermediateFile, *outputFile;

    /*Flags*/
    int errorOccurred = false;
    int macDefSuccess;
    
    /* Open input file */
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) 
    {
        fprintf(stderr, "Error opening input file: %s\n", inputFileName);
        return false;
    }

    /*Update the global pointers*/
    INPUT_FILE = inputFile;

    /* Open intermediate file */
    intermediateFile = fopen(intermediateFileName, "w");
    if (intermediateFile == NULL) 
    {
        fprintf(stderr, "Error opening intermediate file for pre-assembling file %s\n", inputFileName);
        safeExit(1);
    }

    /*Update the global pointer*/
    INTERMEDIATE_FILE = intermediateFile;

    /* Level 1: finding and deleting the macros' definitions*/
    macDefSuccess = processMacroDefinitions(inputFile, intermediateFile, macroList, inputFileName);
    fflush(intermediateFile);

    /*If there is an error while finding macro definitions*/
    if(!macDefSuccess) 
    {
        fclose(intermediateFile);
        INTERMEDIATE_FILE = NULL;
        remove(intermediateFileName);
        return false;
    }

    fclose(intermediateFile);
    INTERMEDIATE_FILE = NULL;

    /* Open intermediate file for reading and output file for writing */
    intermediateFile = fopen(intermediateFileName, "r");
    outputFile = fopen(outputFileName, "w");
    if (intermediateFile == NULL || outputFile == NULL) 
    {
        fprintf(stderr, "Error opening files for macro expansion while pre-assembling file %s\n", inputFileName);
        fclose(intermediateFile);

        /*Update the global pointer*/
        INTERMEDIATE_FILE = NULL;

        remove(intermediateFileName);

        if (outputFile == NULL) 
        {
            INTERMEDIATE_FILE = intermediateFile;
            safeExit(1);
        }
        
        errorOccurred = true;
    }

    /*Update the global pointers*/
    AM_FILE = outputFile;
    INTERMEDIATE_FILE = intermediateFile;

    /* Level 2: macro retirement*/
    if (!expandMacros(intermediateFile, outputFile, *macroList, inputFileName)) 
    {
        errorOccurred = true;
    }

    fflush(outputFile);

    /* removing and closing the extra file */
    fclose(intermediateFile);
    INTERMEDIATE_FILE = NULL;

    remove(intermediateFileName);

    /*Returning 1 for success, 0 if errors were found*/
    return errorOccurred? false : true;  
}

