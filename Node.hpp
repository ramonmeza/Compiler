#ifndef NODE_HPP
#define NODE_HPP

#include <ostream>
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
		auto  itr = children.begin();
		while (itr != children.end())
		{
			itr = children.erase(itr);
		}

		children.clear();
	}

	friend std::ostream& operator<<(std::ostream& os, const Node& n)
	{
		os << "Object {\n\ttype: ";

		switch (n.type)
		{
		case Node::Type::PROGRAM:
			os << "PROGRAM" << "\n";
			break;
		case Node::Type::NUMBERLITERAL:
			os << "NUMBERLITERAL" << "\n";
			break;
		case Node::Type::STRINGLITERAL:
			os << "STRINGLITERAL" << "\n";
			break;
		case Node::Type::CALLEXPRESSION:
			os << "CALLEXPRESSION" << "\n";
			break;
		default:
			break;
		}

		os << "\tvalue: " << n.value << "\n";

		os << "\tchildren:" << "\n";

		for (auto itr = n.children.begin(); itr != n.children.end(); itr++)
		{
			os << *(*itr);
		}

		os << "}" << "\n";

		return os;
	}

public:
	Node::Type type;
	std::string value;

	std::vector<Node*> children;
};

#endif