#include<stdio.h>
#include<stdlib.h>
#include"../stack.h"


int main() {
    Stack *stack = stack_new(sizeof(int), 10);
    for(int i = 0; i < 20; i++) {
        stack_push(stack, &i);
    }

    int tmp = 99;
    for (int i = 0; i < 20; i++) {
        stack_pop(stack, &tmp);
        printf("%d -> ", tmp);
    }
    printf("\n");
    return 0;
}