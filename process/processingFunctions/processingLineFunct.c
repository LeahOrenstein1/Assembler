#include "processingLineFunct.h"

/*Function for processing the data line !after validation verification!*/
int processDataInstruction(char* line, ptrNode *dataImage, int* L)
{
    /*Declaring variables*/
    char* operand, *endOfOperand;
    char tempOperand[MAX_LINE_LENGTH] = {0};
    char tempLine1[MAX_LINE_LENGTH] = {0};
    char tempLine2[MAX_LINE_LENGTH] = {0};
    int numOp;
    int i = 0;
    dataType type;
    char memValue[MEMORY_WORD_LENGTH] = {0};

    /*Getting the data type*/
    type = retDataType(skipWhitespace(line));

    switch (type)
    {
    case ERROR_DATA:
        return 0;
    
    case DATA:
        /*Normalizing the form of the data line*/
        trimAndFormatString(line, tempLine1);
        line = tempLine1;

        line += DATA_LENGTH;

        operand = getOperand(line, &endOfOperand);
        numOp = numOfOperands(line);
        *L = numOp;  /*Update the num of operands variables*/

        /*Adding each operand to the memory*/
        for (i = 0; i < numOp; i++)
        {
            strncpy(tempOperand, operand, endOfOperand - operand); tempOperand[endOfOperand - operand] = '\0';
            
            intToBinaryString(atoi(tempOperand), memValue, MEMORY_WORD_LENGTH);
            appendNode(dataImage, createNode(memValue, NULL));  /*Adding it to the data image*/
            operand = getOperand(endOfOperand + 2, &endOfOperand); /*Getting the next operand (skipping the ", " string which is there becouse of the manipulitions we've made)*/
        }
        break;

    case STRING:

        /*Trimming white spaces*/
        trimWhitespace(line, tempLine2, MAX_LINE_LENGTH);
        line = tempLine2;

        line += STRING_LENGTH + 1;
        operand = getOperand(line, &endOfOperand);

        /*Adding each chrecter to the memory by its ascii code*/
        for ( i = 1; i < strlen(line); i++)
        {   
            if (line[i] == '"' && line[i+1] == '\0') break;  /*If we reached the end of the string*/
            intToBinaryString((int)line[i], memValue, MEMORY_WORD_LENGTH);
            appendNode(dataImage, createNode(memValue, NULL));  /*Adding it to the data image*/
        }

        *L = i;  /*Updating L*/

        /*Adding '\0' to the memory*/
        intToBinaryString((int)'\0', memValue, MEMORY_WORD_LENGTH);
        appendNode(dataImage, createNode(memValue, NULL));  /*Adding it to the data image*/
        break;
    
    default:
        break;
    }

    /*Success*/
    return 1;
}

