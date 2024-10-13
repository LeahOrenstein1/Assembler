#ifndef UTILSPASS_H
#define UTILSPASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mainAssembler/utils.h"
#include "structures/tableStructure/list.h"
#include "definitions/definitions.h"
#include "validationFunctions/utilsError.h"

/**
 * Checks if a line contains a valid data instruction.
 * @param line The line to check.
 * @return 1 if it's a data line, 0 otherwise.
 */
int isDataLine(char* line);

/**
 * Checks if a line contains a valid code instruction.
 * @param line The line to check.
 * @return 1 if it's a code line, 0 otherwise.
 */
int isCodeLine(char* line);

/**
 * Checks if a line contains an extern instruction.
 * @param line The line to check.
 * @return 1 if it's an extern line, 0 otherwise.
 */
int isExternLine(char* line);

/**
 * Checks if a line contains an entry instruction.
 * @param line The line to check.
 * @return 1 if it's an entry line, 0 otherwise.
 */
int isEntryLine(char* line);

/**
 * Counts the number of operands in a line.
 * @param line The line to check.
 * @return The number of operands.
 */
int numOfOperands(char* line);

/**
 * Checks if a string contains only alphanumeric characters.
 * @param str The string to check.
 * @return 1 if the string is alphanumeric, 0 otherwise.
 */
int isAlphanumeric(const char *str);

/**
 * Gets the next operand from a line.
 * @param line The line to parse.
 * @param endOfOperand Pointer to store the end of the operand.
 * @return Pointer to the start of the operand.
 */
char* getOperand(char* line, char** endOfOperand);

/**
 * Determines the type of extern/entry instruction.
 * @param line The line to check.
 * @return The externEntryType of the instruction.
 */
externEntryType retExEnType(const char* line);

/**
 * Checks if a string represents an immediate value.
 * @param str The string to check.
 * @return 1 if it's an immediate value, 0 otherwise.
 */
int isImmediate(char* str);

/**
 * Checks if a string represents a direct addressing mode.
 * @param str The string to check.
 * @return 1 if it's a direct addressing mode, 0 otherwise.
 */
int isDirect(char* str);

/**
 * Checks if a string represents a direct register.
 * @param str The string to check.
 * @return 1 if it's a direct register, 0 otherwise.
 */
int isDirectRegister(char* str);

/**
 * Checks if a string represents an indirect register.
 * @param str The string to check.
 * @return 1 if it's an indirect register, 0 otherwise.
 */
int isInDirectRegister(char* str);

/**
 * Determines the type of data instruction.
 * @param line The line to check.
 * @return The dataType of the instruction.
 */
dataType retDataType(char* line);

/**
 * Determines the type of code instruction.
 * @param line The line to check.
 * @return The codeType of the instruction.
 */
codeType retCodeType(char* line);

/**
 * Converts an integer to its binary string representation.
 * @param num The number to convert.
 * @param result The string to store the result.
 * @param length The length of the binary string.
 */
void intToBinaryString(int num, char* result, int length);

/**
 * Gets the opcode for a given code instruction type.
 * @param codeType The type of code instruction.
 * @return The opcode as a string.
 */
char* getOpCode(codeType codeType);

#endif /* UTILSPASS_H */