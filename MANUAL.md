# chasm Manual
Version 1.0

Originally released December 2010

Converted to Markdown November 2016

## Introduction
CHIP-8 is an interpreted programming language initially developed by Joseph
Weisbecker for the COSMAC VIP computer in 1977. Created to simplify the
programming of video games, CHIP-8 was popular and portable for the computers of
its generation. As a result, a variety of games have been developed in the
CHIP-8 language.

CHIP-8 allows graphical output to a sixty-four by thirty-two monochrome pixel
display. One sound timer triggers the playing of a monotone frequency, and one
delay timer can be used for scheduling. A sixteen-key hexadecimal keypad is used
for input. Sixteen eight-bit data registers can be used to store data, and the
sixteen-bit address register can be used to store a memory address.

The portability of the CHIP-8 language is due to the fact that it is an
interpreted hexadecimal language. All CHIP-8 instructions are hexadecimal
numbers and can be easily stored and read in memory. However, programming in
CHIP-8 has often been perceived as a difficult task due to this hexadecimal
format, as the purpose of each instruction in a program is not immediately
evident. Because of this, the need for a CHIP-8 pseudo-assembler arises.

The CHIP-8 language is an interpreted programming language, as its instructions
are read by an interpreting program, which then executes corresponding code on
the host computer. chasm presents the CHIP-8 language to a programmer using a
system of easy-to-read and remember mnemonics, which are then translated into
the traditional interpreted CHIP-8 opcodes. Because the chasm mnemonics are
translated into an interpreted language rather than a machine language, chasm is
known as a pseudo-assembler instead of a regular assembler.

Although this difference may be important, it over-complicates the matters that
this manual concerns. Therefore, the mnemonic language used by chasm will be
identified as assembly language from this point on, and the interpreted
programming language that chasm outputs will be identified as machine language
or machine code.

## Features
chasm is a pseudo-assembler for the CHIP-8 programming language. It was designed
to accept a text file containing 'assembly language' mnemonics as input, and
output the resulting CHIP-8 'machine code' to a separate file.

Version 1.0 of chasm supports all thirty-five original CHIP-8 commands defined
by Joseph Weisbecker for the COSMAC VIP computer.

chasm also supports an additional command called the `.START` command, used to
specify the memory address at which the resulting CHIP-8 program should be
loaded on the host machine. This designated value is used by chasm to determine
the values of label addresses during the label linking process. Although the
`.START` command is completely optional, it should be the first command found in
the input file when present.

chasm supports two other commands, the `DB` and `DW` commands, which accept an
8-bit value and a 16-bit value respectively as arguments. These commands insert
the given argument into the generated output code at the corresponding address,
and can be used to insert graphics data into CHIP-8 assembly source code.

## Supported instructions
*   Code in { } brackets designate optional parameters for an instruction.
*   Vx and Vy are register names, kk is a byte, nnn is an address, n is a
    nibble.

| Opcode | Mnemonic                 |
| :----: | :----------------------- |
|  00E0  | CLS                      |
|  00EE  | RET                      |
|  0nnn  | SYS (addr)               |
|  1nnn  | JP (addr)                |
|  2nnn  | CALL (addr)              |
|  3xkk  | SE (Vx), (byte)          |
|  4xkk  | SNE (Vx), (byte)         |
|  5xy0  | SE (Vx), (Vy)            |
|  6xkk  | LD (Vx), (byte)          |
|  7xkk  | ADD (Vx), (byte)         |
|  8xy0  | LD (Vx), (Vy)            |
|  8xy1  | OR (Vx), (Vy)            |
|  8xy2  | AND (Vx), (Vy)           |
|  8xy3  | XOR (Vx), (Vy)           |
|  8xy4  | ADD (Vx), (Vy)           |
|  8xy5  | SUB (Vx), (Vy)           |
|  8xy6  | SHR (Vx) {, (Vy)}        |
|  8xy7  | SUBN (Vx), (Vy)          |
|  8xyE  | SHL (Vx) {, (Vy)}        |
|  9xy0  | SNE (Vx), (Vy)           |
|  Annn  | LD I, (addr)             |
|  Bnnn  | JP V0, (addr)            |
|  Cxkk  | RND (Vx), (byte)         |
|  Dxyn  | DRW (Vx), (Vy), (nibble) |
|  Ex9E  | SKP (Vx)                 |
|  ExA1  | SKNP (Vx)                |
|  Fx07  | LD (Vx), DT              |
|  Fx0A  | LD (Vx), K               |
|  Fx15  | LD DT, (Vx)              |
|  Fx18  | LD ST, (Vx)              |
|  Fx1E  | ADD I, (Vx)              |
|  Fx29  | LD F, (Vx)               |
|  Fx33  | LD B, (Vx)               |
|  Fx55  | LD [I], (Vx)             |
|  Fx65  | LD (Vx), [I]             |
|  N/A   | .START (addr)            |
|  N/A   | DB (byte)                |
|  N/A   | DW (word)                |

