#include "scanner.h"

const vector<string> keywords{ "for", "to", "do" };
const vector<string> delimeters{ ".", ";", "[", "]", "" };
const vector<string> operators{ ":=", "-", "+" };
const vector<string> numericConstants{ "1" };
vector<string> findedID;
vector<string> findedKeywords;
vector<string> findedDelimeters;
vector<string> findedOperators;
vector<string> findedNumericConstants;
vector<string> scannedTokens;

bool ex = false;

void toLower(string token)
{
	for (int i = 0; i < token.size(); i++)
	{
		token[i] = tolower(token[i]);   //������� �� �����
	}
}

bool isID(const string &str)
{
	bool flagLetter = false;
	bool flagDigit = false;

	try
	{
		if (isdigit(str[0])) 
		{
			if (str.size() == 1) 
				return false;
			else
			{
				flagDigit = true;
				ex = true;
				throw (str);
			}
		}

		for (int i = 0; i < str.size(); i++)
		{
			if (ispunct(str[i]))      //������������� �� ����� ��������� ����� ���������� 
			{
				if (str.size() == 1)
					return false;
				else
				{
					ex = true;
					throw (str);
				}
			}
			if (isalpha(str[i]))
				flagLetter = true;
		}
		if (!flagLetter)
		{
			ex = true;
			throw (str);
		}
	}

	catch (const string)
	{
		if (ex)
		{
			ex = false;
			cout << "\nError with '" << str << "'! An identifier cannot contain punctuation marks!" << endl;
		}
		if (flagLetter)
		{
			ex = false;
			cout << "\nError with '" << str <<"'! An identifier must contain a letter!" << endl;
		}
		if (flagDigit)
		{
			ex = false;
			cout << "\nError with '" << str << "'! An identifier cannot start with a number!" << endl;
		}
		return false;
	}

	return true;
}

bool isNumericConstant(const string &str)
{
	bool flag = false;   //���������� ��� ������������ ����� �����������

	for (int i = 0; i < str.size(); i++)
	{
		if (!(isdigit(str[i])))   //����� ������ ��������� ������ �����
		{
			flag = true;
			return false;
		}
	}

	if (!flag)
		for (auto numericConstant : numericConstants)
			if (numericConstant == str)
			{
				flag = true;
				return true;
			}
	try
	{
		if (!flag)
			throw (str);
	}

	catch (const string)
	{
		ex = true;
		cout << "\nError with '"<< str << "'! Number is not a registered numeric constant!" << endl;
		return false;
	}
}

bool isKeyword(const string &str)
{
	toLower(str);

	for (auto keyword : keywords)
		if (keyword == str)
			return true;

	return false;
}

bool isDelimeter(const string &str)
{
	bool flag = false;

	for (int i = 0; i < str.size(); i++)
	{
		if (!(ispunct(str[i])))   //����������� ����� ��������� ������ ����� ����������
		{
			flag = true;
			return false;
		}
	}

	if ((!flag) && (str == ":" || str == "="))   //��������� � ����� �� ����������� � �������� ��������������� ������������, �� �������� ������� ���������������
	{
		flag = true;
		return false;
	}

	if (!flag)
		for (auto delimeter : delimeters)
			if (delimeter == str)
			{
				flag = true;
				return true;
			}
			else flag = true;

	try
	{
		if (!flag)
			throw (str);
	}

	catch (const string)
	{
		ex = true;
		cout << "\nError with '" << str << "'! Delimeter is not a registered delimeter!" << endl;
		return false;
	}

	return false;
}

bool isOperator(const string &str)
{
	bool flag = false;

	for (int i = 0; i < str.size(); i++)
	{
		if (!(ispunct(str[i])))   //�������� ����� ��������� ������ ����� ����������
		{
			flag = true;
			return false;
		}
	}

	if (!flag)
		for (auto oper : operators)
			if (oper == str)
			{
				flag = true;
				return true;
			}
			else flag = true;

	try
	{
		if (!flag)
			throw (str);
	}

	catch (const string)
	{
		ex = true;
		cout << "\nError with '" << str << "'! Operator is not a registered operator!" << endl;
		return false;
	}

	return false;
}

bool isSpace(const string &str)
{
	if (str == " " || str == "\n")
		return true;

	return false;
}

