#ifndef _STACK_H_

#include<stdbool.h>
typedef struct Stack Stack;
#define byte char
#define DEFAULT_SIZE 16
enum {
    OK,
    STACK_FULL,
    STACK_EMPTY = -1
};

struct Stack
{
    int top;
    void* data;
    int totalElements;
    int memberSize;
};

Stack* stack_new(int memberSize, int totalElements);
int stack_push(Stack* stack, void* element);
int stack_pop(Stack* stack, void* target);
int stack_top(Stack* stack, void* target);
bool stack_empty(Stack* stack);

int stack_free(Stack* stack);
#endif // !_STACK_H_
