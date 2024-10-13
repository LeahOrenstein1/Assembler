#ifndef FREEINGALLOCATIONSFUNC_H
#define FREEINGALLOCATIONSFUNC_H

#include "definitions/definitions.h"
#include "structures/tableStructure/list.h"
#include "structures/macro.h"
#include "structures/command.h"
#include "structures/symbol.h"
#include "structures/symbolAppearance.h"

/* Function prototypes */

/**
 * safeExit - Safely exits the program.
 * @status: The exit status to be passed to the exit() function.
 *
 * This function frees all allocated resources, closes open files,
 * and then exits the program with the given status.
 */
void safeExit(int status);


/**
 * freeAllResources - Frees all dynamically allocated resources.
 *
 * This function frees memory allocated for file names and various
 * linked lists used throughout the program. It sets all freed
 * pointers to NULL to prevent dangling references.
 *
 * Lists freed: SYMBOL_LIST_PTR, ENTRY_LIST_PTR, DATA_IMAGE_PTR,
 * CODE_IMAGE_PTR, MEM_IMAGE_PTR, SYM_APPEAR_MEM_PTR, MACRO_LIST_PTR.
 */
void freeAllResources();


/**
 * closeFiles - Closes all open file handles used by the program.
 *
 * This function closes the following file handles if they are open:
 * INPUT_FILE, AM_FILE, OB_FILE, ENT_FILE, EXT_FILE, and INTERMEDIATE_FILE.
 * It sets all closed file pointers to NULL.
 */
void closeFiles();

#endif