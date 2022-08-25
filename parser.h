#include <stddef.h>
#ifndef _PARSER_H_

#include <stdlib.h>
#include <stdbool.h>

#define MAX_TOKEN 1024

bool isoperator(char op);
bool isparenthesis(char* ch);

size_t operator_precedence(char ch);

int convert_operator_to_type(char op);

char* validate(char* expression);
char** parse(char* expression, size_t *length);
int evaluate(char** expression, size_t len);

#endif // !_PARSER_H_
