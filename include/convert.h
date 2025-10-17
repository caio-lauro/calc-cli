#ifndef CONVERT_H
#define CONVERT_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <variant>
#include <cctype>

using namespace std;

vector<variant<int, double, char>> convert_to_rpn(const string &expression);

#endif