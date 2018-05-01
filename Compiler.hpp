#ifndef COMPILER_HPP
#define COMPILER_HPP
#pragma once

#include <string>

#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Emitter.hpp"

class Compiler
{
public:
	Compiler()
	{
	}

	~Compiler()
	{
	}

	// Compile the given input
	std::string Compile(std::string input)
	{
		tokenizer.Tokenize(input);
		parser.ParseProgram(tokenizer.tokens);
		return emitter.Emit(parser.AST);
	}

public:
	Tokenizer tokenizer;
	Parser parser;
	Emitter emitter;
};

#endif