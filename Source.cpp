#include <iostream>
#include "Tokenizer.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	Tokenizer t;

	string code = "(add 2 (subtract \"345\" 6))";

	t.Tokenize(code);

	cout << t;

	system("PAUSE");

	return 0;
}