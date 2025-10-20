#include <iostream>

#include "../include/expression.h"
#include "../include/convert.h"
#include "../include/solve.h"

#define COUT_PRECISION 10
#define EPSILON 1e-8f

using namespace std;

bool isApproximatelyInteger(float x) { return abs(x - (int)x) <= EPSILON; }

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "Usage: calc EXPRESSION\n";
        return 1;
    }

    const string expression = get_expression(argc, argv);
    const vector<variant<int, double, char>> rpn_expression = convert_to_rpn(expression);

    const double result = solve_rpn(rpn_expression);

    cout.precision(COUT_PRECISION);
    cout << (isApproximatelyInteger(result) ? (int)result : result) << endl;

    return 0;
}