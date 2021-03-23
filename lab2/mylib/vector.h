#ifndef VECTOR_H
#define VECTOR_H

typedef struct Fare{
    char id[20];
    int ta;
    int ts;
}Fare;

typedef struct vector{
    int head;
    int tail;
    Fare data[30];
    int num;
}vector;

vector* vector_new();
int vector_put(vector* v, Fare data);
int vector_pop(vector* v);
void vector_delete(vector* v);
void vector_print(vector* v);

#endif
