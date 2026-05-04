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
    auto apply_unary = [&](double (*fn)(double)) {
        stack.back() = fn(stack.back());
    };
    
    for (const auto &token : rpn_expression) {
        if (holds_alternative<double>(token)) 
            stack.push_back(get<double>(token));
        else if (holds_alternative<int>(token))
            stack.push_back((double) get<int>(token));
        else {
            char c = get<char>(token);
            
            switch (c) {
                case 'r': 
                    apply_unary(sqrt); 
                    continue;
                case 'l': 
                    apply_unary(log10);
                    continue;
                case 'n': 
                    apply_unary(log);
                    continue;
                case 's': 
                    apply_unary(sin);
                    continue;
                case 'c': 
                    apply_unary(cos);
                    continue;
                case 't': 
                    apply_unary(tan);
                    continue;
                case 'u': 
                    apply_unary([](double x){ return -x; }); 
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
        for (auto x : stack) {
            cout << x << ' ';
        }
        cout << '\n';
        cout << "Something went wrong when trying to calculate the expression.\n";
        exit(1);
    }

    return stack.back();
}