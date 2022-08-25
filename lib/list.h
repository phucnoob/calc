#include <stdlib.h>
#ifndef _LIST_H_
#include <stddef.h>
// Magic macro.
#define INT_VALUE(x) *(int*)x
#define DOUBLE_VALUE(x) *(double*)x
#define FLOAT_VALUE(x) *(float*)x


typedef struct ListNode ListNode;
struct ListNode {
    void* data;
    ListNode* next;
};

void listnode_free(ListNode* node);

typedef struct List List;
struct List {
    size_t member_size;
    size_t length;
    ListNode* head;
    ListNode* tail;
};
// new list.
List* list_new(size_t member_size);
// new list with init data.
List* list_new_with(size_t member_size, void* data);
// free list.
void list_free(List* list);


// Add element to the end of list.
List* list_append(List* list, void* data);
// Return last element.
ListNode* list_last(List* list);
// Return the first element.
ListNode* list_first(List* list);
// Remove last element.
ListNode* list_pop(List* list);
// Remove the first element.
ListNode* list_shift(List* list);

// Foreach
void list_foreach(List* list, void (*func)(void *data));

#endif // !_LIST_H_
