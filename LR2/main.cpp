#include "scanner.h"
#include "parser.h"

void main()
{
	cout << "Lexical scan...\n";
	scan("code.txt");
	cout << "Parsing... \n";
	parser();
	system("PAUSE");
}