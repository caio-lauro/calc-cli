#include "../include/operator.h"

int get_level_of_priority(const char& c) {
    switch (c) {
        case '+': case '-':
            return 1;
        case '*': case '/': case '%':
            return 2;
        case '^': case 'r':
            return 3;
        case 's': case 'c': case 't':
            return 4;
        case 'l': case 'n':
            return 5;
    }

    return 0;
}

bool is_sqrt(const string& expression, const size_t i) {
    return expression.find("sqrt", i) == i;
}

bool is_log(const string& expression, const size_t i) {
    return expression.find("log", i) == i || expression.find("ln", i) == i;
}

bool is_sin(const string& expression, const size_t i) {
    return expression.find("sin", i) == i;
}

bool is_cos(const string& expression, const size_t i) {
    return expression.find("cos", i) == i;
}

bool is_tan(const string& expression, const size_t i) {
    return expression.find("tan", i) == i;
}

char get_operator_type(const string& expression, const size_t i) {
    switch (expression[i]) {
        case '+': case '-': case '*': case '/': case '%': case '^':
            return expression[i];
        case 's':
            return is_sqrt(expression, i) ? 'r' : (is_sin(expression, i) ? 's' : '\0');
        case 'l':
            return is_log(expression, i) ? (expression[i + 1] == 'o' ? 'l' : 'n') : '\0';
        case 'c':
            return is_cos(expression, i) ? 'c' : '\0';
        case 't':
            return is_tan(expression, i) ? 't' : '\0';
    }

    return '\0';
}