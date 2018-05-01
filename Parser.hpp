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
		ClearAST();
	}

	friend std::ostream& operator<<(std::ostream& os, const Parser& p)
	{
		if (p.AST != nullptr)
		{
			os << *p.AST << std::endl;
		}

		return os;
	}

	void ClearAST()
	{
		if (AST != nullptr)
		{
			for (auto itr = AST->children.begin(); itr != AST->children.end(); itr++)
			{
				delete (*itr);
				(*itr) = nullptr;
			}

			delete AST;
			AST = nullptr;
		}
	}

	void ParseProgram(std::vector<Token*>& tokens)
	{
		// Clear AST
		ClearAST();

		// Keep track of our place in the tokens
		int current = 0;

		// Create the base node for the AST
		AST = new Node(Node::Type::PROGRAM, "program");

		// Create a node pointer for adding to our AST
		Node* node = nullptr;

		while (current < (int)tokens.size())
		{
			node = ParseToken(tokens, &current);
			AST->children.push_back(node);
		}
	}

	// Parse a token
	Node* ParseToken(std::vector<Token*>& tokens, int* current)
	{
		// Get the current token
		Token* token = tokens[(*current)];

		// Parse the token based on it's type
		if (token->type == Token::Type::NUM)
			return ParseNumber(tokens, current);
		if (token->type == Token::Type::STRING)
			return ParseString(tokens, current);
		if (token->type == Token::Type::PAREN && token->value == "(")
			return ParseExpression(tokens, current);

		throw std::invalid_argument("Unknown token type.");
		return nullptr;
	}

	// Parses a number
	Node* ParseNumber(std::vector<Token*>& tokens, int* current)
	{
		// Create a node to return
		Node* node = new Node(Node::Type::NUMBERLITERAL, tokens[(*current)]->value);

		// Increase current
		(*current) += 1;

		return node;
	}

	// Parses a string
	Node* ParseString(std::vector<Token*>& tokens, int* current)
	{
		// Create a node to return
		Node* node = new Node(Node::Type::STRINGLITERAL, tokens[(*current)]->value);

		// Increase current
		(*current) += 1;

		return node;
	}

	// Parses an expression
	Node* ParseExpression(std::vector<Token*>& tokens, int* current)
	{
		// Skip the first token, which is the opening parenthesis
		Token* token = tokens[++(*current)];

		// Create a node to return
		Node* node = new Node(Node::Type::CALLEXPRESSION, token->value);

		// Get the next token (after the expression name)
		token = tokens[++(*current)];

		// Keep parsing the expression
		while (!(token->type == Token::Type::PAREN && token->value == ")"))
		{
			// Parse the next token in the expression
			node->children.push_back(ParseToken(tokens, current));
			token = tokens[(*current)];
		}

		// Increment the current
		(*current)++;

		// Return the node
		return node;
	}

public:
	Node * AST;
};

#endif