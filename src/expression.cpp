#include "../include/expression.h"

char replace_different_parentheses(const char c) {
    if (c == '{' || c == '[') 
        return '(';
    if (c == '}' || c == ']')
        return ')';
    return c;
}

string get_expression(int argc, char *argv[]) {
    string expression = "";
    for (int i = 1; i < argc; i++) {
        string part = "";
        
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (argv[i][j] != ' ')
                part += replace_different_parentheses(argv[i][j]);
        }

        expression.append(part);
    }
    
    return expression;
}