/*Function for processing a code instruction, !after it found valid!*/
int processCodeInstruction(char* line, ptrNode *codeImage, ptrNode symbolList, ptrNode* symbolMemApearance, int* L, int IC, int lineNumber)
{
    /*Declaring variables*/
    char* operand, *endOfOperand;
    char tempLine[MAX_LINE_LENGTH] = {0};
    char tempSrcOperand[MAX_LINE_LENGTH] = {0};
    char tempDstOperand[MAX_LINE_LENGTH] = {0};
    boolean twoRegisters = false;
    ptrSymbolAppearance symAppearMem;

    /*Macros for handlling with opCode*/
    const char* codeInstructions [] = CODE_INSTRUCTIONS_NAMES;

    /*Macros for handling with adressing modes*/
    const char* binaryAdressingMode [] = ADRESSING_MODES_BINARY;
    
    int numOp;
    codeType type = retCodeType(line);
    adressingMode adModeSrc, adModeDst;

    /*Strings for the 3 memory words (Not must to be used)*/
    char memValues[3][MEMORY_WORD_LENGTH + 1] = {{0}};

    /*Normalizing the for of the line */
    trimAndFormatString(line, tempLine);
    line = tempLine;

    line += strlen(codeInstructions[type]);   /*Skipping the command name*/
    line = skipWhitespace(line);   /*Skipping the white spaces*/

    strncpy(memValues[0], getOpCode(type), OPCODE_LENGTH);   /*Processing opCode*/

    /*Processing the adressing mode according to the num of operands for the specific instruction*/
    numOp = numOfOperands(line);

    switch (numOp)
    {
    case 2:
        /*Processing the first operand*/
        operand = getOperand(line, &endOfOperand);
        strncpy(tempSrcOperand, operand, endOfOperand - operand); 
        tempSrcOperand[endOfOperand - operand] = '\0';

        adModeSrc = checkAdressingMode(tempSrcOperand);

        /*Getting the dst operand's adressing mode for updating the "twoRegisters" falg*/
        operand = getOperand(endOfOperand + 2, &endOfOperand);
        strncpy(tempDstOperand, operand, endOfOperand - operand);
        tempDstOperand[endOfOperand - operand] = '\0';

        adModeDst = checkAdressingMode(tempDstOperand);

        /*Setting the source and destination adressing mode*/
        strncpy(memValues[0] + FIRST_SRC_ADRESSING_INDEX, binaryAdressingMode[adModeSrc], 4);  
        strncpy(memValues[0] + FIRST_DST_ADRESSING_INDEX, binaryAdressingMode[adModeDst], 4);  

        strncpy(memValues[0] + ARE_FIRST_INDEX, A_BINARY, ARE_LENGTH);  /*Setting the A bit*/

        twoRegisters = (adModeDst == DIRECT_REGISTER || adModeDst == INDIRECT_REGISTER) && (adModeSrc == DIRECT_REGISTER || adModeSrc == INDIRECT_REGISTER);

        if (processSrcMemWord(tempSrcOperand, tempDstOperand, memValues[1], adModeSrc, adModeDst, symbolList, twoRegisters) == false) return 0;   /*Processing the source memory word*/

        if (twoRegisters)
        {
            /*Updating L*/
            *L = 2;

            /*Adding the first and seccond memory word to the code image*/
            appendNode(codeImage, createNode(memValues[0], NULL));
            appendNode(codeImage, createNode(memValues[1], NULL));

            /*Success*/
            return 1;
        }

        /*Processing the second operand*/
        if (processDstMemWord(tempDstOperand, memValues[2], adModeDst) == false) return 0;   /*Processing the destination memory word*/
        
        /*Adding the memory words to the memory image*/
        appendNode(codeImage, createNode(memValues[0], NULL));
        if (adModeSrc == DIRECT) 
        {
            symAppearMem = createSymbolAppearance(IC + 1, lineNumber);

            /*Adding the symbol to the symbol memory apearance list and the uncomleted memory word*/
            appendNode(symbolMemApearance, createNode(tempSrcOperand, symAppearMem));
        }
        
        appendNode(codeImage, createNode(memValues[1], NULL)); /*Add the memory word ro the code images*/
        

        if (adModeDst == DIRECT) 
        {
            symAppearMem = createSymbolAppearance(IC + 2, lineNumber);
            /*Adding the symbol to the symbol memory apearance list and the uncomleted memory word*/
            appendNode(symbolMemApearance, createNode(tempDstOperand, symAppearMem));
        }

        appendNode(codeImage, createNode(memValues[2], NULL)); /*Add the memory word ro the code images*/
        
        /*Updating L*/
        *L = 3;

        /*Success*/
        return 1;

    case 1:
        /*Processing the dst operand*/
        operand = getOperand(line, &endOfOperand);
        strncpy(tempDstOperand, operand, endOfOperand - operand);
        tempDstOperand[endOfOperand - operand] = '\0';

        adModeDst = checkAdressingMode(tempDstOperand);

        /*Setting the adressing modes*/
        strncpy(memValues[0] + FIRST_DST_ADRESSING_INDEX, binaryAdressingMode[adModeDst], 4);
        strncpy(memValues[0] + FIRST_SRC_ADRESSING_INDEX, binaryAdressingMode[ADRRESING_ERROR], 4);

        strncpy(memValues[0] + ARE_FIRST_INDEX, A_BINARY, ARE_LENGTH);  /*Setting the A bit*/

        if (processDstMemWord(tempDstOperand, memValues[1], adModeDst) == false) return 0;   /*Processing the destination memory word*/

        /*Adding the memory words to the memory image*/
        appendNode(codeImage, createNode(memValues[0], NULL));
        if (adModeDst == DIRECT) 
        {
            symAppearMem = createSymbolAppearance(IC + 1, lineNumber);

            /*Adding the symbol to the symbol memory apearance list and the uncomleted memory word*/
            appendNode(symbolMemApearance, createNode(tempDstOperand, symAppearMem));
        }

        appendNode(codeImage, createNode(memValues[1], NULL));
        

        /*Updating L*/
        *L = 2;

        /*Success*/
        return 1;
    
    default:

        if (numOp != 0)   return 0; /*Failure*/

        /*Setting the memory word to 0 - except from the opcode and are*/
        intToBinaryString(0, memValues[0] + FIRST_SRC_ADRESSING_INDEX, MEMORY_WORD_LENGTH);   
        strncpy(memValues[0] + ARE_FIRST_INDEX, A_BINARY, 4);  /*Setting the adressing mode to 0*/

        /*Adding the first word to the memory image*/
        appendNode(codeImage, createNode(memValues[0], NULL));

        /*Updating L*/
        *L = 1;

        /*Success*/
        return 1;
    }
}

