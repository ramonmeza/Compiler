#ifndef TOKEN_HPP
#define TOKEN_HPP
#pragma once

#include <string>

enum TokenType
{
	NIL,
	PAREN,
	NUM,
	NAME,
	STRING
};

class Token
{
public:
	Token()
	{
		length = 0;
		type = TokenType::NIL;
		value = nullptr;
	}

	Token(TokenType _type, std::string _value)
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
	TokenType type;
	std::string value;
};

#endif