#ifndef SOLVE_H
#define SOLVE_H

#include <iostream>
#include <vector>
#include <variant>
#include <cmath>

using namespace std;

double solve_rpn(const vector<variant<int, double, char>>& rpn_expression);

#endif