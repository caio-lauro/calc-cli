#include "../include/convert.h"
#include "../include/constants.h"

bool valid_parentheses(const string &expression);
int get_level_of_priority(const char& c);
bool is_operator(const char& c);
bool is_sqrt(const string& expression, size_t i);
bool is_log(const string& expression, size_t i);

vector<variant<int, double, char>> convert_to_rpn(const string &expression) {
    if (!valid_parentheses(expression)) {
        cout << "Invalid use of parentheses, check and try again.\n";
        exit(1);
    }

    vector<char> operations;
    vector<variant<int, double, char>> rpn_expression;
    for (size_t i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            string number = "";
            while (isdigit(expression[i]) || expression[i] == '.') {
                number += expression[i++];
            }

            int point_count = count(number.begin(), number.end(), '.');
            if (point_count == 0) {
                rpn_expression.push_back(stoi(number));
            } else if (point_count == 1) {
                rpn_expression.push_back(stod(number));
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
        } else if (is_operator(expression[i]) || is_sqrt(expression, i) || is_log(expression, i)) {
            while (operations.size() > 0 && get_level_of_priority(operations.back()) >= get_level_of_priority(expression[i])) {
                rpn_expression.push_back(operations.back());
                operations.pop_back();
            }

            if (expression[i + 1] != 'n') {
                operations.push_back(expression[i]);
                if (expression[i] == 's') i += 3;
                else if (expression[i] == 'l') i += 2;
            } else {
                operations.push_back(expression[i + 1]);
                i++;
            }
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

bool is_sqrt(const string& expression, size_t i) {
    return expression.find("sqrt", i) == i;
}

bool is_log(const string& expression, size_t i) {
    return expression.find("log", i) == i || expression.find("ln", i) == i;
}