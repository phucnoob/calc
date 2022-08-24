#include "list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* list_new(size_t memberSize) {
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->member_size = memberSize;

    return list;
}

List* list_new_with(size_t memberSize, void* data) {
    List* list = list_new(memberSize);
    list->length = 1;
    list->head = malloc(sizeof(ListNode));
    list->head->data = malloc(memberSize);
    memcpy(list->head->data, data, memberSize);
    list->tail = list->head;

    return list;
}

void list_free(List* list) {
    ListNode* head = list->head;
    ListNode* tmp = NULL;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->data);
        free(head);
    }

    free(list);
}


List* list_append(List* list, void* data) {
    ListNode *node = malloc(sizeof(ListNode));

    node->data = malloc(list->member_size);
    node->next = NULL;
    memcpy(node->data, data, list->member_size);

    if (list->head == NULL) {
        list->head = node;
    }

    list->tail->next = node;
    list->tail = node;
    list->length++;

    return list;
}

ListNode* list_last(List* list) {
    return NULL;
}

ListNode* list_first(List* list) {
    return NULL;
}

ListNode* list_pop(List* list) {
    return NULL;
}

ListNode* list_shift(List* list) {
    return NULL;
}

void list_foreach(List* list, void (*func)(void *data)) {
    ListNode *head = list->head;

    while (head != NULL) {
        (*func)(head->data);
        head = head->next;
    }
}