void role(const string& str)
{
	bool flag = false;   //���������� ��� ���������� ���������� ��� �������� ��������
	string bufferStr = str;   //���������� ��� �������� �������� ���������� ������
	string bufferID;   //���������� ��� �������� �������� ���������� ���������������

	if (isKeyword(str))
	{
		for (auto keyword : findedKeywords)
			if (keyword == str)
				flag = true;
		if (!flag)
			findedKeywords.push_back(str);   //���� ���������� �� ���� �������, ������� ������������ � ������ � ���� ����������
		flag = false;
	}
	else if (isDelimeter(str))
	{
		for (auto delimeter : findedDelimeters)
			if (delimeter == str)
				flag = true;
		if (!flag)
			findedDelimeters.push_back(str);
		flag = false;
	}
	else if (isOperator(str))
	{
		for (auto oper : findedOperators)
			if (oper == str)
				flag = true;
		if (!flag)
			findedOperators.push_back(str);
		flag = false;
	}
	else if (isNumericConstant(str))
	{
		for (auto numericConstant : findedNumericConstants)
			if (numericConstant == str)
				flag = true;
		if (!flag)
			findedNumericConstants.push_back(str);
		flag = false;
	}
	else if (isID(str))
	{
		for (int i = 0; i < str.size(); i++)
			bufferStr[i] = tolower(str[i]);

		for (auto ID : findedID)
		{
			bufferID = ID;
			for (int i = 0; i < ID.size(); i++)
				bufferID[i] = tolower(ID[i]);
			if (bufferID == bufferStr)
				flag = true;
		}

		if (!flag)
			findedID.push_back(str);
		flag = false;
	}
	else
	{
		cout << "Invalid token: " << str << endl;
		ex = false;
	}
}

void print()
{
	//����� ������ ������������ ������
	cout << "\n==============\nIDENTIFIERS\n==============\n\n";
	for (auto ID : findedID)
	{
		cout << ID << endl;
	}

	cout << "\n==============\nKEYWORDS\n==============\n\n";
	for (auto keyword : findedKeywords)
	{
		cout << keyword << endl;
	}

	cout << "\n==============\nDELIMETERS\n==============\n\n";
	for (auto delimeter : findedDelimeters)
	{
		cout << delimeter << endl;
	}

	cout << "\n==============\nOPERATORS\n==============\n\n";
	for (auto oper : findedOperators)
	{
		cout << oper << endl;
	}

	cout << "\n==============\nNUMERIC CONSTANTS\n==============\n\n";
	for (auto numericConstant : findedNumericConstants)
	{
		cout << numericConstant << endl;
	}
}

void scan(const string &fileName)
{
	char ch;            //���������� ��� �������� ��������
	string buffer;       //���������� ��� �������� ������������������� ��������

	fstream file(fileName, fstream::in);
	if (!file.is_open())
	{
		cout << "Error while opening the file\n";
		exit(0);
	}
	else
	{
		while (file >> noskipws >> ch)   //������ �������� �� ����� � ������ ��������� ���������� ��������
		{
			if (isSpace(string(1, ch)))  //1 - ������ ������, ch - ������ ��� ���������� �������. � ����� ����������� �� ������ �������
			{
				if (!buffer.empty())   //���� ����� �� ����, ��������� ���������� ������ �� ���������� � ������������� ���������, ����� ���� ����� ����������
				{
					role(buffer);   //����������� ���� �������
					scannedTokens.push_back(buffer);
					buffer = "";   //��������� ������
				}
				continue;
			}

			if (isDelimeter(string(1, ch)) || isDelimeter(buffer))   //���� �������� ������ ��� ���������� ������ �������� ������������
			{
				if (isDelimeter(string(1, ch)) && !isDelimeter(buffer))   //���� �������� ������ �������� ������������, � ���������� ������ - ���, �� ����� ����������� �� ���������� � ��������� � ����������
				{
					if (!buffer.empty())
					{
						role(buffer);
						scannedTokens.push_back(buffer);
						buffer = "";
					}
					role(string(1, ch));
					scannedTokens.push_back(string(1, ch));
					continue;
				}
				else if (!isDelimeter(string(1, ch)) && isDelimeter(buffer))
				{
					role(buffer);
					buffer = "";
				}
				else
				{
					if (!buffer.empty())
					{
						role(buffer);
						scannedTokens.push_back(buffer);
						buffer = "";
					}
					else
					{
						role(string(1, ch));
						scannedTokens.push_back(string(1, ch));
					}
				}
			}

			buffer += ch;   //������������ ������, ������������ ����������
		}

		if (string(1, ch) != ";")
		{
			role(buffer);
			scannedTokens.push_back(buffer);
			buffer = "";
		}

		//print();   //����� ������ ������������ ������
		cout << "Lexical scan is complete." << endl;
	}
	file.close();
}

string getToken(int counter)
{
	return scannedTokens[counter];
}