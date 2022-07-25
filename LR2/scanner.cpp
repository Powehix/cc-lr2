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
		token[i] = tolower(token[i]);   //регистр не важен
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
			if (ispunct(str[i]))      //идентификатор не может содержать знаки пунктуации 
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
	bool flag = false;   //переменная для переключения между состояниями

	for (int i = 0; i < str.size(); i++)
	{
		if (!(isdigit(str[i])))   //число должно содержать только цифры
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
		if (!(ispunct(str[i])))   //разделитель может содержать только знаки пунктуации
		{
			flag = true;
			return false;
		}
	}

	if ((!flag) && (str == ":" || str == "="))   //двоеточие и равно не встречаются в качестве однопозиционных разделителей, но являются частями двухпозиционных
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
		if (!(ispunct(str[i])))   //оператор может содержать только знаки пунктуации
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
	bool flag = false;   //переменная для нахождения совпадений при переборе векторов
	string bufferStr = str;   //переменная для проверки регистра подаваемой строки
	string bufferID;   //переменная для проверки регистра хранящихся идентификаторов

	if (isKeyword(str))
	{
		for (auto keyword : findedKeywords)
			if (keyword == str)
				flag = true;
		if (!flag)
			findedKeywords.push_back(str);   //если совпадение не было найдено, лексема записывается в вектор и флаг опускается
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
	//вывод таблиц распознанных лексем
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
	char ch;            //переменная для хранения символов
	string buffer;       //переменная для хранения последовательностей символов

	fstream file(fileName, fstream::in);
	if (!file.is_open())
	{
		cout << "Error while opening the file\n";
		exit(0);
	}
	else
	{
		while (file >> noskipws >> ch)   //чтение символов из файла с учетом начальных пробельных символов
		{
			if (isSpace(string(1, ch)))  //1 - размер строки, ch - символ для заполнения размера. В буфер добавляется по одному символу
			{
				if (!buffer.empty())   //если буфер не пуст, проверяет содержимое буфера на совпадение с существующими лексемами, после чего буфер обнуляется
				{
					role(buffer);   //определение типа лексемы
					scannedTokens.push_back(buffer);
					buffer = "";   //обнуление буфера
				}
				continue;
			}

			if (isDelimeter(string(1, ch)) || isDelimeter(buffer))   //если входящий символ или содержимое буфера является разделителем
			{
				if (isDelimeter(string(1, ch)) && !isDelimeter(buffer))   //если входящий символ является разделителем, а содержимое буфера - нет, то буфер проверяется на совпадение с лексемами и обнуляется
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

			buffer += ch;   //формирование буфера, посимвольное добавление
		}

		if (string(1, ch) != ";")
		{
			role(buffer);
			scannedTokens.push_back(buffer);
			buffer = "";
		}

		//print();   //вывод таблиц распознанных лексем
		cout << "Lexical scan is complete." << endl;
	}
	file.close();
}

string getToken(int counter)
{
	return scannedTokens[counter];
}