#include "scanner.h"
#include "parser.h"

int counter = 0;
bool isState = false;
string msg;
bool exc = false;

bool state(string currentToken)
{
	toLower(currentToken);

	try
	{
		if (currentToken == "for")
		{
			isState = true;
			counter++;
			currentToken = getToken(counter);
			state(currentToken);
			currentToken = getToken(counter);
			toLower(currentToken);
			if (currentToken == "to")
			{
				counter++;
				currentToken = getToken(counter);
				exp(currentToken);
				currentToken = getToken(counter);
				toLower(currentToken);
				if (currentToken == "do")
				{
					counter++;
					currentToken = getToken(counter);
					state(currentToken);
					isState = false;
					return true;
				}
				else
				{				
					msg = "Error! Missing 'do'!\n";
					throw (msg);
				}
			}
			else
			{
				msg = "Error! Mssing 'to'!\n";
				throw (msg);
			}
		}
		else if (isState)
		{
			var(currentToken);
			currentToken = getToken(counter);
			if (currentToken == ":=")
			{
				counter++;
				currentToken = getToken(counter);
				exp(currentToken); 
				//return true;
			}
			else
			{
				msg = "Error! Missing ':='!\n";
				throw (msg);
			}
		}
		else
		{
			msg = "Error! Missing 'for'!\n";
			throw (msg);
		}
	}

	catch (string)
	{
		cout << msg;
		exc = true;
		return false;
	}
}

bool var(string token)
{
	toLower(token);

	try
	{
		if (isID(token))
		{
			counter++;
			token = getToken(counter);
			if (token == "[")
			{
				counter++;
				token = getToken(counter);
				var(token);
				token = getToken(counter);
				if (token == "]")
				{
					return true;
				}
				else
				{
					msg = "Error! Missing ']'!\n";
					throw (msg);
				}
			}
			else if (token == ".")
			{
				counter++;
				token = getToken(counter);
				var(token);
				return true;
			}
			else return true;
		}
		else if (isNumericConstant(token))
			return false;
		else
		{
			msg = "Error! Missing identifier!\n";
			throw (msg);
		}
	}

	catch (string)
	{
		cout << msg;
		exc = true;
		return false;
	}
}

bool exp(string token)
{
	try
	{
		term(token);
		token = getToken(counter);
		if (isOperator(token))
		{
			counter++;
			token = getToken(counter);
			term(token);
			return true;
		}
		else if (token == "to" || token == "do")
			return false;
		else
		{
			msg = "Error! Missing operator!\n";
			throw (msg);
		}
	}

	catch (string)
	{
		cout << msg;
		exc = true;
		return false;
	}
}

bool term(string token)
{
	if (var(token))
		return true;
	else if (isNumericConstant(token))
	{
		counter++;
		return true;
	}
	else return false;
}

void parser()
{
	string currentToken = getToken(counter);

	state(currentToken);

	if (!exc)
		cout << "Parsing is successful.\n";
	else cout << "Error with parsing.\n";
}