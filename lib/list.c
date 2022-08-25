#include "list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


void listnode_free(ListNode* node) {
    free(node->data);
    free(node);
}

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
    list->head->next = NULL;
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
        list->tail = node;
        list->length++;

        return list;
    }

    list->tail->next = node;
    list->tail = node;
    list->length++;

    return list;
}

ListNode* list_last(List* list) {
    return list->tail;
}

ListNode* list_first(List* list) {
    return list->head;
}

ListNode* list_pop(List* list) {

    ListNode *current = list->head;
    ListNode* poped = list->tail;
    if (current == NULL) {
        return NULL;
    }

    if (current->next == NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        return poped;
    }

    while (current && current->next != list->tail) {
        current = current->next;
    }

    current->next = NULL;
    list->tail = current;
    list->length--;
    
    return poped;
}

ListNode* list_shift(List* list) {

    ListNode* shift = list->head;
    if (shift == NULL) {
        return NULL;
    }

    if (shift->next == NULL) {
        list->tail = NULL;
        list->head = NULL;
        list->length = 0;

        return shift;
    }

    list->head = shift->next;
    list->length--;

    return shift;
}

void list_foreach(List* list, void (*func)(void *data)) {
    ListNode *head = list->head;

    while (head != NULL) {
        (*func)(head->data);
        head = head->next;
    }
}
