# Assembler Project

This project implements an assembler for a custom assembly language. 
The assembler takes assembly code as input and produces machine code as output, along with additional files for linking and loading.

## Features

- Macro expansion
- Two-pass assembly process
- Thoroughly tested and verified for correctness
- Supports various addressing modes
- Generates object files (.ob), entry files (.ent), and external files (.ext)
- Error detection and reporting
- Efficient memory management using advanced C programming techniques

## Project Structure

```
.
├── definitions/              # Project-wide definitions
├── invalid_inputs_examples/  # Examples of invalid input files
├── mainAssembler/            # Main assembler code
├── process/                  # Assembly process implementation
│   ├── processingFunctions/  # Functions for processing assembly lines
│   └── validationFunctions/  # Error checking and validation functions
├── structures/               # Data structure implementations
│   └── tableStructure/       # List and node structures
└── valid_inputs_examples/    # Examples of valid input files
```

### Key Files

- `assembler.exe`: The compiled assembler executable
- `makefile`: Build configuration for the project

## Building the Project

To build the project, use the provided makefile:

```
make
```

This will compile all the necessary files and create the `assembler.exe` executable.

## Usage

```
./assembler <file1> <file2> ... <fileN>
```

Important Note on File Names:

Input files should be specified without the '.as' suffix.
The assembler automatically appends '.as' to the input file names.
For example, to assemble a file named 'program.as', use:
./assembler program

## Input Files

Input files should have the `.as` extension and contain valid assembly code according to the defined language syntax. Examples of valid and invalid input files can be found in the `valid_inputs_examples/` and `invalid_inputs_examples/` directories respectively. 

## Output Files

For each input file, the assembler generates:

- `.am` file: The input file after macro expansion
- `.ob` file: The object file containing the machine code
- `.ent` file: Entry points defined in the assembly code (if any)
- `.ext` file: External references used in the assembly code (if any)

Examples of these output files can be found in the `valid_inputs_examples/` directory.

## Error Handling

The assembler performs extensive error checking and will report any syntax errors, undefined symbols, or other issues encountered during the assembly process. Examples of error messages for invalid inputs can be found in the `invalid_inputs_examples/` directory.

## Memory Management

This project demonstrates advanced memory management techniques in C:

Efficient allocation and deallocation of memory
Proper use of dynamic memory allocation
Prevention of memory leaks through careful resource management
Optimized data structures to minimize memory footprint