## Example output
The following table contains a side-by-side comparison of two files: input.asm,
a text file containing assembly language mnemonics, and output.c8, a data file
containing corresponding CHIP-8 machine language opcodes. Each line (or lines)
of input.asm has its corresponding CHIP-8 opcode printed directly adjacent under
the output.c8 column. input.asm is printed as if viewed in a standard ASCII text
editor, and output.c8 is printed as if viewed in a hexadecimal editor with a
byte-span value of 2. It should be noted that CHIP-8 commands are stored using
big-endian mode, with the most-significant byte first and the least-significant
byte last.

        ----- input.asm -----             --- output.c8 ---
        START:  CLS                             00E0
                RND V0, #FF                     C0FF
                LD I, #224                      A224
                LD B, V0                        F033
                LD V2, [I]                      F265
                LD F, V0                        F029
                LD V0, #00                      6000
                LD V3, #00                      6300
                DRW V0, V3, 5                   D035
                LD F, V1                        F129
                LD V0, #05                      6005
                DRW V0, V3, 5                   D035
                LD F, V2                        F229
                LD V0, 10                       600A
                DRW V0, V3, 5                   D035
                LD V0, K                        F00A
                JP START                        1200

                DB #FF                          FFEA
                DB #EA                              

                DW #21AC                        21AC

## Proper usage
chasm accepts two files: an input file and an output file. The lines stored in
the input file are read and converted into corresponding CHIP-8 code, which is
then stored in the output file. If an error occurs while opening either the
input or output file, an error message is displayed to the user.

The proper syntax for chasm is:

    chasm [input filename] [output filename]

If this syntax is not followed, an error message, along with the guidelines for
the proper syntax, are displayed to the user.

## Design description
### Initialization
Upon startup, chasm checks to make sure the correct amount of command line
arguments were entered and processes them accordingly. chasm is called with the
following syntax:

    chasm [input filename] [output filename]

chasm attempts to open the file passed by the user as input.

### Input processing
chasm processes the assembly language commands found in the input file by
looping through the file and processing each individual line, separating it into
sections called "arguments." An argument is any part of an assembly command. The
following diagram provides an example:

| Argument 0 | Argument 1 |   | Argument 2 |
|:----------:|:----------:|:-:|:----------:|
|     LD     |      F     | , |     V0     |

While separating each line into arguments, chasm checks if a label has been
included. If one is found, a label is created, and the corresponding argument is
removed from the argument array. This allows processing of the line to continue
regardless of the created label.

After the line has been separated into arguments and any present labels have
been removed, chasm begins processing the arguments and generating the resulting
machine code. If an error is found in the syntax of the arguments, or the
assembler undergoes an error, relevant information is printed to the screen.

### Label linking
After the entire input file has been processed, any references to labels made by
assembly language commands will have been stored in a label reference array.
chasm loops through this array, checking to make sure that each label referenced
actually exists, and linking the identified labels with their corresponding
memory addresses.

### File output
chasm has now finished generating machine code corresponding to the assembly
instructions found in the input file. This machine code is sent to the
designated output file for storage, and the program reaches completion.
