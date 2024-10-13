#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "definitions/definitions.h"
#include "structures/macro.h"
#include "structures/command.h"
#include "structures/tableStructure/list.h"
#include "mainAssembler/utils.h"
#include "mainAssembler/freeingAllocationsFunc.h"
#include "utilsPass.h"

/**
 * Processes macro definitions in the input file.
 *
 * This function reads the input file, identifies macro definitions,
 * and writes non-macro content to the output file.
 *
 * @param inputFile Pointer to the input file.
 * @param outputFile Pointer to the output file.
 * @param ptrMacroList Pointer to the macro list to be populated.
 * @param inputFileName Name of the input file (for error reporting).
 * @return 1 if successful, 0 if errors were encountered.
 */
int processMacroDefinitions(FILE* inputFile, FILE* outputFile, ptrNode *ptrMacroList, const char* inputFileName);

/**
 * Expands macros in the input file.
 *
 * This function reads the input file, replaces macro calls with their definitions,
 * and writes the expanded content to the output file.
 *
 * @param inputFile Pointer to the input file.
 * @param outputFile Pointer to the output file.
 * @param macroList List of defined macros.
 * @param inputFileName Name of the input file (for error reporting).
 * @return 1 if successful, 0 if errors were encountered.
 */
int expandMacros(FILE* inputFile, FILE* outputFile, ptrNode macroList, const char* inputFileName);

/**
 * Manages the pre-assembler process.
 *
 * This function orchestrates the entire pre-assembler process, including
 * macro definition processing and macro expansion.
 *
 * @param inputFileName Name of the input file.
 * @param outputFileName Name of the output file.
 * @param macroList Pointer to the macro list to be populated.
 * @return 1 if successful, 0 if errors were encountered.
 */
int preprocessFile(const char* inputFileName, const char* outputFileName, ptrNode* macroList);

#endif /* PREASSEMBLER_H */