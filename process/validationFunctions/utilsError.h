#ifndef UTILSERROR_H
#define UTILSERROR_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "mainAssembler/utils.h"
#include "definitions/definitions.h"
#include "utilsPass.h"

/**
 * Checks if there are two operands which are not separated with a comma.
 * @param str The string to check.
 * @return 1 if there are adjacent items without a comma, 0 otherwise.
 */
int hasAdjacentItemsWithoutComma(char* str);

/**
 * Checks if all operands in a line are integers.
 * @param line The line to check.
 * @return 1 if all operands are integers, 0 otherwise.
 */
int operandsAreIntegers(char* line);

/**
 * Checks if all operands in a line are within the valid range.
 * @param line The line to check.
 * @return 1 if all operands are in range, 0 otherwise.
 */
int operandsAreInRange(char* line);

/**
 * Checks if a string is a valid quoted string.
 * @param str The string to check.
 * @return 1 if the string is a valid quoted string, 0 otherwise.
 */
int isValidQuotedString(char* str);

/**
 * Checks if a string represents a valid integer.
 * @param str The string to check.
 * @return 1 if the string is a valid integer, 0 otherwise.
 */
int isValidInteger(char* str);

/**
 * Checks if a number represented by a string is within the valid range.
 * @param str The string representing the number.
 * @return 1 if the number is in range, 0 otherwise.
 */
int isNumberInRange(char* str);

/**
 * Determines the type of code instruction.
 * @param line The line containing the instruction.
 * @return The codeType of the instruction.
 */
codeType checkCodeType(char* line);

/**
 * Determines the addressing mode of the first operand in the line.
 * @param line The line to check.
 * @return The adressingMode of the operand.
 */
adressingMode checkAdressingMode(char* line);

/**
 * Checks if there are multiple commas in a well-formed string.
 * @param line The line to check.
 * @return 1 if multiple commas are found, 0 otherwise.
 */
int multipleCommas(char* line);

/**
 * Checks if a string represents a valid register.
 * @param str The string to check.
 * @return 1 if the string is a valid register, 0 otherwise.
 */
int isRegister(char* str);

/**
 * Checks if the operands have valid addressing modes for the specific command type.
 * @param line The line containing the operands.
 * @param type The type of the code instruction.
 * @return 1 if addressing modes are valid, 0 otherwise.
 */
int validAdressingModes(char* line, codeType type);

/**
 * Checks if an operand is valid and prints an error message if it's not.
 * @param operand The operand to check.
 * @param inputFileName The name of the input file.
 * @param lineNumber The line number in the input file.
 * @return 1 if the operand is valid, 0 otherwise.
 */
int isValidOperand(char* operand, char* inputFileName, int lineNumber);

/**
 * Checks if a string represents a register that is out of the valid range.
 * @param str The string to check.
 * @return 1 if the register is out of range, 0 otherwise.
 */
int isRegisterOutOfRange(char* str);

/**
 * Checks if a string represents an immediate value that is out of the valid range.
 * @param str The string to check.
 * @return 1 if the immediate value is out of range, 0 otherwise.
 */
int isImmediateOutOfRange(char* str);

/**
 * Checks if a label used as an operand is valid.
 * @param line The line containing the label.
 * @return 1 if there's an error in the label, 0 if it's valid.
 */
int errorInLabelAsOperand(char* line);

#endif /* UTILSERROR_H */