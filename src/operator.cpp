#include "../include/operator.h"

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

bool is_sqrt(const string& expression, const size_t i) {
    return expression.find("sqrt", i) == i;
}

bool is_log(const string& expression, const size_t i) {
    return expression.find("log", i) == i || expression.find("ln", i) == i;
}