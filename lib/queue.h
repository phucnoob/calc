#include "list.h"

typedef struct Queue Queue;
struct Queue {
    List* list;
};

Queue* queue_new(size_t member_size);
Queue* queue_enqueue(Queue *queue, void* element);
void queue_dequeue(Queue *queue, void* target);
void queue_free(Queue *queue);