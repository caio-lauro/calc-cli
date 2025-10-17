#include <iostream>

#include "../include/expression.h"
#include "../include/convert.h"
#include "../include/solve.h"

#define COUT_PRECISION 10

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "Usage: calc EXPRESSION\n";
        return 1;
    }

    string expression = get_expression(argc, argv);
    vector<variant<int, double, char>> rpn_expression = convert_to_rpn(expression);

    double result = solve_rpn(rpn_expression);
    if ((int)result == result) { 
        cout << (int)result;
    } else {
        cout.precision(COUT_PRECISION);
        cout << result;
    }

    cout << endl;

    return 0;
}