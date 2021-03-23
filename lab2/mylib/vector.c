#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

vector* vector_new(){
    vector *q = (vector *) calloc(1, sizeof(vector));
    q->head = 0;
    q->tail = 0;
    q->num = 0;
    return q;
}

int vector_put(vector* v, Fare data){
    if(v->head == v->tail && v->num == 30)
        return -1;
    else{
        v->data[v->tail] = data;
        v->tail = (v->tail +1) % 30;
        (v->num)++;
    }
    return 0;
}

int vector_pop(vector* v){
    if(v->head == v->tail && v->num == 0)
        return -1;
    else{
        v->head = (v->head +1) % 30;
        (v->num)--;
    }
    return 0;
}

void vector_delete(vector* v){
    free(v);
}

void vector_print(vector* v){
    for(int i = 0; i < v->num; i ++)
        printf("%s ", v->data[v->head + i].id);
    printf("\n");
}
