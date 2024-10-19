# Compiler

This project is a C++ implementation of [Yehonathan Sharvit's JavaScript compiler](http://blog.klipse.tech/javascript/2017/02/08/tiny-compiler-intro.html).

The project has 4 main parts:

- Tokenizer
- Parser
- Emitter
- Compiler

## Concepts

### Tokenizer

The Tokenizer class takes input and converts it into a vector of Tokens. Each token consists of a type and a value.

### Parser

The Parser class takes in tokens and converts it into an Abstract Syntax Tree (AST).

### Emitter

The Emitter class takes the AST and converts it into C-like code syntax (string-ify).

### Compiler

The Compiler class combines all of the previous parts.

## Building

### `g++`

Build: `g++ *.cpp *.hpp -o compiler.o`
Run: `./compiler.o`

### Docker

Build: `docker build . --tag compiler`
Run: `docker run --rm -i compiler:latest`
