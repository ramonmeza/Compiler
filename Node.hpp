#ifndef NODE_HPP
#define NODE_HPP
#pragma once

#include <string>

enum NodeType
{
	NIL,
	NUMBERLITERAL,
	STRINGLITERAL
};

class Node
{
public:
	Node()
	{
		type = NodeType::NIL;
		left = nullptr;
		right = nullptr;
	}

	Node(NodeType _type, std::string _value)
	{
		type = _type;
		value = _value;
	}

	~Node()
	{
		delete left;
		left = nullptr;

		delete right;
		right = nullptr;
	}

public:
	NodeType type;
	std::string value;
	
	Node* left;
	Node* right;
};

#endif