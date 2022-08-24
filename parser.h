#ifndef _PARSER_H_

#include <stdlib.h>
#include <stdbool.h>
enum {
    ERROR = -1,
    SUCCESS = 0
};

enum TOKEN_TYPE {
    NUMERAL = 2,
    ADD = 4,
    SUBSTRACT = 8,
    MULTIPLY = 16,
    DIVIDE = 32,
    PARENTHESIS = 64
};

typedef struct Token Token;
struct Token {
    enum TOKEN_TYPE type;
    char* repr;
};

Token* token_new(char* repr);
bool isoperator(char op);

int convert_operator_to_type(char op);

char* validate(char* expression);
char* parse(char* expression);
int evaluate(char* expression);

#endif // !_PARSER_H_
