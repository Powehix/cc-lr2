#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool state(string currentToken);
bool var(string token);
bool exp(string token);
bool term(string token);
void parser();
