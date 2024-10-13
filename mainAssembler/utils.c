#include "utils.h"


/* Helper function to trim whitespace and return a new string */
void trimWhitespace(const char* str, char* result, size_t result_size) 
{
    size_t start = 0, end = strlen(str) - 1, i = 0;
    
    while (isspace((unsigned char)str[start])) start++;
    while (end > start && isspace((unsigned char)str[end])) end--;
    
    for (i = 0; start <= end && i < result_size - 1; start++, i++) 
    {
        result[i] = str[start];
    }
    result[i] = '\0';
}


/*Function for initializing the file name vatiables*/
char* AllocateMemFileName(const char* fileName, size_t size)
{
    /*Allocating memory for the variable*/
    char* string = malloc(sizeof(char)* (size + 1));

    if (string == NULL)
    {
        fprintf(stderr, "Error: Can not allocate memory for a file name\n");
        safeExit(1);
    }   

    /*Updating the variable*/  
    strncpy(string, fileName, size);

    string[size] = '\0';

    /*Returning*/
    return string;
}


char* skipWhitespace(char* str) 
{
    if (str == NULL) return NULL;

    while (*str != '\0' && isspace((unsigned char)*str)) 
    {
        str++;
    }

    return str;
}


void trimAndFormatString(const char *input, char output[MAX_LINE_LENGTH]) 
{
    int length = strlen(input);
    int start = 0, end = length - 1;
    int j = 0;
    int commaFound = 0;
    int i;

    /* Remove leading whitespace */
    while (start < length && isspace((unsigned char)input[start])) 
    {
        start++;
    }

    /* Remove trailing whitespace */
    while (end > start && isspace((unsigned char)input[end])) 
    {
        end--;
    }

    /* Process the string */
    for (i = start; i <= end && j < MAX_LINE_LENGTH - 1; i++) 
    {
        /* Remove duplicate whitespace */
        if (isspace((unsigned char)input[i]) && (j == 0 || isspace((unsigned char)output[j - 1]))) 
        {
            continue;
        }
        
        /* Handle commas */
        if (input[i] == ',') 
        {
            /* Remove space before comma if not after another comma */
            if (j > 0 && isspace((unsigned char)output[j - 1]) && !commaFound) 
            {
                j--;
            }
            output[j++] = ',';
            if (j < MAX_LINE_LENGTH - 1) 
            {
                output[j++] = ' ';
            }
            commaFound = 1;
        } 
        else 
        {
            output[j++] = input[i];
            commaFound = 0;
        }
    }

    /* Remove trailing space if it exists */
    if (j > 0 && isspace((unsigned char)output[j - 1])) 
    {
        j--;
    }

    /* Null-terminate the string */
    output[j] = '\0';
}


boolean isSpaceOrEnd(char c)
{
    return c == ' ' || c == '\0' || c == '\t' || c == '\n' || c == EOF;
}

