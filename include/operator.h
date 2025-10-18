#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>

using namespace std;

int get_level_of_priority(const char& c);
bool is_operator(const char& c);
bool is_sqrt(const string& expression, size_t i);
bool is_log(const string& expression, size_t i);


#endif