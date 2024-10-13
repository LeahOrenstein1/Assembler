# Compiler
CC = gcc

# Compiler flags
CFLAGS = -ansi -pedantic -Wall

# Include directories
INCLUDES = -I. -ImainAssembler -Iprocess -Iprocess/validationFunctions -Iprocess/processingFunctions -Istructures -Istructures/tableStructure -Idefinitions

# Source files
SRCS = mainAssembler/assembler.c mainAssembler/utils.c mainAssembler/freeingAllocationsFunc.c \
       process/preAssembler.c process/firstPass.c process/secondPass.c process/utilsPass.c \
       process/validationFunctions/errors.c process/validationFunctions/utilsError.c \
       process/processingFunctions/processingLineFunct.c \
       structures/command.c structures/macro.c structures/symbol.c \
       structures/symbolAppearance.c \
       structures/tableStructure/list.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: assembler

# Linking the final executable
assembler: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@

# Generic rule for creating object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean target
clean:
	del /Q mainAssembler\*.o process\*.o process\validationFunctions\*.o process\processingFunctions\*.o structures\*.o structures\tableStructure\*.o assembler.exe

# Dependencies
mainAssembler/assembler.o: mainAssembler/assembler.c process/preAssembler.h process/firstPass.h process/secondPass.h structures/command.h structures/macro.h mainAssembler/freeingAllocationsFunc.h definitions/definitions.h
mainAssembler/utils.o: mainAssembler/utils.c mainAssembler/utils.h
mainAssembler/freeingAllocationsFunc.o: mainAssembler/freeingAllocationsFunc.c mainAssembler/freeingAllocationsFunc.h structures/tableStructure/list.h structures/symbol.h structures/symbolAppearance.h definitions/definitions.h
process/preAssembler.o: process/preAssembler.c process/preAssembler.h structures/macro.h structures/command.h structures/tableStructure/list.h mainAssembler/utils.h definitions/definitions.h
process/firstPass.o: process/firstPass.c process/firstPass.h structures/symbol.h structures/tableStructure/list.h process/validationFunctions/errors.h process/utilsPass.h mainAssembler/utils.h definitions/definitions.h
process/secondPass.o: process/secondPass.c process/secondPass.h structures/symbol.h structures/tableStructure/list.h process/utilsPass.h mainAssembler/utils.h definitions/definitions.h
process/utilsPass.o: process/utilsPass.c process/utilsPass.h mainAssembler/utils.h structures/tableStructure/list.h definitions/definitions.h
process/validationFunctions/errors.o: process/validationFunctions/errors.c process/validationFunctions/errors.h process/utilsPass.h structures/tableStructure/list.h definitions/definitions.h
process/validationFunctions/utilsError.o: process/validationFunctions/utilsError.c process/validationFunctions/utilsError.h definitions/definitions.h
process/processingFunctions/processingLineFunct.o: process/processingFunctions/processingLineFunct.c process/processingFunctions/processingLineFunct.h definitions/definitions.h
structures/command.o: structures/command.c structures/command.h
structures/macro.o: structures/macro.c structures/macro.h structures/tableStructure/list.h structures/command.h
structures/symbol.o: structures/symbol.c structures/symbol.h mainAssembler/freeingAllocationsFunc.h
structures/symbolAppearance.o: structures/symbolAppearance.c structures/symbolAppearance.h definitions/definitions.h
structures/tableStructure/list.o: structures/tableStructure/list.c structures/tableStructure/list.h structures/tableStructure/node.h

# Phony targets
.PHONY: all clean