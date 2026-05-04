#include "../include/convert.h"
#include "../include/operator.h"
#include "../include/constants.h"

bool valid_parentheses(const string &expression);

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
        } else {
            const char operator_type = get_operator_type(expression, i);
            if (operator_type == '\0') {
                cout << "Invalid character " << expression[i] << " in expression.\n";
                exit(1);
            }

            const int operator_priority = get_level_of_priority(operator_type);
            const int right_associative = (operator_type == 'u' || operator_type == '^') ? 1 : 0;
            while (!operations.empty() && 
                get_level_of_priority(operations.back()) >= operator_priority + right_associative) 
            {
                rpn_expression.push_back(operations.back());
                operations.pop_back();
            }
            operations.push_back(operator_type);

            switch (operator_type) {
                case 'r':
                    i += 3;
                    break;
                
                case 'l': case 's': case 'c': case 't':
                    i += 2;
                    break;

                case 'n':
                    i++;
                    break;
            }
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