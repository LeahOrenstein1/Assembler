#include "utilsError.h"

/* Checks if there are two operands which are not seperated with a comma, returns true if there are */
int hasAdjacentItemsWithoutComma(char* str) 
{
    /*Declaring variables*/
    int i;
    int len = strlen(str);
    int foundNonSpace = 0;

    /* Skip leading spaces */
    while (isspace((unsigned char)*str)) str++;

    for (i = 0; i < len; i++) 
    {
        if (isspace((unsigned char)str[i])) 
        {
            if (foundNonSpace && i > 0 && str[i-1] != ',') 
            {
                return true;  /* Found a space not preceded by a comma */
            }
        }
        else 
        {
            foundNonSpace = true;
        }
    }

    return false;  /* All spaces (except leading) are preceded by commas */
}


/*Checks if the operands are integers, returns true if valid*/
int operandsAreIntegers(char* line)
{
    /*Declaring variables*/    
    char operand[MAX_LINE_LENGTH] = {0}; /*The operand must not be longer than the line's length*/
    int operandStart, i;
    boolean inOperand = false;

    /*For each char*/
    for (i = 0; line[i] != '\0'; i++) 
    {
        /*If the char is not a space or a comma*/
        if (!isspace((unsigned char)line[i]) && line[i] != ',') 
        {
            /*If we are not in an operand*/
            if (!inOperand) 
            {
                inOperand = true;
                operandStart = i;
            }
        }
        else
        {
            /*If we are in an operand*/
            if (inOperand) 
            {
                inOperand = false;
                /*Copy the operand to the token*/
                strncpy(operand, line + operandStart, i - operandStart);
                operand[i - operandStart] = '\0';

                /*Check if the operand is valid*/
                if (!isValidInteger(operand)) 
                {
                    return false;
                }
            }
            inOperand = false;
        }
    }

    /*Checks the last operand*/
    if (inOperand) 
    {
        strncpy(operand, line + operandStart, i - operandStart);
        operand[i - operandStart] = '\0';
        if (!isValidInteger(operand)) 
        {
            return false;
        }
    }

    /*Valid*/
    return true;
}


/*Checks if the operands are in range, returns true if there is any error in it*/
int operandsAreInRange(char* line)
{
    /*Declaring variables*/
    char operand[MAX_LINE_LENGTH] = {0}; /*The operand must not be longer than the line's length*/
    int operandStart, i;
    boolean inOperand = false;

    /*For each char*/
    for (i = 0; line[i] != '\0'; i++) 
    {
        /*If the char is not a space or a comma*/
        if (!isspace((unsigned char)line[i]) && line[i] != ',') 
        {
            /*If we are not in an operand*/
            if (!inOperand) 
            {
                inOperand = true;
                operandStart = i;
            }
        }
        else
        {
            /*If we are in an operand*/
            if (inOperand) 
            {
                inOperand = false;
                /*Copy the operand to the token*/
                strncpy(operand, line + operandStart, i - operandStart);
                operand[i - operandStart] = '\0';

                /*Check if the operand is in range*/
                if (!isNumberInRange(operand)) 
                {
                    return false;
                }
            }
            inOperand = false;
        }
    }
    /*Checks the last operand*/
    if (inOperand) 
    {
        strncpy(operand, line + operandStart, i - operandStart);
        operand[i - operandStart] = '\0';
        if (!isNumberInRange(operand)) 
        {
            return false;
        }
    }

    /*Valid*/
    return true;
}


/*Checks if the string represents a integer. returns true if it is, else otherwise*/
int isValidInteger(char* str)
{
    /*If it begins with a sign - skip it*/
    if (*str == '+' || *str == '-') str++;

    /*If the string is empty*/
    if (*str == '\0' || *str == EOF) return false;

    /*For each charecter, checkes if it is a digit*/
    while (*str != '\0' && *str != EOF)
    {
        if (!isdigit(*str))
            return false; 
        str++;   
    }
    
    return true;
}


/*Checks if a string is a number in range*/
int isNumberInRange(char* str)
{
    /*Declaring variables*/
    int num;

    /*Convert the string to a number*/
    if (sscanf(str, "%d", &num) == 0) 
    {
        return false;
    }

    /*Check if the number is in range*/
    return num >= MIN_INTEGER_VALUE && num <= MAX_INTEGER_VALUE;
}


