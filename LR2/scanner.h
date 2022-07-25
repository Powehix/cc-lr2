#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void toLower(string token);
bool isID(const string &str);
bool isNumericConstant(const string &str);
bool isKeyword(const string &str);
bool isDelimeter(const string &str);
bool isOperator(const string &str);
bool isSpace(const string &str);
void role(const string &token);
void print();
void scan(const string &file);
string getToken(int counter);
