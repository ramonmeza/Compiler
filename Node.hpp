#ifndef NODE_HPP
#define NODE_HPP
#pragma once

#include <string>
#include <vector>

class Node
{
public:
	enum Type
	{
		NIL,
		PROGRAM,
		NUMBERLITERAL,
		STRINGLITERAL,
		CALLEXPRESSION
	};

public:
	Node()
	{
		type = Node::Type::NIL;
	}

	Node(Node::Type _type, std::string _value)
	{
		type = _type;
		value = _value;
	}

	~Node()
	{
		for (auto itr = children.begin(); itr != children.end(); itr++)
		{
			delete (*itr);
			(*itr) = nullptr;
		}

		children.clear();
	}

	friend std::ostream& operator<<(std::ostream& os, const Node& n)
	{
		os << "Object {" << std::endl;
		os << "\ttype: ";

		switch (n.type)
		{
		case Node::Type::PROGRAM:
			os << "PROGRAM" << std::endl;
			break;
		case Node::Type::NUMBERLITERAL:
			os << "NUMBERLITERAL" << std::endl;
			break;
		case Node::Type::STRINGLITERAL:
			os << "STRINGLITERAL" << std::endl;
			break;
		case Node::Type::CALLEXPRESSION:
			os << "CALLEXPRESSION" << std::endl;
			break;
		default:
			break;
		}

		os << "\tvalue: " << n.value << std::endl;

		os << "\tchildren:" << std::endl;

		for (auto itr = n.children.begin(); itr != n.children.end(); itr++)
		{
			os << *(*itr);
		}

		os << "}" << std::endl;

		return os;
	}

public:
	Node::Type type;
	std::string value;

	std::vector<Node*> children;
};

#endif