#ifndef SECONDPASS_H
#define SECONDPASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures/tableStructure/list.h"
#include "definitions/definitions.h"
#include "structures/symbol.h"
#include "process/validationFunctions/errors.h"
#include "process/utilsPass.h"
#include "process/processingFunctions/processingLineFunct.h"

/**
 * Updates the position of data symbols in the symbol list.
 * 
 * @param symbolList The list of symbols.
 * @param IC The instruction counter.
 * @return true if successful, false otherwise.
 */
int symbolPositionUpdate(ptrNode symbolList, int IC);

/**
 * Validates symbols in the memory appearance list and entry list.
 * 
 * @param inputFileName Name of the input file.
 * @param symbolList The list of symbols.
 * @param memAppearList The list of symbol appearances in memory.
 * @param entryList The list of entry symbols.
 * @return true if all symbols are valid, false otherwise.
 */
int symbolValidation(char* inputFileName, ptrNode symbolList, ptrNode memAppearList, ptrNode entryList);

/**
 * Updates the addresses of entry symbols.
 * 
 * @param symbolList The list of symbols.
 * @param entryList The list of entry symbols.
 * @return true if successful, false otherwise.
 */
int updateEnSymbolsAdress(ptrNode symbolList, ptrNode entryList);

/**
 * Creates the external symbols file (.ext).
 * 
 * @param outputFileName Name of the output file.
 * @param symbolList The list of symbols.
 * @param symbolAppearance The list of symbol appearances.
 * @return true if successful, false otherwise.
 */
int createExFile(char* outputFileName, ptrNode symbolList, ptrNode symbolAppearance);

/**
 * Creates the entry symbols file (.ent).
 * 
 * @param outputFileName Name of the output file.
 * @param symbolList The list of symbols.
 * @param entryList The list of entry symbols.
 * @return true if successful, false otherwise.
 */
int createEnFile(char* outputFileName, ptrNode symbolList, ptrNode entryList);

/**
 * Creates the object file (.ob).
 * 
 * @param outputFileName Name of the output file.
 * @param memoryImage The memory image.
 * @param symbolList The list of symbols.
 * @param symAppearanceList The list of symbol appearances.
 * @param IC The instruction counter.
 * @param DC The data counter.
 * @return true if successful, false otherwise.
 */
int createObFile(char* outputFileName, ptrNode memoryImage, ptrNode symbolList, ptrNode symAppearanceList, int IC, int DC);

/**
 * Performs the second pass of the assembler.
 * 
 * @param FileName Array of file names.
 * @param memoryImage The memory image.
 * @param symbolList The list of symbols.
 * @param enteryList The list of entry symbols.
 * @param symAppearMem The list of symbol appearances in memory.
 * @param IC The instruction counter.
 * @param DC The data counter.
 * @param errorFound Flag indicating if an error was found in the first pass.
 * @return true if successful, false otherwise.
 */
int secondPass(char* FileName[6], ptrNode memoryImage, ptrNode symbolList, ptrNode enteryList, ptrNode symAppearMem, int IC, int DC, boolean errorFound);

/**
 * Checks if there are any external symbols in the symbol list.
 * 
 * @param symbolList The list of symbols.
 * @return true if external symbols are found, false otherwise.
 */
boolean isThereExtern(ptrNode symbolList);

#endif /* SECONDPASS_H */