/*Function for checking a validation of a string format, returns true if the string is formed like this: ".*" (regex)*/
int isValidQuotedString(char* str) 
{
    size_t len = strlen(str);
    size_t i;

    /* Check if string is too short to be a valid quoted string */
    if (len < 2) 
    {
        return false;
    }

    /* Check if string starts and ends with quotes */
    if (str[0] != '"' || str[len-1] != '"') 
    {
        return false;
    }

    /* Check all characters between quotes */
    for (i = 1; i < len - 1; i++) 
    {
        /* All ASCII values from 0 to 127 are valid */
        if (!isprint((unsigned char)str[i])) 
        {
            return false;
        }
    }

    return true;
}


/*Returns the type of a code instruction */
codeType checkCodeType(char* line)
{
    /*Declaring variables*/
    codeType i = 0;
    const char* codeInstructions[] = CODE_INSTRUCTIONS_NAMES;

    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(line, line, MAX_LINE_LENGTH);

    /*If the line contains a valid code instriction - return 1*/
    for (i = 0; i < NUM_OF_CODE_INSTRUCTIONS; i++)
    {
        if (strncmp(line, codeInstructions[i], strlen(codeInstructions[i])) == 0)
        {
            return i;
        }
    }

    return ERROR_CODE;
}


/*Returns the adressing mode of the firs operand in the line*/
adressingMode checkAdressingMode(char* line)
{
    /*Declaring variables*/
    char tempLine[MAX_LINE_LENGTH] = {0};

    /*Normalizing the form of the line*/
    trimAndFormatString(line, tempLine);
    line = tempLine;

    if (isImmediate(line))
    {
        return IMMIDIATE;
    }

    if (isInDirectRegister(line))
    {
        return INDIRECT_REGISTER;
    }

    if (isDirectRegister(line))
    {
        return DIRECT_REGISTER;
    }

    if (isDirect(line))
    {
        return DIRECT;
    }

    return ADRRESING_ERROR;
}


/*Checks if there are multiple commas in well formed string, returns true if found*/
int multipleCommas(char* line)
{
    int i = 0;
    int len = strlen(line);

    for (i = 0; i < len - 2; i++)
    {
        if (line[i] == ',' && line[i + 2] == ',')
        {
            return true;
        }
    }

    return false;
}


/*Returns true if the firs operand in the string is a valid register*/
int isRegister(char* str)
{
    int i;
    int index = 0;
    char* registers[] = REGISTER_NAMES;

    /*If the potential register name is too short or too long*/
    if (strlen(str) < 2) return false;
    while (str[index] != ' ' && str[index] != ',' && str[index] != '\0' && str[index] != '\n' && str[index] != EOF) index++;
    if (index > 3) return false;

    /*If the string is a register*/
    for (i = 0; i < NUM_OF_REGISTERS; i++)
    {
        if (strncmp(str, registers[i], strlen(registers[i])) == 0)
        {
            return true;
        }
    }

    /*Not a valid register*/
    return false;
}


/*Returns true if the line's operands are valid adressing mode for the specific command type*/
int validAdressingModes(char* line, codeType type)
{
    /*Declaring variables*/
    adressingMode mode;
    optType opt;

    /*Needed const arrays*/
    int srcOptions[] = SRC_OPTIONS_FOR_INSTRUCTION;
    int dstOptions[] = DEST_OPTIONS_FOR_INSTRUCTION;
    int numOfOperandsForCom[] = NUM_OF_OPERANDS_REQUIRED;
    const int optionsInOpt[][5] = OPTIONS_FOR_ADRESSING;
    int numOfOptions[] = NUM_OF_DRESSING_OPTIONS;
    char tempLine[MAX_LINE_LENGTH] = {0};
    char* operand, *endOfOperand;
    int i;

    /*Flag*/
    boolean valid = false;

    /*Normalizing the form of the line*/
    trimAndFormatString(line, tempLine);
    line = tempLine;

    /*Getting the first operand*/
    operand = getOperand(line, &endOfOperand);
    if (*endOfOperand == ',') endOfOperand++;

    /*Checking the adressing mode of the operand*/
    mode = checkAdressingMode(operand);

    /*If the adressing mode is not valid*/
    if (mode == ADRRESING_ERROR)
    {
        return false;
    }

    /*If the function should have both, dst and src operands*/
    if (numOfOperandsForCom[type] == 2)
    {
        /*Checks src operand*/
        opt = srcOptions[type];

        /*Checks if the adressing mode is valid for the src operand in the specific command*/
        for (i = 0; i < numOfOptions[opt]; i++)
        {
            if (optionsInOpt[opt][i] == mode)
            {
                valid = true;
                break;
            }
        }

        /*Invalid adressing mode for src operand*/
        if (!valid)
        {
            return false;
        }

        valid = false;

        /*Checks dst operand*/
        operand = getOperand(endOfOperand, &endOfOperand);
        mode = checkAdressingMode(operand);
        opt = dstOptions[type];

        /*Checks if the adressing mode is valid for the dst operand in the specific command*/
        for (i = 0; i < numOfOptions[opt]; i++)
        {
            if (optionsInOpt[opt][i] == mode)
            {
                return true;
            }
        }

        /*Valid adressing modes of operands src and dst */
        return false;
    }  

    /*If the command should have only dst operand*/
    else if (numOfOperandsForCom[type] == 1)
    {
        opt = dstOptions[type];

        /*Checks if the adressing mode is valid for the dst operand in the specific command*/
        for (i = 0; i < numOfOptions[opt]; i++)
        {
            if (optionsInOpt[opt][i] == mode)
            {
                return true;
            }
        }
    }

    /*Else - It is a non operands command, or the dst operand is invalid*/
    return false;
}


