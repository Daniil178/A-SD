#include <stdio.h>
#include <stdlib.h>
#include "func.h"

const char *MSGS[] = {"0. Quit", "1. Add element", "2. Delete element",
                      "3. Search element", "4. Print"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);


int main() {
    int c = 0, key, q;
    Item *head = (Item *) calloc(1, sizeof(Item));
    Skiplist *list = (Skiplist *) calloc(1, sizeof(Skiplist));
    list->head = head;
    Item *x;
    for(int i = 0; i<MAX_LEVEL; ++i)
        list->head->forwards[i] = NULL;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                delete_list(list);
                break;
            case 1:
                printf("Please, enter key:\n");
                scanf("%d", &key);
                getchar();
                if(insert(key, list) == 1)
                    printf("Error, this element exist\n");
                break;
            case 2:
                printf("Please, enter key:\n");
                scanf("%d", &key);
                getchar();
                if(delete(key, list) == 1)
                    printf("Error, this element don`t exist\n");
                break;
            case 3:
                printf("Please, enter key:\n");
                scanf("%d", &key);
                getchar();
                x = search_elem(key, list);
                if(x == NULL)
                    printf("This element not found\n");
                else
                    printf("key - %d, level - %d\n",x->key, x->level);
                break;
            case 4:
                if(print_list(list) == 1)
                    printf("Empty\n");
                break;
        }
    } while (c != 0);
    return 0;
}
