# chasm
An assembler for the CHIP-8 programming language.

## Note from the author
Development of this project ceased in 2011. The source code is provided here 
only for reference. It is not guaranteed to be bug-free, and will not be
maintained. For a more complete and actively developed CHIP-8 assembler,
consider using [Octo][1].

## Usage
To assemble a CHIP-8 program using chasm, execute the following command:

    chasm [input filename] [output filename]

For more information about how to use chasm, see the [MANUAL][2].

## Compiling
chasm can be compiled using the GNU C++ Compiler (G++) of the GNU Compiler
Collection (GCC).

    g++ chasm.cpp -o chasm

A `makefile` is also included with this project.

## License
This project is licensed under the MIT License. For more information, see the
included [LICENSE][3] file.

[1]: http://github.com/JohnEarnest/Octo "Octo"
[2]: MANUAL.md "chasm Manual"
[3]: LICENSE "MIT License"