/*Checks if a label is valid as operand*/
int errorInLabelAsOperand(char* line)
{
    /*Declaring variables*/
    char tempLine[MAX_LINE_LENGTH] = {0};
    char* operand, *endOfOperand;

    /*Normalizing the form of the line*/
    trimAndFormatString(line, tempLine);
    line = tempLine;

    /*Getting the first operand*/
    operand = getOperand(line, &endOfOperand);

    /*If the label begins with a non letter char*/
    if (!isalpha(*operand))
    {
        return true;
    }

    /*If the operand is a valid label*/
    if (!isAlphanumeric(operand))
    {
        return true;
    }

    /*If the label is too long*/
    if (strlen(operand) > MAX_LABEL_LENGTH)
    {
        return true;
    }

    /*Else - the operand is not a valid label*/
    return false;
}


int isValidOperand(char* operand, char* inputFileName, int lineNumber)
{
    char tempOperand[MAX_LABEL_LENGTH + 1] = {0};
    strncpy(tempOperand, operand, MAX_LABEL_LENGTH);
    tempOperand[MAX_LABEL_LENGTH] = '\0';
    operand = tempOperand;

    /*If the operand is empty*/
    if (strlen(operand) == 0)
    {
        fprintf(stderr, "Error:%s:%d: Empty operand.\n", inputFileName, lineNumber);
        return false;
    }

    /*If the operand is a register (In an indirect adressing mode, otherwise it would be a label) out of registers' range*/
    if (isRegisterOutOfRange(operand + 1) && operand[0] == '*')
    {
        fprintf(stderr, "Error:%s:%d: Register out of range. Valid range: [r0 - r7].\n", inputFileName, lineNumber);
        return false;
    }

    /*If the operand is a valid register - return true*/
    else if (isRegister(operand + 1) && operand[0] == '*') return true;
    
    /*If the operand is an immidiate out of 12 bit range*/
    if (isImmediateOutOfRange(operand + 1) && operand[0] == '#')
    {
        fprintf(stderr, "Error:%s:%d: Immediate value out of range. Valid range: [%d, %d].\n", inputFileName, lineNumber, MIN_IMMIDIATE_VALUE, MAX_IMMIDIATE_VALUE);
        return false;
    }

    /*If the operand is an immidiate in range - return true*/
    else if (!isImmediateOutOfRange(operand + 1) && *operand == '#' && isValidInteger(operand + 1)) return true;
    
    /*If the operand is a invalid label*/
    if (errorInLabelAsOperand(operand))
    {
        fprintf(stderr, "Error:%s:%d: Invalid label or unidentified operand.\n", inputFileName, lineNumber);
        return false;
    }

    /*No errors, valid*/
    return true;
}

/*Checks if a string represents an out-of-range register*/
int isRegisterOutOfRange(char* str)
{
    if (*str == '\0' || *str != 'r') return false;
    str++;
    if (*str == '+' || *str == '-') return false;
    if (!isValidInteger(str)) return false;

    /*The string begins with 'r' and continues with a number. Checks if it is an in-range number*/
    return atoi(str) < MIN_REGISTER_VALUE || atoi(str) > MAX_REGISTER_VALUE;
}

/*Checks if a string represents an out-of-range immidiate*/
int isImmediateOutOfRange(char* str)
{
    if (!isValidInteger(str)) return false;
    return atoi(str) < MIN_IMMIDIATE_VALUE || atoi(str) > MAX_IMMIDIATE_VALUE;
}