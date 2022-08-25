#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "../lib/list.h"

bool test_new_with() {
    int number = 42;
    List* list = list_new_with(sizeof(int), &number);

    int ans = *(int*)(list->head->data);

    return ans == number;
}

bool test_append() {
    int number = 1;
    List *list = list_new(sizeof(number));
    int arr[10];
    while (number <= 10) {
        list_append(list, &number);
        arr[number - 1] = number;

        number++;
    }

    ListNode* head = list->head;
    int tmp = -1;

    for (int i = 0; i < 10; i++) {
        tmp = *(int*) head->data;
        if (tmp != arr[i]) {
            return false;
        } else {
            head = head->next;
        }
    }

    return true;
}

bool test_pop() {
    List* list = list_new(sizeof(int));
    int number = 0;
    list_append(list, &number);
    number = 1;
    list_append(list, &number);
    number = 2;
    list_append(list, &number);
    number = 3;
    list_append(list, &number);

    ListNode* node = list_pop(list);

    int tmp = *(int*) node->data;

    return tmp == number;
}

bool test_first() {
    int number = 0;
    List* list = list_new(sizeof(int));

    list_append(list, &number);
    number = 100;
    list_append(list, &number);

    ListNode *node = list_first(list);
    int ans = INT_VALUE(node->data);

    return ans == 0;
}

bool test_last() {
    int number = 0;
    List* list = list_new(sizeof(int));

    list_append(list, &number);
    number = 100;
    list_append(list, &number);

    ListNode *node = list_last(list);
    int ans = INT_VALUE(node->data);

    return ans == 100;
}

void stats_test(bool (*test_func)(), char* test_name) {
    printf("Test ...%s...", test_name);
    if ((*test_func)()) {
        printf("OK...\n");
    } else {
        printf("Failed...\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    stats_test(test_new_with, "Test new list");
    stats_test(test_append, "Test list append");
    stats_test(test_pop, "Test List pop");
    stats_test(test_first, "Test List front");
    stats_test(test_last, "Test List back");
    return 0;
}