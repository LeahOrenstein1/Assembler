#ifndef PROCESSLINEFUNCT_H
#define PROCESSLINEFUNCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilsError.h"
#include "process/preAssembler.h"
#include "structures/tableStructure/list.h"
#include "utilsPass.h"
#include "mainAssembler/utils.h"
#include "definitions/definitions.h"
#include "structures/symbol.h"
#include "validationFunctions/errors.h"
#include "structures/symbolAppearance.h"

/**
 * Processes a data instruction line and updates the data image.
 *
 * @param line The instruction line to process.
 * @param dataImage Pointer to the data image list.
 * @param L Pointer to store the number of memory words used.
 * @return 1 if successful, 0 if an error occurred.
 */
int processDataInstruction(char* line, ptrNode *dataImage, int* L);

/**
 * Processes a code instruction line and updates the code image.
 *
 * @param line The instruction line to process.
 * @param codeImage Pointer to the code image list.
 * @param symbolList The symbol table.
 * @param symbolMemApearance Pointer to the symbol memory appearance list.
 * @param L Pointer to store the number of memory words used.
 * @param IC Current instruction counter.
 * @param lineNumber Current line number in the source file.
 * @return 1 if successful, 0 if an error occurred.
 */
int processCodeInstruction(char* line, ptrNode *codeImage, ptrNode symbolList, ptrNode* symbolMemApearance, int* L, int IC, int lineNumber);

/**
 * Processes an extern instruction and updates the symbol list.
 *
 * @param line The instruction line to process.
 * @param symbolList Pointer to the symbol list.
 * @param lineNumber Current line number in the source file.
 * @param fileName Name of the current source file.
 * @return 1 if successful, 0 if an error occurred.
 */
int processExternInstruction(char* line, ptrNode *symbolList, int lineNumber, char* fileName);

/**
 * Processes an entry instruction and updates the entry list.
 *
 * @param line The instruction line to process.
 * @param entryList Pointer to the entry list.
 * @param lineNumber Current line number in the source file.
 * @return 1 if successful, 0 if an error occurred.
 */
int processEntryInstruction(char* line, ptrNode *entryList, int lineNumber);

/**
 * Processes the source memory word for a code instruction.
 *
 * @param srcOp Source operand.
 * @param dstOp Destination operand.
 * @param srcMem Array to store the processed memory word.
 * @param srcAdMode Addressing mode of the source operand.
 * @param dstAdMode Addressing mode of the destination operand.
 * @param symbolList The symbol table.
 * @param twoRegisters Flag indicating if both operands are registers.
 * @return 1 if successful, 0 if an error occurred.
 */
int processSrcMemWord(char* srcOp, char* dstOp, char srcMem[MEMORY_WORD_LENGTH + 1], adressingMode srcAdMode, adressingMode dstAdMode, ptrNode symbolList, boolean twoRegisters);

/**
 * Processes the destination memory word for a code instruction.
 *
 * @param dstOp Destination operand.
 * @param dstMem Array to store the processed memory word.
 * @param dstAdMode Addressing mode of the destination operand.
 * @return 1 if successful, 0 if an error occurred.
 */
int processDstMemWord(char* dstOp, char dstMem[MEMORY_WORD_LENGTH + 1], adressingMode dstAdMode);

#endif /* PROCESSLINEFUNCT_H */