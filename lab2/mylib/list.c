#include <stdlib.h>
#include <stdio.h>
#include "list.h"

list *list_new() {
    return (list *) calloc(1, sizeof(list));
}

void list_delete(list *list) {
    Item *ptr = list->head, *ptr_prev;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        //free(ptr_prev->data);
        free(ptr_prev);
    }
    free(list);
}

void list_print(list *list) {
    Item *ptr = list->head;
    while (ptr) {
        printf("%s ", ptr->data.id);
        ptr = ptr->next;
    }
    printf("\n");
}

int list_put(list *list, Fare data) {
    Item *new = (Item *) malloc(sizeof(Item));
    if (!new) {
        return -1;
    }
    new->data = data;
    new->next = NULL;
    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
    return 0;
}

int list_pop(list *list) {
    if (list->head == list->tail) {
        list->tail = NULL;
    }
    Item *head = list->head;
    list->head = head->next;
    free(head);
    return 0;
}
