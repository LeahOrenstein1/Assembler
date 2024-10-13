#include "firstPass.h"

/* Function for managing the first pass */
int firstPass(char* inputFileName, ptrNode* memoryImage, ptrNode* symbolListPtr, ptrNode* symAppearMem, ptrNode* entryList, int* IC, int* DC)
{
    /*Declaring variables*/

    /*Counters*/
    int lineNumber = 0;

    /*Flags*/
    int error = false;
    int isErrorInLine = false;

    char line[MAX_LINE_LENGTH];

    /*Lists*/
    ptrNode dataImage = NULL;
    ptrNode codeImage = NULL;

    /* Opening the am file*/
    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", inputFileName);
        return false;
    }

    /*Update the global pointers*/
    AM_FILE = inputFile;
    CODE_IMAGE_PTR = &codeImage;
    DATA_IMAGE_PTR = &dataImage;

    /*Reading the file line by line and processing it*/
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL)
    {
        lineNumber++;
        isErrorInLine = processLine(inputFileName, line, symbolListPtr, entryList, &codeImage, &dataImage, symAppearMem, IC, DC, lineNumber);
        /*If an error found in the line*/
        if (!isErrorInLine)
        {
            error = true;
        }
    }

    /*Create the final lists*/
    appendNode(&codeImage, dataImage);

    *memoryImage = codeImage;

    CODE_IMAGE_PTR = NULL;
    DATA_IMAGE_PTR = NULL;

    return error? false : true;

}


int processLine(char* inputFileName, char* line, ptrNode* symbolListPtr, ptrNode* entryList, ptrNode* codeImage, ptrNode* dataImage, ptrNode* symAppearMem, int* IC, int* DC, int lineNumber)
{
    /*Declaring variables*/
    char labelName[MAX_LABEL_LENGTH] = {0};
    char labelNameTemp[MAX_LINE_LENGTH] = {0};
    char tempLine[MAX_LINE_LENGTH] = {0};
    int error = false;
    int labelFound = false;
    int L = 0;
    int i = 0;

    /*No notes line, we'v skipped them in the pre-assembler*/

    /* Clearing the line from extra white spaces in the end and begining, using the temporary line */
    trimWhitespace(line, tempLine, MAX_LINE_LENGTH); 
    line = tempLine;



    /*If the line is a note line - error, the ; was not the first charecter (wasn't recognized by the pre-assemble)*/
    if (line[0] == ';')
    {
        fprintf(stderr, "Error: Illegal note in the middle of the line. file %s, line %d\n", inputFileName, lineNumber);
        return false;
    }

    /*Look for a label declaration*/
    while (i < strlen(line) && line[i] != ':')  i++; 
    
    if (line[i] == ':')
    {
        /*Label found, updates the labels flag and checks if valid and if so adding it to the symbols table*/
        labelFound = true;

        /*Checking if the label name is valid*/

        /*Clearing only the begining of the label name from white spaces*/
        sprintf(labelNameTemp,"%.*s\0", i + 1, line);
        trimWhitespace(labelNameTemp, labelNameTemp, MAX_LINE_LENGTH);
        sprintf(labelNameTemp,"%.*s\0", strlen(labelNameTemp) - 1, labelNameTemp);

        /*If there is no white space after the label*/
        if (line[i + 1] != ' ' && line[i + 1] != '\t')
        {
            /*Error - invalid label name*/
            fprintf(stderr, "Error: Missing white space after label. File %s, line %d\n", inputFileName, lineNumber);
            error = true;
        }

        if (errorInLabel(labelNameTemp , inputFileName, lineNumber, *symbolListPtr))
        {
            /*Error - invalid label name*/
            error = true;
        }
        else
        {
            /*Copying the label name to a new string*/
            sprintf(labelName, "%.*s\0", i, line);
        }

        /*Checking if the command after the label is valid*/

        /*If it is a data instruction*/
        if (isDataLine(line + i + 1))
        {
            /*Adding the label to the symbols table*/
            appendNode(symbolListPtr, createNode(labelName ,createSymbol(*DC, SYMBOL_TYPE_DATA, lineNumber)));
        }

        /*If it is a code instruction*/
        else if (isCodeLine(line + i + 1))
        {   
            /*Adding the label to the symbols table*/
            appendNode(symbolListPtr, createNode(labelName ,createSymbol(*IC, SYMBOL_TYPE_CODE, lineNumber)));
        }            

        /*If there is nothing after the label*/
        else if (i + 1 == strlen(line))
        {
            /*Label without a command after it*/
            fprintf(stderr, "Error: Label without a command after it in line %d file %s\n", lineNumber, inputFileName);
            error = true;
        }
            
        else
        {
            if (!isExternLine(line + i + 1) || isEntryLine(line + i + 1)) /*If before extern or entry command - don't add to the symbol table*/
            {
                /*Error - invalid command after the label*/
                appendNode(symbolListPtr, createNode(labelName ,createSymbol(*IC, SYMBOL_TYPE_CODE, lineNumber)));
                fprintf(stderr, "Error: Invalid command after the label in line %d file %s\n", lineNumber, inputFileName);
                return false;
            }
        }
        i++;
    }

    if (error)
    {
        return false;
    }

    /*If there is no label in the line*/
    if (!labelFound)
        i = 0;
    
    line += i;
    line = skipWhitespace(line);

    if (isDataLine(line))
    {
        /*If it is a valid data instruction*/
        if (!errorInData(line, inputFileName, lineNumber))
        {
            /*Processing the data instruction and adding it to the memory*/
            processDataInstruction(line, dataImage, &L);
            *DC += L;  /*Updating the DC*/
        }
        else
        {
            error = true;
        }
    }

    else if (isCodeLine(line))
    {
        /*If it is a valid code instruction*/
        if (!errorInCode(line, inputFileName, lineNumber))
        {
            /*Processing the code instruction and adding it to the memory*/
            processCodeInstruction(line, codeImage, *symbolListPtr, symAppearMem, &L, *IC, lineNumber);

            /*Updating the IC*/
            *IC += L;
            L = 0;
        }
        else
        {
            error = true;
        }
    }

    else if (isExternLine(line))
    {
        /*If it is a valid extern instruction*/
        if (!errorInExEn(line, inputFileName, lineNumber))
        {
            if(!processExternInstruction(line, symbolListPtr, lineNumber, inputFileName))   error = true;  /*Process the extern line*/
        }   
        else
        {
            error = true;
        }
    }

    else if (isEntryLine(line))
    {
        /*If it is a valid entry instruction*/
        if (!errorInExEn(line, inputFileName, lineNumber))
        {
            if(!processEntryInstruction(line, entryList, lineNumber))   error = true;  /*Process the entry line*/
        }
        else
        {
            error = true;
        }
    }

    /*If it is not a code, data, extern or entry command*/
    else
    {
        /*Error - invalid instruction*/
        fprintf(stderr, "Error: Instruction is not valid in line %d file %s\n", lineNumber, inputFileName);
        error = true;
    }

    return error? false : true;
}

