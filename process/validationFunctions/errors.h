#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

#include "utilsError.h"
#include "process/preAssembler.h"
#include "structures/tableStructure/list.h"
#include "utilsPass.h"
#include "definitions/definitions.h"

/**
 * Checks a data command for errors.
 *
 * @param line The line containing the data command to check.
 * @param inputFileName The name of the input file being processed.
 * @param lineNumber The line number in the input file.
 * @return 1 if any error is found, 0 otherwise.
 */
int errorInData(char* line, char* inputFileName, int lineNumber);

/**
 * Checks a code command for errors.
 *
 * @param line The line containing the code command to check.
 * @param inputFileName The name of the input file being processed.
 * @param lineNumber The line number in the input file.
 * @return 1 if any error is found, 0 otherwise.
 */
int errorInCode(char* line, char* inputFileName, int lineNumber);

/**
 * Checks a label for errors.
 *
 * @param label The label to check.
 * @param inputFileName The name of the input file being processed.
 * @param lineNumber The line number in the input file.
 * @param symbolList The list of symbols to check for duplicates.
 * @return 1 if any error is found, 0 otherwise.
 */
int errorInLabel(char* label, char* inputFileName, int lineNumber, ptrNode symbolList);

/**
 * Checks an .extern or .entry command for errors.
 *
 * @param line The line containing the .extern or .entry command to check.
 * @param inputFileName The name of the input file being processed.
 * @param lineNumber The line number in the input file.
 * @return 1 if any error is found, 0 otherwise.
 */
int errorInExEn(char* line, char* inputFileName, int lineNumber);

#endif /* ERRORS_H */