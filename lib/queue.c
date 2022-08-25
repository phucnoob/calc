#include "queue.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Queue* queue_new(size_t member_size) {
    Queue *queue = malloc(sizeof(Queue));
    queue->list = list_new(member_size);

    return queue;
}

Queue* queue_enqueue(Queue *queue, void* element) {
    list_append(queue->list, element);

    return queue;
}

void queue_dequeue(Queue *queue, void* target) {
    ListNode* node = list_shift(queue->list);
    memcpy(target, node->data, queue->list->member_size);
}

void queue_free(Queue *queue) {
    list_free(queue->list);
    free(queue);
}
