#include <algorithm>
#include <iostream>
#include <vector>
#include <variant>
#include <cctype>
#include <cmath>

#define PI 3.14159265359
#define e 2.71828182846

using namespace std;

void replace_different_parentheses(string &expression);
vector<variant<int, double, char>> convert_to_rpn(const string &expression);
double solve_rpn(const vector<variant<int, double, char>>& rpn_expression);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "Usage: calc EXPRESSION\n";
        return 1;
    }

    string expression = "";
    for (int i = 1; i < argc; i++) {
        string part = "";
        
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (argv[i][j] != ' ') part += argv[i][j];
        }

        expression.append(part);
    }

    replace_different_parentheses(expression);

    vector<variant<int, double, char>> rpn_expression = convert_to_rpn(expression);

    /* for (const auto &i : rpn_expression) {
        if (holds_alternative<int>(i)) cout << get<int>(i); 
        else if (holds_alternative<double>(i)) cout << get<double>(i); 
        else if (holds_alternative<char>(i)) cout << get<char>(i); 

        cout << " ";
    }
    cout << endl; */

    double result = solve_rpn(rpn_expression);
    if ((int)result == result) cout << (int)result;
    else cout << result;
    cout << endl;

    return 0;
}

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

void replace_different_parentheses(string &expression) {
    for (char &c : expression) {
        if (c == '{' || c == '[') c = '(';
        else if (c == '}' || c == ']') c = ')'; 
    }
}

int convert_to_int(const string& number) {
    return stoi(number);
}

double convert_to_double(const string& number) {
    return stod(number);
}

bool valid_parentheses(const string &expression) {
    int count = 0;
    for (const char &c : expression) {
        if (c == '(') count++;
        else if (c == ')') {
            if (count == 0) return false;
            count--;
        }
    }

    return count == 0;
}

int get_level_of_priority(const char& c) {
    switch (c) {
        case '+': case '-':
            return 1;
        case '*': case '/': case '%':
            return 2;
        case '^': case 's':
            return 3;
        default:
            return 0;
    }
}

bool is_operator(const char& c) {
    return get_level_of_priority(c) != 0;
}

bool is_sqrt(const string& expression, int i) {
    return expression.find("sqrt") == i;
}

vector<variant<int, double, char>> convert_to_rpn(const string &expression) {
    if (!valid_parentheses(expression)) {
        cout << "Invalid use of parentheses, check and try again.\n";
        exit(1);
    }

    vector<char> operations;
    vector<variant<int, double, char>> rpn_expression;
    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            string number = "";
            while (isdigit(expression[i]) || expression[i] == '.') {
                number += expression[i++];
            }

            int point_count = count(number.begin(), number.end(), '.');
            if (point_count == 0) {
                rpn_expression.push_back(convert_to_int(number));
            } else if (point_count == 1) {
                rpn_expression.push_back(convert_to_double(number));
            } else {
                cout << "Weird syntax, try again.\n";
                exit(1);
            }
        }
        
        if (expression[i] == 'p' || expression[i] == 'P') {
            if (i < expression.size() - 1 && (expression[i + 1] == 'i' || expression[i + 1] == 'I')) {
                rpn_expression.push_back(PI);
                i += 2;
            } else {
                cout << "Invalid expression, maybe you wanted to type pi?\n";
                exit(1);
            }
        }

        if (expression[i] == 'e' || expression[i] == 'E') {
            rpn_expression.push_back(e);
            i++;
        }
        
        if (i >= expression.length()) break;

        if (expression[i] == '(') {
            operations.push_back(expression[i]);
        } else if (expression[i] == ')') {
            while (operations.size() > 0 && operations.back() != '(') {
                rpn_expression.push_back(operations.back());
                operations.pop_back();
            }
            operations.pop_back();
        } else if (is_operator(expression[i]) || is_sqrt(expression, i)) {
            while (operations.size() > 0 && get_level_of_priority(operations.back()) >= get_level_of_priority(expression[i])) {
                rpn_expression.push_back(operations.back());
                operations.pop_back();
            }
            operations.push_back(expression[i]);
            if (expression[i] == 's') i += 3;
        } else {
            cout << "Invalid character " << expression[i] << " in expression.\n";
            exit(1);
        }
    }

    while (operations.size() > 0) {
        rpn_expression.push_back(operations.back());
        operations.pop_back();
    }

    return rpn_expression;
}