/*If the line is valid, processing the extern line*/
int processExternInstruction(char* line, ptrNode *symbolList, int lineNumber, char* fileName)
{
    ptrSymbol symbol;
    line += EXTERN_LENGTH + 1;   /*Skipping the ".extern" command and the space after it*/

    /*Check if the external symbol is already defined in the file*/
    if (searchKey(*symbolList, line) != NULL)
    {
        fprintf(stderr, "Error:%s:%d: External symbol %s is also defined in the file.\n", fileName, lineNumber, line);
        return 0;
    }

    symbol = createSymbol(0, SYMBOL_TYPE_EXTERN, lineNumber);

    /*Creating a symbol and adding it to the symbol list*/
    appendNode(symbolList, createNode(line, symbol));
    return 1;
}

/*If the line is valid, processing the entry line*/
int processEntryInstruction(char* line, ptrNode *entryList, int lineNumber) 
{
    ptrSymbol symbol;

    line += ENTRY_LENGTH + 1;   /*Skipping the ".entry" command and the space after it*/

    symbol = createSymbol(0, SYMBOL_TYPE_ENTRY, lineNumber);

    /*Creating a symbol and adding it to the entry list*/
    appendNode(entryList, createNode(line, symbol));

    return 1;
}

/*Gets two operands and processing the src memory word - the second one*/
int processSrcMemWord(char* srcOp, char* dstOp, char srcMem[MEMORY_WORD_LENGTH + 1], adressingMode srcAdMode, adressingMode dstAdMode, ptrNode symbolList, boolean twoRegisters)
{
    int immidiateValue;

    if (twoRegisters)
    {
        intToBinaryString(atoi(srcOp + (srcAdMode == INDIRECT_REGISTER? 2 : 1)), srcMem, 9);   /*Processing the source register + zeros for the beginning*/
        intToBinaryString(atoi(dstOp + (dstAdMode == INDIRECT_REGISTER? 2 : 1)), srcMem + FIRST_DST_REGISTER_INDEX, 3);   /*Processing the destination register*/

        strncpy(srcMem + ARE_FIRST_INDEX, A_BINARY, ARE_LENGTH);  /*Setting the A bit*/

        /*Success*/
        return 1;
    }

    switch (srcAdMode)
    {
    case IMMIDIATE:
        srcOp++;  /*Skipping the '#' character*/

        immidiateValue = atoi(srcOp);
        intToBinaryString(immidiateValue, srcMem, BINARY_OPERAND_LENGTH);   /*Processing the immidiate value*/
            
        strncpy(srcMem + ARE_FIRST_INDEX, A_BINARY, ARE_LENGTH);  /*Setting the A bit*/ 

        /*Success*/
        return 1;
    
    case DIRECT:
        
        strncpy(srcMem, "???????????????", MEMORY_WORD_LENGTH);  /*Leave it for the second pass*/

        /*Success*/
        return 1;  
    
    default:

        if (srcAdMode == ADRRESING_ERROR) return 0;  /*Failure*/

        intToBinaryString(atoi(srcOp + (srcAdMode == INDIRECT_REGISTER? 2 : 1)), srcMem, 9);   /*Processing the source register + zeros for the beginning*/
        strncpy(srcMem + DST_FIRST_INDEX, "000", 3);   /*Setting the destination register to 0*/
        strncpy(srcMem + ARE_FIRST_INDEX, A_BINARY, ARE_LENGTH);  /*Setting the A bit*/
        
        /*Success*/
        return 1;

    }

}

/*Processing the dst memory word*/
int processDstMemWord(char* dstOp, char dstMem[MEMORY_WORD_LENGTH + 1], adressingMode dstAdMode)
{
    int immidiateValue;

    switch (dstAdMode)
    {
    case IMMIDIATE:
        dstOp++;  /*Skipping the '#' character*/

        immidiateValue = atoi(dstOp);
        intToBinaryString(immidiateValue, dstMem, BINARY_OPERAND_LENGTH);   /*Processing the immidiate value*/
            
        strncpy(dstMem + ARE_FIRST_INDEX, A_BINARY, ARE_LENGTH);  /*Setting the A bit*/ 
        
        /*Success*/
        return 1;   
    
    case DIRECT:
        
        strncpy(dstMem, "???????????????", MEMORY_WORD_LENGTH);  /*Leave it for the second pass*/

        /*Success*/
        return 1;  
    
    default:

        if (dstAdMode == ADRRESING_ERROR) return 0;  /*Failure*/

        intToBinaryString(atoi(dstOp + (dstAdMode == INDIRECT_REGISTER? 2 : 1)), dstMem, 12);   /*Processing the destination register*/
        strncpy(dstMem + ARE_FIRST_INDEX, A_BINARY, ARE_LENGTH);  /*Setting the A bit*/
        
        /*Success*/
        return 1;

    }

}
