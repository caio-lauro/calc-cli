#include "../include/solve.h"

pair<double, double> get_operands(vector<double>& stack) {
    const auto x = stack.back();
    stack.pop_back();
    const auto y = stack.back();
    stack.pop_back();
    return {x, y};
}

double solve_rpn(const vector<variant<int, double, char>>& rpn_expression) {
    vector<double> stack;
    for (const auto &token : rpn_expression) {
        if (holds_alternative<double>(token)) 
            stack.push_back(get<double>(token));
        else if (holds_alternative<int>(token))
            stack.push_back((double) get<int>(token));
        else {
            char c = get<char>(token);
            
            if (c == 's' && stack.size() == 1) {
                const auto back = stack.back();
                stack.pop_back();
                stack.push_back(sqrt(back));
                continue;
            }

            if (c == 'l' && stack.size() == 1) {
                const auto back = stack.back();
                stack.pop_back();
                stack.push_back(log10(back));
                continue;
            }
            
            if (c == 'n' && stack.size() == 1) {
                const auto back = stack.back();
                stack.pop_back();
                stack.push_back(log(back));
                continue;
            }

            if (c == '-' && stack.size() == 1) {
                const auto back = stack.back();
                stack.pop_back();
                stack.push_back(-back);
                continue;
            }

            if (stack.size() < 2) {
                cout << "That seems wrong...\n";
                exit(1);
            }

            auto [y, x] = get_operands(stack);
            if (c == '+') {
                stack.push_back(x + y);
            } else if (c == '-') {
                stack.push_back(x - y);
            } else if (c == '*') {
                stack.push_back(x * y);
            } else if (c == '/') {
                stack.push_back(x / y);
            } else if (c == '%') {
                if ((int)x != x || (int)y != y) {
                    cout << "You shouldn't try the modulo with anything other than an integer.\n";
                    exit(1);
                }

                stack.push_back((int)x % (int)y);
            } else if (c == '^') {
                stack.push_back(pow(x, y));
            }
        }
    }

    if (stack.size() > 1) {
        cout << "Something went wrong when trying to calculate the expression.\n";
        exit(1);
    }

    return stack.back();
}