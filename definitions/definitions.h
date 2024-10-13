#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>

#include "structures/tableStructure/node.h"

/*File for the definitions*/

#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 31

#define MIN_REGISTER_VALUE 0
#define MAX_REGISTER_VALUE 7

/*Definitions of max-min values avaliable*/
#define MIN_IMMIDIATE_VALUE -2048
#define MAX_IMMIDIATE_VALUE 2047
#define MAX_INTEGER_VALUE 16383
#define MIN_INTEGER_VALUE -16384

#define MAX_MEMORY_SIZE 4096

#define NUM_OF_REGISTERS 8
#define NUM_OF_CODE_INSTRUCTIONS 16
typedef enum {false, true} boolean;

/*Definitions for code instructions*/
typedef enum {mov, cmp, add, sub, lea, clr, not, inc, dec, jmp, bne, red, prn, jsr, rts, stop, ERROR_CODE} codeType;

#define CODE_INSTRUCTIONS_NAMES {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop", NULL}
#define NUM_OF_OPERANDS_REQUIRED {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}

#define NUM_OF_DRESSING_OPTIONS {4, 3, 2, 1}
typedef enum {OPT1, OPT2, OPT3, OPT4, NO_OPT} optType;
#define OPTIONS_FOR_ADRESSING { \
    {IMMIDIATE, DIRECT, INDIRECT_REGISTER, DIRECT_REGISTER, -1}, \
    {DIRECT, INDIRECT_REGISTER, DIRECT_REGISTER, -1, 0}, \
    {DIRECT, INDIRECT_REGISTER, -1, 0, 0}, \
    {DIRECT, -1, 0, 0, 0} \
}
#define SRC_OPTIONS_FOR_INSTRUCTION {OPT1, OPT1, OPT1, OPT1, OPT4, NO_OPT, NO_OPT, NO_OPT, NO_OPT, NO_OPT, NO_OPT, NO_OPT, NO_OPT, NO_OPT, NO_OPT, NO_OPT}
#define DEST_OPTIONS_FOR_INSTRUCTION {OPT2, OPT1, OPT2, OPT2, OPT2, OPT2, OPT2, OPT2, OPT2, OPT3, OPT3, OPT2, OPT1, OPT3, NO_OPT, NO_OPT}

typedef enum{IMMIDIATE, DIRECT, INDIRECT_REGISTER, DIRECT_REGISTER, ADRRESING_ERROR} adressingMode;

#define REGISTER_NAMES {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", NULL}
#define FIRST_SRC_REGISTER_INDEX 6
#define FIRST_DST_REGISTER_INDEX 9

#define OPCODE_LENGTH 4

#define FIRST_SRC_ADRESSING_INDEX 4
#define FIRST_DST_ADRESSING_INDEX 8

#define ADRESSING_MODES_BINARY {"0001", "0010", "0100", "1000", "0000"}

#define ARE_FIRST_INDEX 12

#define DST_ADRRESSING {8, 9, 10, 11}
#define SRC_ADRRESSING {4, 5, 6, 7}

#define A_BINARY "100"
#define R_BINARY "010"
#define E_BINARY "001"
#define ARE_LENGTH 3

#define SRC_FIRST_INDEX 6
#define DST_FIRST_INDEX 9

#define BINARY_OPERAND_LENGTH 12

#define OPCODE_BINARY {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111", "????"}

#define MEMORY_WORD_LENGTH 15

/*Definitions for data instructions*/
#define DATA_INSTRUCTIONS {".data", ".string", NULL}
typedef enum {STRING, DATA, ERROR_DATA} dataType;
#define DATA_LENGTH 5
#define STRING_LENGTH 7
#define DATA_COMMAND_LENGTH {DATA_LENGTH, STRING_LENGTH}    

/*Definitions for extern - entry commands*/
#define EXTERN_ENTRY_COMMANDS {".extern", ".entry", NULL}
typedef enum {ENTRY, EXTERN, ERROR_EXTERN_ENTRY} externEntryType;
#define ENTRY_LENGTH 6
#define EXTERN_LENGTH 7
#define LENGTH_OF_EX_EN {ENTRY_LENGTH, EXTERN_LENGTH}

enum {inputFileName, baseName, amFile, obFile, entFile, extFile};

/*Global variables for freeing the memory from each sub-function if needed*/
char* FILE_NAMES_PTR[6];
ptrNode* SYMBOL_LIST_PTR;
ptrNode* ENTRY_LIST_PTR;
ptrNode* MEM_IMAGE_PTR;
ptrNode* SYM_APPEAR_MEM_PTR;
ptrNode* CODE_IMAGE_PTR;
ptrNode* DATA_IMAGE_PTR;
ptrNode* MACRO_LIST_PTR;

FILE *INPUT_FILE;
FILE *AM_FILE;
FILE *OB_FILE;
FILE *ENT_FILE;
FILE *EXT_FILE;
FILE *INTERMEDIATE_FILE;



#endif