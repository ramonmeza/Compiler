#ifndef TOKEN_HPP
#define TOKEN_HPP
#pragma once

#include <string>

class Token
{
public:
	enum Type
	{
		NIL,
		PAREN,
		NUM,
		NAME,
		STRING
	};

public:
	Token()
	{
		length = 0;
		type = Token::Type::NIL;
		value = nullptr;
	}

	Token(Token::Type _type, std::string _value)
	{
		length = _value.length();
		type = _type;
		value = _value;
	}

	~Token()
	{
	}

public:
	// Properties
	int length;
	Token::Type type;
	std::string value;
};

#endif