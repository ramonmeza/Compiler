#include <iostream>
#include <string>

#include "Compiler.hpp"

int main(int argc, char *argv[])
{
	const std::string code = "(add 1 2 (mult 3 4))";

	Compiler compiler;

	std::cout << code << " = " << compiler.Compile(code) << std::endl;

	return 0;
}