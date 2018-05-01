#include <iostream>

#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Emitter.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	string code = "(print \"Hello\" 2)(add 2 (subtract 4 2))";

	Tokenizer t;
	Parser p;
	Emitter e;

	t.Tokenize(code);
	p.ParseProgram(t.tokens);
	cout << e.Emit(p.AST) << endl;

	system("PAUSE");

	return 0;
}