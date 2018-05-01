#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#pragma once

#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "Token.hpp"

class Tokenizer
{
public:
	Tokenizer()
	{
	}

	~Tokenizer()
	{
		ClearTokens();
	}

	friend std::ostream& operator<<(std::ostream& os, const Tokenizer& t)
	{
		if (!t.tokens.empty())
		{
			for (auto itr = t.tokens.begin(); itr != t.tokens.end(); itr++)
			{
				os << "Object {" << std::endl;

				os << "\t";
				switch ((*itr)->type)
				{
				case Token::Type::NIL:
					os << "type: NIL";
					break;
				case Token::Type::PAREN:
					os << "type: PAREN";
					break;
				case Token::Type::NUM:
					os << "type: NUM";
					break;
				case Token::Type::NAME:
					os << "type: NAME";
					break;
				case Token::Type::STRING:
					os << "type: STRING";
					break;
				default:
					break;
				}

				os << std::endl << "\tvalue: " << (*itr)->value << std::endl;
				os << "}" << std::endl;
			}
		}

		return os;
	}

	void ClearTokens()
	{
		if (!tokens.empty())
		{
			for (auto itr = tokens.begin(); itr != tokens.end(); itr++)
			{
				delete (*itr);
				(*itr) = nullptr;
			}

			tokens.clear();
		}
	}

	void Tokenize(std::string const& input)
	{
		// Clear the tokens
		ClearTokens();

		// Keep track of where we are in the input
		int current = 0;

		// Go through the input one character at a time
		while (current < (int)input.length())
		{
			// Counts the number of characters read from the input
			int consumedCharacters = 1;

			// Skip whitespace
			if (!IsWhitespace(input, current))
			{
				// Create a pointer to store token in
				Token* tok = nullptr;

				// Find the correct token
				if ((tok = TokenizeParenOpen(input, current)) != nullptr)
				{
					consumedCharacters = 1;
				}
				else if ((tok = TokenizeParenClose(input, current)) != nullptr)
				{
					consumedCharacters = 1;
				}
				else if ((tok = TokenizeString(input, current)) != nullptr)
				{
					// Add to to account for the opening and closing "
					consumedCharacters = tok->length + 2;
				}
				else if ((tok = TokenizeNumber(input, current)) != nullptr)
				{
					consumedCharacters = tok->length;
				}
				else if ((tok = TokenizeName(input, current)) != nullptr)
				{
					consumedCharacters = tok->length;
				}
				else
				{
					throw std::invalid_argument("Unknown character.");
				}

				// Add the token to the tokens vector
				tokens.push_back(tok);
			}

			// Increment the current
			current += consumedCharacters;
		}
	}

public:
	// Holds the tokens
	std::vector<Token*> tokens;

private:
	// Generic function that tokenizes a single character
	Token * TokenizeCharacter(Token::Type type, std::string value, std::string const& input, int current)
	{
		// If the input matches the value
		if (input.substr(current, 1) == value)
		{
			// Create a token to return
			Token* tok = new Token(type, value);
			return tok;
		}

		return nullptr;
	}

	// Tokenizer for open parenthesis (
	Token* TokenizeParenOpen(std::string const& input, int current)
	{
		return TokenizeCharacter(Token::Type::PAREN, "(", input, current);
	}

	// Tokenizer for open parenthesis (
	Token* TokenizeParenClose(std::string const& input, int current)
	{
		return TokenizeCharacter(Token::Type::PAREN, ")", input, current);
	}

	// Multiple character tokens
	Token* TokenizePattern(Token::Type type, std::string pattern, std::string const& input, int current)
	{
		// Get the first character of the input
		std::string character = input.substr(current, 1);

		// Use this to keep track of the size of the value
		int consumedCharacters = 0;

		// Regex
		std::regex r(pattern);

		if (std::regex_match(character, r))
		{
			// Store the value of the token
			std::string tokenValue;

			while (std::regex_match(character, r))
			{
				// Append the character to the token value
				tokenValue.append(character);

				// Increment the count
				consumedCharacters++;

				// Get the next character in the input to test
				character = input.substr(current + consumedCharacters, 1);
			}

			// Create a token to return
			Token* tok = new Token(type, tokenValue);
			return tok;
		}

		return nullptr;
	}

	// Tokenizer for numbers
	Token* TokenizeNumber(std::string const& input, int current)
	{
		return TokenizePattern(Token::Type::NUM, "[0-9]", input, current);
	}

	// Tokenizer for names
	Token* TokenizeName(std::string const& input, int current)
	{
		return TokenizePattern(Token::Type::NAME, "[A-Za-z]", input, current);
	}

	// Tokenizer for strings
	Token* TokenizeString(std::string const& input, int current)
	{
		// Strings must start with "
		if (input[current] == '"')
		{
			// Move the input to the next character to check
			int consumedCharacters = 1;
			char character = input[current + consumedCharacters];

			// Use to build up string for token's value
			std::string tokenValue = "";

			// Loop until end of string is found
			while (character != '"')
			{
				// If there is no end of the string
				if (character == input.back())
				{
					throw std::invalid_argument("Unterminated string.");
				}

				// Add the character to the value
				tokenValue += character;

				// Move to the next character
				consumedCharacters++;
				character = input[current + consumedCharacters];
			}

			// Create a token to return
			Token* tok = new Token(Token::Type::STRING, tokenValue);
			return tok;
		}

		return nullptr;
	}

	// Skip whitespace
	bool IsWhitespace(std::string const& input, int current)
	{
		return (input.substr(current, 1) == " ") ? true : false;
	}
};

#endif