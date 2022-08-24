#include "parser.h"
#include "lib/stack.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

Token* token_new(char* repr) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->repr = repr;

    return token;
}

bool isoperator(char op)  {
    return op == '+' || op == '-' || op == '*' || op == '/';
}


int convert_operator_to_type(char op) {
    if (isoperator(op)) {
        switch (op) {
            case '+':
                return ADD;
            case '-':
                return SUBSTRACT;
            case '*':
                return MULTIPLY;
            case '/':
                return DIVIDE;

            default:
                return NUMERAL;
        }
    }

    return ERROR;
}

static bool is_valid_char(char ch) {
    return isoperator(ch) || ('0' <= ch && ch <= '9');
}

char* validate(char* expression) {
    int str_len = strlen(expression);
    char* str = malloc(str_len + 1);
    int index = 0;
    
    for (int i = 0; i < str_len; i++) {
        if (is_valid_char(expression[i])) {
            str[index++] = expression[i];
        }
    }

    str[index] = '\0';

    return str;
}
char* parse(char *expression) {
    // 1 + 2 + 3 * 4
    int str_len = strlen(expression);
    char* polish_exp = malloc(str_len + 1);
    Stack *op_stack = stack_new(sizeof(char), DEFAULT_SIZE);
    int index = 0;


    for (size_t i = 0; i < str_len; i++)
    {
        if (isdigit(expression[i])) {
            polish_exp[index++] = expression[i];
        } else if (isoperator(expression[i])) {
            stack_push(op_stack, &expression[i]);
        }
    }

    while (!stack_empty(op_stack)) {
        char tmp = '\0';
        stack_pop(op_stack, &tmp);

        polish_exp[index++] = tmp;
    }

    polish_exp[index] = '\0';

    return polish_exp;
}

static int eval_add(int a, int b) {
    return a + b;
}

static int eval_subtract(int a, int b) {
    return a - b;
}

static int eval_multiply(int a, int b) {
    return a * b;
}

static int eval_divide(int a, int b) {
    return a / b;
}

int evaluate(char* expression) {
    Stack *stack = stack_new(sizeof(int), DEFAULT_SIZE);
    int str_len = strlen(expression);

    for (int i = 0; i < str_len; i++) {
        if (isoperator(expression[i])) {

            int num1 = 0;
            int num2 = 0;
            stack_pop(stack, &num1);
            stack_pop(stack, &num2);
            printf("%d %d\n", num1, num2);
            int result = 0;

            switch (expression[i]) {
                case '+':
                    result = eval_add(num1, num2);
                    break;
                case '-':
                    result = eval_subtract(num1, num2);
                    break;
                case '*':
                    result = eval_multiply(num1, num2);
                    break;
                case '/':
                    result = eval_divide(num1, num2);
                    break;
            }

            stack_push(stack, &result);
        } else {
            int int_val = expression[i] - '0';
            stack_push(stack, &int_val);
        }
    }

    int result = 0;
    stack_pop(stack, &result);
    stack_free(stack);

    return result;
}

#include <stdio.h>
int main() {
    char exp[1024];

    scanf("%1023[^\n]", exp);
    char* valid = validate(exp);

    printf("Validate: %s\n", valid);

    char* po = parse(valid);
    printf("%s\n", po);
    int ans = evaluate(po);

    printf("%d\n", ans);
    return 0;
}