#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>

using namespace std;

int get_level_of_priority(const char& c);
char get_operator_type(const string& expression, const size_t i);

#endif