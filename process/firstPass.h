#ifndef FIRSTPASS_H
#define FIRSTPASS_H

#include <stdio.h>

#include "structures/symbol.h"
#include "structures/symbolAppearance.h"
#include "structures/tableStructure/list.h"
#include "validationFunctions/errors.h"
#include "processingFunctions/processingLineFunct.h"
#include "utilsPass.h"
#include "mainAssembler/utils.h"

#define MAX_LINE_LENGTH 81

/**
 * Performs the first pass of the assembler on the input file.
 *
 * @param inputFileName Name of the input file to process.
 * @param memoryImage Pointer to the memory image list.
 * @param symbolListPtr Pointer to the symbol list.
 * @param symAppearMem Pointer to the symbol appearance in memory list.
 * @param entryList Pointer to the entry list.
 * @param IC Pointer to the Instruction Counter.
 * @param DC Pointer to the Data Counter.
 * @return 1 if the first pass was successful, 0 if errors were encountered.
 */
int firstPass(char* inputFileName, ptrNode* memoryImage, ptrNode* symbolListPtr, ptrNode* symAppearMem, ptrNode* entryList, int* IC, int* DC);

/**
 * Processes a single line during the first pass.
 *
 * @param inputFileName Name of the input file being processed.
 * @param line The line to process.
 * @param symbolListPtr Pointer to the symbol list.
 * @param entryList Pointer to the entry list.
 * @param codeImage Pointer to the code image list.
 * @param dataImage Pointer to the data image list.
 * @param symAppearMem Pointer to the symbol appearance in memory list.
 * @param IC Pointer to the Instruction Counter.
 * @param DC Pointer to the Data Counter.
 * @param lineNumber The current line number in the input file.
 * @return 1 if the line was processed successfully, 0 if errors were encountered.
 */
int processLine(char* inputFileName, char* line, ptrNode* symbolListPtr, ptrNode* entryList, ptrNode* codeImage, ptrNode* dataImage, ptrNode* symAppearMem, int* IC, int* DC, int lineNumber);

#endif /* FIRSTPASS_H */