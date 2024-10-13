#include "utilsPass.h"

/*Function to check if the line contains a valid data instruction name*/
int isDataLine(char* line)
{
    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(line, line, MAX_LINE_LENGTH);

    /*If the line contains a valid data instriction - return 1*/
    if (strncmp(line, ".data", 5) == 0 || strncmp(line, ".string", 7) == 0)
    {
        if (!(line[5] == ' ' || line[5] == '\0') && !(line[7] == ' ' || line[7] == '\0')) return 0;
        return 1;
    }

    return 0;
}


/*Function to check if the line contains a valid code instruction name*/
int isCodeLine(char* line)
{
    /*Declaring variables*/
    int i = 0;
    const char* codeInstructions[] = CODE_INSTRUCTIONS_NAMES;

    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(line, line, MAX_LINE_LENGTH);

    /*If the line contains a valid code instriction - return 1*/
    for (i = 0; i < 16; i++)
    {
        if (strncmp(line, codeInstructions[i], strlen(codeInstructions[i])) == 0)
        {
            if (!(line[strlen(codeInstructions[i])] == ' ' || line[strlen(codeInstructions[i])] == '\0')) return 0;
            return 1;
        }
    }

    return 0;
}


int isExternLine(char* line)
{
    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(line, line, MAX_LINE_LENGTH);

    /*If the line contains a valid code instriction - return 1*/
    if (strncmp(line, ".extern", 7) == 0)
    {
        if (!(line[7] == ' ' || line[7] == '\0')) return 0;
        return 1;
    }

    return 0;
}


int isEntryLine(char* line)
{
    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(line, line, MAX_LINE_LENGTH);

    /*If the line contains a valid code instriction - return 1*/
    if (strncmp(line, ".entry", 6) == 0)
    {
        if (!(line[6] == ' ' || line[6] == '\0')) return 0;
        return 1;
    }

    return 0;
}


int isAlphanumeric(const char *str) 
{
    while (*str) 
    {
        if (!isalnum((unsigned char)*str)) 
        {
            return 0;  /*We found a non-alphanumeric charecters*/
        }
        str++;
    }
    return 1;  /*All charecters are alphanumeric*/
}

int numOfOperands(char* line)
{
    int counter = 0;
    char* operand, *endOfOperand;

    while (1)
    {
        operand = getOperand(line, &endOfOperand);
        if (*operand == '\0') break;
        counter++;
        line = endOfOperand + 2;
    }
    
    return counter;
}


/*Returns a pointer to the first non space char' and updates the endOfOperans pointer to the first comma or space*/
char* getOperand(char* line, char** endOfOperand)
{
    while (isspace((unsigned char)*line)) line++;

    *endOfOperand = line;

    while (**endOfOperand != '\0' && !isspace((unsigned char)**endOfOperand) && **endOfOperand != ',') (*endOfOperand)++;
    
    return line;
}


/*Returns the type of an extern entry command*/
externEntryType retExEnType(const char* line)
{
    if (strncmp(line, ".extern", 7) == 0)
    {
        return EXTERN;
    }
    else if (strncmp(line, ".entry", 6) == 0)
    {
        return ENTRY;
    }

    return ERROR_EXTERN_ENTRY;
}


/*Returns true if the first operand in the string is a valid immidiate*/
int isImmediate(char* str)
{
    char* index = str;
    char temp[MAX_LINE_LENGTH] = {0};

    /*Look for the first space or comma*/
    while (*index != ' ' && *index != ',' && *index != '\0' && *index != '\n' && *index != EOF) index++;
    
    /*If the string is a immidiate*/
    if (*str == '#')
    {
        str++;
    }
    else
    {
        return false;
    }

    strncpy(temp, str, index - str);
    temp[index - str] = '\0';

    /*Is a valid integer*/
    return isValidInteger(temp);
}


/*Returns true if the first operand in the string is a valid direct*/
int isDirect(char* str)
{
    char* index = str;
    char temp[MAX_LINE_LENGTH] = {0};

    /*Normalizing the strings format*/
    trimAndFormatString(str, temp);
    str = temp;

    str = getOperand(str, &index);
    str[index - str] = '\0';

    /*Is a valid integer*/
    return !errorInLabelAsOperand(str);
}

/*Returns true if the first operand in the string is a valid direct register*/
int isDirectRegister(char* str)
{
    return isRegister(str); 
}

/*Returns true if the first operand in the string is an indirect register*/
int isInDirectRegister(char* str)
{
    /*Checks if the string is empty*/
    if (*str =='\0') return false;

    /*Returns if the first operand in the string is an indirect register*/
    return isRegister(str + 1) && *str == '*';
}

/*Returns the data instruction type, string or data*/
dataType retDataType(char *line)
{
    return strncmp(line, ".data", 5) == 0? DATA : (strncmp(line, ".string", 7) == 0? STRING :  ERROR_DATA);
}

/*Returns the type of the code instruction*/
codeType retCodeType(char* line)
{
    codeType i;
    const char* codeInstructions[] = CODE_INSTRUCTIONS_NAMES;
    line = skipWhitespace(line);   /*Skip the white spaces in the begining of the line*/

    /*Compares the command name to the valid command names and returns the type found*/
    for (i = 0; i < NUM_OF_CODE_INSTRUCTIONS; i++)
    {
        if (strncmp(line, codeInstructions[i], strlen(codeInstructions[i])) == 0)
        {
            return i;
        }
    }

    return ERROR_CODE;   /*Not a valid command name*/
}

/*Gets a number which can be presented as a 15 bit binary number and converts it to its binary form in string*/
void intToBinaryString(int num, char* result, int length) 
{
    int i;
    unsigned int mask;
    
    /* Validate length */
    if (length <= 0 || length > 32) 
    {
        result[0] = '\0';
        return;
    }
    
    /* Set mask for the leftmost bit */
    mask = 1u << (length - 1);
    
    /* Convert to binary string */
    for (i = 0; i < length; i++) 
    {
        result[i] = (num & mask) ? '1' : '0';
        mask >>= 1;
    }

    /* Add null terminator */
    result[length] = '\0';
}


/*Returns the opCode of the code instruction*/
char* getOpCode(codeType codeType)
{
    char* opcodes[] = OPCODE_BINARY;
    return opcodes[codeType];
}