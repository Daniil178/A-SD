#ifndef LIST_H
#define LIST_H

typedef struct Fare{
    char id[20];
    int ta;
    int ts;
}Fare;

typedef struct Item {
    Fare data;
    struct Item *next;
} Item;

typedef struct list {
    Item *head;
    Item *tail;
} list;

list *list_new();
int list_put(list* l, Fare data);
int list_pop(list *list);
void list_delete(list* l);
void list_print(list *list);

#endif
