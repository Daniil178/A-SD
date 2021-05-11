#include <stdio.h>
#include <stdlib.h>
#include "func_dop.h"
#include <limits.h>

Queue *queue_new() {
    return (Queue *) calloc(1, sizeof(Queue));
}

void queue_delete(Queue *queue) {
    list *ptr = queue->head, *ptr_prev;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(queue);
}

int queue_put(Queue *queue, int ind) {
    list *new = (list *) malloc(sizeof(list));
    if (!new) {
        return -1;
    }
    new->index = ind;
    new->next = NULL;
    if (!queue->head) {
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }
    return 0;
}

int queue_get(Queue *queue, int *output) {
    if (!queue->head) {
        return -1;
    }
    *output = queue->head->index;
    if (queue->head == queue->tail) {
        queue->tail = NULL;
    }
    list *head = queue->head;
    queue->head = head->next;
    free(head);
    return 0;
}

int dialog(const char *msgs[], int n) {
    char *error = "";
    int choice;
    do {
        puts(error);
        error = "You're wrong. Try again!";
        for (int i = 0; i < n; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice: ");
        scanf("%d", &choice);
        //choice = getchar() - '0';
        while (getchar() != '\n') {}
    } while (choice < 0 || choice >= n);
    return choice;
}

int search_vert(int id, vertex *adj, int n){
    int ind=-1;
    for(int i=0; i<n && ind == -1; i++)
        if(adj[i].id == id)
            ind = i;
    return ind;
}

int add_elem(list **head, int ind2){
    list *ptr, *new;
    new = (list *) calloc(1, sizeof(list));
    new->index = ind2;
    if(*head == NULL) {
        *head = new;
    }
    else{
        ptr = *head;
        while(ptr->next != NULL){
            if(ptr->index == ind2)
                return 1;
            ptr = ptr->next;
        }
        if(ptr->index == ind2)
            return 1;
        else {
            ptr->next = new;
        }
    }
    return 0;
}

int add_vert(int id, coordinats v, vertex **adj, int n){
    if(n == 0){
        *adj = (vertex *)calloc(1, sizeof(vertex));
        (*adj)[0].id = id, (*adj)[0].coord = v;
    }
    else{
        for(int i=0; i< n; i++){
            if((*adj)[i].id == id)
                return 1;
        }
        *adj = (vertex *) realloc(*adj, (n+1)*sizeof(vertex));
        (*adj)[n].id = id;
        (*adj)[n].coord = v;
        (*adj)[n].adj = NULL;
    }
    return 0;
}

int add_edge(int id1, int id2, vertex **adj, int n){
    int ind1=-1, ind2=-1, i;
    if(n == 0)
        return -1;
    else{
        for(i=0; i<n && (ind1 == -1 || ind2 == -1);i++){
            if((*adj)[i].id == id1)
                ind1 = i;
            if((*adj)[i].id == id2)
                ind2 = i;
        }
        if(ind1 == -1 || ind2 == -1)
            return -2;
        if(add_elem(&(*adj)[ind1].adj, ind2) == 1)
            return 1;
        if(ind1 != ind2)
            if(add_elem(&(*adj)[ind2].adj, ind1) == 1)
                return 1;
    }
    return 0;
}

int BFS(int id1, int id2, vertex *adj, int n){
    int color[n], pred[n], d[n], u, *path, i;
    int ind = search_vert(id1, adj,n), v = search_vert(id2, adj, n);
    if(ind == -1 || v == -1)
        return -1;
    list *ptr;
    Queue *q = queue_new();
    for(i=0;i<n; i++){
        color[i] = 0; ///white
        d[i] = INT_MAX;
        pred[i] = -1;
    }
    color[ind] = 1; ///grey
    d[ind] = 0;
    queue_put(q, ind);
    while(queue_get(q, &u) != -1){
        ptr = adj[u].adj;
        while(ptr != NULL){
            if(color[ptr->index] == 0){
                color[ptr->index] = 1;
                d[ptr->index] = d[u] +1;
                pred[ptr->index] = u;
                queue_put(q, ptr->index);
            }
            ptr = ptr->next;
        }
        color[u] = 2; ///black
    }
    queue_delete(q);
    if(d[v] == INT_MAX)
        return -2;
    path = (int *)calloc(d[v]+1, sizeof(int));
    ind = v;
    path[d[ind]] = adj[ind].id;
    while(d[ind] != 0){
        path[d[ind]-1] = adj[pred[ind]].id;
        ind = pred[ind];
    }
    for(i=0; i<d[v]; i++)
        printf("%d->", path[i]);
    printf("%d\n",path[d[v]]);
    free(path);
    i = d[v];
    //free(pred), free(d), free(color);
    return i;
}

void print_graph(vertex *adj, int n){
    list *ptr;
    if(n == 0)
        printf("Empty\n");
    else {
        for (int i = 0; i < n; i++) {
            printf("%d: (%f,%f) ",adj[i].id, adj[i].coord.x, adj[i].coord.y);
            ptr = adj[i].adj;
            if(ptr != NULL)
                printf("-> ");
            while (ptr != NULL) {
                printf("%d; ", adj[ptr->index].id);
                ptr = ptr->next;
            }
            printf("\n");
        }
        printf("\n");
    }
}

int search_nodes(vertex **adj, int *n){
    int id1, id2;
    coordinats v;
    float x,y;
    FILE *vert, *edge;
    if((vert = fopen("Vertexs.txt", "r+")) == NULL)
        return -1;
    while(!feof(vert)){
        fscanf(vert, "%d %f %f\n", &id1, &v.x, &v.y);
        add_vert(id1+1, v, adj, *n);
        *n = *n + 1;
    }
    fclose(vert);
    if((edge = fopen("Edges.txt", "r+")) == NULL)
        return -1;
    while(!feof(edge)){
        fscanf(edge, "%*d %d %d %*f\n", &id1, &id2);
        add_edge(id1+1, id2+1, adj, *n);
    }
    fclose(edge);
    return 0;
}

void delete_graph(vertex *adj, int n){
    list *ptr;
    for (int i = 0; i < n; i++) {
        if(adj[i].adj != NULL) {
            while (adj[i].adj->next != NULL) {
                ptr = adj[i].adj->next;
                adj[i].adj->next = ptr->next;
                free(ptr);
            }
            free(adj[i].adj);
        }
    }
    free(adj);
}
