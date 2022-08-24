#include "stack.h"
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


Stack* stack_new(int memberSize, int totalElements) {
    Stack *stack = malloc(sizeof(Stack));
    stack->top = STACK_EMPTY;
    stack->totalElements = totalElements;
    stack->memberSize = memberSize;

    stack->data = malloc(memberSize * totalElements);

    return stack;
}

static int stack_expand(Stack *stack) {

    stack->totalElements *= 2;
    stack->data = realloc(stack->data, stack->totalElements * stack->memberSize);
    return OK;
}

int stack_push(Stack* stack, void* element) {
    if (stack->top + 1 >= stack->totalElements) {
        stack_expand(stack);
    }

    stack->top++;
    void* target = (byte*)(stack->data) + stack->top * stack->memberSize;
    memcpy(target, element, stack->memberSize);
    
    return OK;
}

int stack_pop(Stack* stack, void* target) {
    if (stack->top == STACK_EMPTY) {
        return STACK_EMPTY;
    }

    void* element = (byte*)(stack->data) + (stack->top * stack->memberSize);
    stack->top--;

    memcpy(target, element, stack->memberSize);

    return OK;
}

int stack_top(Stack* stack, void* target) {
    if (stack->top == STACK_EMPTY) {
        return STACK_EMPTY;
    }

    void* element = (byte*)(stack->data) + stack->top * stack->memberSize;
    memcpy(target, element, stack->memberSize);

    return OK;
}

bool stack_empty(Stack *stack) {
    return stack->top == STACK_EMPTY;
}

int stack_size(Stack* stack) {
    return stack->top + 1;
}

int stack_free(Stack* stack) {
    free(stack->data);
    free(stack);

    return OK;
}