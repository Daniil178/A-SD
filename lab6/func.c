#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"


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
        choice = getchar() - '0';
        while (getchar() != '\n') {}
    } while (choice < 0 || choice >= n);
    return choice;
}

double random(){
    return ((double) rand() - 1)/RAND_MAX;
}

Item* create_item(int key){
    Item *item;
    int level = 1;
    srand(time(NULL));
    item = (Item *) calloc(1, sizeof(Item));
    item->key = key;
    while(random() < 0.5 && level < MAX_LEVEL){
        level += 1;
    }
    item->level = level;
    return item;
}

Item *search_elem(int key, Skiplist *list){
    Item *x = list->head;
    for(int i = list->level -1; i >= 0; --i){
        while(x->forwards[i] != NULL && x->forwards[i]->key < key){
            x = x->forwards[i];
        }
    }
    x = x->forwards[0];
    if(x != NULL && x->key == key){
        return x;
    }
    else
        return NULL;
}

int insert(int key, Skiplist *list){
    Item* update[MAX_LEVEL] = {NULL};
    Item *x = list->head;
    for(int i = list->level -1; i >= 0; --i){
        while(x->forwards[i] != NULL && x->forwards[i]->key < key)
            x = x->forwards[i];
        update[i] = x;
    }
    x = x->forwards[0];
    if(x != NULL && x->key == key) {
        return 1;
    }
    Item *new = create_item(key);
    if(list->level < new->level){
        for(int i=new->level-1; i>list->level-1; --i){
            update[i] = list->head;
        }
        list->level = new->level;
    }
    for(int i=0; i<list->level; ++i){
        new->forwards[i] = update[i]->forwards[i];
        update[i]->forwards[i] = new;
    }
    return 0;
}

int delete(int key, Skiplist *list){
    Item *x = list->head;
    Item* update[MAX_LEVEL] = {NULL};
    int i;
    for(i = list->level -1; i >= 0; --i){
        while(x->forwards[i] != NULL && x->forwards[i]->key < key)
            x = x->forwards[i];
        update[i] = x;
    }
    x = x->forwards[0];
    if(x != NULL && x->key == key){
        i = 0;
        while(i < x->level && update[i]->forwards[i] == x){
            update[i]->forwards[i] = x->forwards[i];
            ++i;
        }
        free(x);
        while(list->level > 1 && list->head->forwards[list->level] == NULL)
            --list->level;
        return 0;
    }
    else
        return 1;
}

int print(Skiplist *list){
    Item *x = list->head;
    x = x->forwards[0];
    if(x != NULL) {
        while (x != NULL) {
            printf("%d,%d  ", x->key, x->level);
            x = x->forwards[0];
        }
        return 0;
    }
    else
        return 1;
}

void delete_list(Skiplist *list){
    Item *del = list->head;
    while(list->head != NULL){
        del = list->head;
        list->head = del->forwards[0];
        free(del);
    }
    free(list);
}
