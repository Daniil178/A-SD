#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#ifdef Vector
#include "vector.h"
#endif

#ifdef List
#include "list.h"
#endif

Queue *queue_new() {
    Queue *q = (Queue *) calloc(1, sizeof(Queue));
#ifdef List
    q->head = 0;
    q->tail = 0;
#endif

#ifdef Vector
    q->head = 0;
    q->tail = 0;
#endif
    q->num = 0;
    return q;
}

void queue_delete(Queue *queue) {
#ifdef List
    Item *ptr = queue->head, *ptr_prev;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
#endif
    free(queue);
}

int queue_put(Queue *queue, Fare data) {
#ifdef List
    Item *new = (Item *) malloc(sizeof(Item));
    if (!new) {
        return -1;
    }
    new->data = data;
    new->next = NULL;
    if (queue->num == 0) {
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }
#endif

#ifdef Vector
    if(queue->head == queue->tail && queue->num == 30)
        return -1;
    else{
        queue->data[queue->tail] = data;
        queue->tail = (queue->tail +1) % 30;
        (queue->num)++;
    }
#endif
    queue->num ++;
    return 0;
}

int queue_pop(Queue *queue) {
    if (queue->head == queue->tail && queue->num == 0) {
        return -1;
    }
#ifdef List
    if (queue->head == queue->tail) {
        queue->tail = NULL;
    }
    Item *head = queue->head;
    queue->head = head->next;
    free(head);
#endif

#ifdef Vector
    else{
        queue->head = (queue->head +1) % 30;
    }
#endif
    queue->num --;
    return 0;
}

Fare *queue_get(Queue *queue){
#ifdef List
    return &queue->head->data;
#endif

#ifdef Vector
    return &queue->data[queue->head];
#endif
}

void queue_print(Queue *queue) {
#ifdef List
    Item *ptr = queue->head;
    while (ptr) {
        printf("%s ", ptr->data.id);
        ptr = ptr->next;
    }
#endif

#ifdef Vector
    for(int i = 0; i < queue->num; i ++)
        printf("%s ", queue->data[queue->head + i].id);
#endif
    printf("\n");
}
