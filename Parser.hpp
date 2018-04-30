#ifndef PARSER_HPP
#define PARSER_HPP
#pragma once

#include <string>
#include <vector>

#include "Node.hpp"
#include "Token.hpp"

class Parser
{
public:
	Parser()
	{
	}

	~Parser()
	{
	}

	// Parses a number token
	Node* ParseNumber(std::vector<Token*>& token, int current)
	{
		Node* node = new Node(NodeType::NUMBERLITERAL, token[current]->value);
		return node;
	}

	// Parses a string token
	Node* ParseString(std::vector<Token*>& token, int current)
	{
		Node* node = new Node(NodeType::STRINGLITERAL, token[current]->value);
		return node;
	}

	// Parses an expression
	Node* ParseExpression(std::vector<Token*>& tokens, int current)
	{

	}

public:
	Node* root;
};

#endif