#include <iostream>

#include "Compiler.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	string code = "(add 1 2 (mult 3 4))";

	Compiler compiler;

	cout << compiler.Compile(code) << endl;

	system("PAUSE");

	return 0;
}