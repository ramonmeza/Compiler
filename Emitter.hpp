#ifndef EMITTER_HPP
#define EMITTER_HPP

#include <stdexcept>
#include <string>

#include "Node.hpp"

class Emitter
{
public:
	Emitter()
	{
	}

	~Emitter()
	{
	}

	// Emitter dispatcher
	std::string Emit(Node* node)
	{
		switch (node->type)
		{
		case Node::Type::PROGRAM:
			return EmitProgram(node);
			break;
		case Node::Type::CALLEXPRESSION:
			return EmitExpression(node);
			break;
		case Node::Type::NUMBERLITERAL:
			return EmitNumber(node);
			break;
		case Node::Type::STRINGLITERAL:
			return EmitString(node);
			break;
		default:
			throw std::invalid_argument("Unknown node type.");
			break;
		}
	}

	// Emit a number
	std::string EmitNumber(Node* node)
	{
		return node->value;
	}

	// Emit a string
	std::string EmitString(Node* node)
	{
		return "\\\"" + node->value + "\\\"";
	}

	// Emit a program
	std::string EmitProgram(Node* node)
	{
		// String to build and return
		std::string temp;

		// Emit each node in the program
		for (auto itr = node->children.begin(); itr != node->children.end(); itr++)
		{
			temp.append(Emit((*itr)));
			temp.append(";");
			temp.append("\n");
		}

		return temp;
	}

	// Emit an expression
	std::string EmitExpression(Node* node)
	{
		// String to build and return
		std::string temp;

		// Expression name
		temp.append(node->value);
		temp.append("(");

		// Add the parameters to the expression
		for (auto itr = node->children.begin(); itr != node->children.end(); itr++)
		{
			temp.append(Emit((*itr)));

			// Don't add comma on last parameter
			if ((*itr) != node->children.back())
			{
				temp.append(", ");
			}
		}

		// Closing parenthesis
		temp.append(")");

		return temp;
	}
};

#endif