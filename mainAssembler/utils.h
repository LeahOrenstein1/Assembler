#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "freeingAllocationsFunc.h"
#include "definitions/definitions.h"

#define MAX_LINE_LENGTH 81

/* Helper functions */

/**
 * Trims whitespace from the beginning and end of a string.
 *
 * @param str The input string to trim.
 * @param result Buffer to store the trimmed string.
 * @param result_size Size of the result buffer.
 */
void trimWhitespace(const char* str, char* result, size_t result_size);

/**
 * Allocates memory for a file name and initializes it.
 *
 * @param fileName The original file name.
 * @param size The size to allocate (usually strlen(fileName) + some extra).
 * @return A pointer to the newly allocated and initialized string.
 */
char* AllocateMemFileName(const char* fileName, size_t size);

/**
 * Skips leading whitespace in a string.
 *
 * @param str The input string.
 * @return A pointer to the first non-whitespace character in the string.
 */
char* skipWhitespace(char* str);

/**
 * Trims and formats a string, handling whitespace and commas.
 *
 * This function removes leading and trailing whitespace, reduces multiple
 * spaces to single spaces, and ensures proper spacing around commas.
 *
 * @param input The input string to format.
 * @param output Buffer to store the formatted string.
 */
void trimAndFormatString(const char *input, char output[MAX_LINE_LENGTH]);

/**
 * Checks if a character is a space or the end of a string.
 * 
 * @param c The character to check.
 * @return 1 if the character is a space or the end of a string, 0 otherwise.
 */
boolean isSpaceOrEnd(char c);

#endif /* UTILS_H */