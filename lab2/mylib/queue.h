#ifndef QUEUE_H
#define QUEUE_H
#ifdef List
#include "list.h"
#endif
#ifdef Vector
#include "vector.h"
#endif
/*
typedef struct Fare{
    char id[30];
    int ta;
    int ts;
}Fare;
#ifdef List
typedef struct Item {
    Fare data;
    struct Item *next;
} Item;
#endif*/
typedef struct Queue {
#ifdef List
    Item *head;
    Item *tail;
#endif

#ifdef Vector
    int head;
    int tail;
    Fare data[30];
#endif
    int num;
} Queue;

Queue *queue_new();
void queue_delete(Queue *queue);
int queue_put(Queue *queue, Fare data);
int queue_pop(Queue *queue);
Fare *queue_get(Queue *queue);
void queue_print(Queue *queue);
#endif

