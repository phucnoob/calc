#include "parser.h"
#include "lib/stack.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

bool isoperator(char op)  {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}


size_t operator_precedence(char ch) {
    switch (ch) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case '^':
            return 3;
        
        default:
            return 0;
    }
}

static bool is_valid_char(char ch) {
    return isoperator(ch) || ('0' <= ch && ch <= '9') || ch == '(' || ch ==  ')';
}

static char* str_from_char(char ch) {
    char* str =  malloc(2 * (sizeof(char)));
    str[0] = ch;
    str[1] = '\0';

    return str;
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

char** parse(char *expression, size_t *length) {
    // 1 + 2 + 3 * 4
    int str_len = strlen(expression);
    char** polish_exp = malloc( MAX_TOKEN * (sizeof(char*)));

    Stack *op_stack = stack_new(sizeof(char), DEFAULT_SIZE);
    size_t index = 0;


    for (size_t i = 0; i < str_len; i++)
    {

        if (isdigit(expression[i])) {
            int len = 0;
            while (isdigit(expression[i + len])) {
                len++;
            }
            polish_exp[index++] = strndup(expression + i, len);
            i += len - 1;
            continue;
        }

        if (isoperator(expression[i])) {
            while (!stack_empty(op_stack)) {
                char tmp = '\0';
                stack_top(op_stack, &tmp);

                if (tmp == '(') {
                    break;
                }

                if (operator_precedence(tmp) >= operator_precedence(expression[i])) {
                    stack_pop(op_stack, &tmp);
                    polish_exp[index++] = str_from_char(tmp);
                } else {
                    break;
                }
            }

            stack_push(op_stack, &expression[i]);
            continue;
        }

        if (expression[i] == '(') {
            stack_push(op_stack, &expression[i]);
            continue;
        }

        if (expression[i] == ')') {
            while (!stack_empty(op_stack)) {
                char top = 0;
                stack_top(op_stack, &top);

                if (top == '(') {
                    break;
                }

                stack_pop(op_stack, &top);
                polish_exp[index++] = str_from_char(top);
            }

            char tmp = '\0';
            stack_pop(op_stack, &tmp);
        }
    }

    while (!stack_empty(op_stack)) {
        char tmp = '\0';
        stack_pop(op_stack, &tmp);

        polish_exp[index++] = str_from_char(tmp);
    }

    *length = index;
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

static int eval_pow(int a, int b) {

    if (b == 0) {
        return 1;
    }

    if (b == 1) {
        return a;
    }

    int tmp = eval_pow(a, b / 2);
    if ((b & 1) == 0) {
        return tmp * tmp;
    } else {
        return a * tmp * tmp;
    }
}

int evaluate(char** expression, size_t len) {
    Stack *stack = stack_new(sizeof(int), DEFAULT_SIZE);

    for (int i = 0; i < len; i++) {
        if (isoperator(expression[i][0])) {

            int num1 = 0;
            int num2 = 0;
            stack_pop(stack, &num2);
            stack_pop(stack, &num1);
            printf("%d %c %d\n", num1, expression[i][0], num2);
            int result = 0;

            switch (expression[i][0]) {
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
                case '^':
                    result = eval_pow(num1, num2);
                    break;

                default:
                    break;
            }

            stack_push(stack, &result);
        } else {
            int int_val = atoi(expression[i]);
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
    char exp[1024] = "3 + 4 * 2 / ( 1 - 5 )";

    scanf("%1023[^\n]", exp);
    char* valid = validate(exp);

    printf("Validate: %s\n", valid);

    size_t len = 0;
    char** po = parse(valid, &len);

    for (int i = 0; i < len; i++) {
        printf("'%s', ", po[i]);
    }

    printf("\n");

    int ans = evaluate(po, len);

    printf("%d\n", ans);
    return 0;
}