#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

int h1(int k){
    return (37*k % 15);
}

int h2(int k){
    return (17*k % 29);
}

int h3(int k, int i, int size){
    return ((h1(k) + i*h2(k)) % size);
}

int dialog(const char *msgs[], int n) {
    char *error = "";
    int choice, true;
    do {
        puts(error);
        error = "You're wrong. Try again!";
        for (int i = 0; i < n; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice: ");
        true = scanf("%d", &choice);
        //choice = getchar() - '0';
        while (getchar() != '\n') {}
    } while (choice < 0 || choice >= n || true <= 0);
    return choice;
}

char *get_str() {
    char buf[81] = {};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len =(int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

void getInt(int *a){
    int n;
    do{
        n = scanf("%d", a);
        while(getchar() != '\n');
        if( n <= 0){
            printf("Error, try again: ");
        }

    }while(n <= 0);
}

int Search_Elem_ks1(int key, Table *table){
    if(table->csize1 == 0)
        return -1;
    /*else if(table->csize1 == table->msize1){
        return -2;
    }*/
    else {
        for (int i = 0; i < table->csize1; i++)
            if (table->ks1[i].key == key)
                return i;
        return -1;
    }
}

int search_elem_ks2(char *key, Table *table){
    int h, k = (int) strlen(key);
    if(table->csize2 == 0)
        return -1;
    else{
        for(int i=0; i<table->msize2; i++){
            h = h3(k, i, table->msize2);
            if (strcmp(table->ks2[h].key, key) == 0 && table->ks2[h].busy == 1)
                return h;
        }
        return -1;
    }
}

int search_son(int par, Table * table){
    for(int i=0; i < table->csize1; i++){
        if(table->ks1[i].par == par && table->ks1[i].par != table->ks1[i].key)
            return i;
    }
    return -1;
}

int delete_all_version(Node *node, Table *table){
    Node *ptr = node, *del;
    if(table->ks1[node->item->index1].par == node->item->key1 && search_son(node->item->key1, table) >=0 && ptr != NULL) {
        return -1;
    }
    else{
        while (ptr->next != NULL) {
            del = ptr->next;
            ptr->next = ptr->next->next;
            free(del->item->info);
            free(del->item);
            free(del);
        }
        free(ptr->item->info);
        free(ptr->item);
        free(ptr);
        table->csize1 --;
        table->csize2 --;
        return 0;
    }
}

int delete_elem_ks1(int key1, Table *table, int version){
    int search1 = Search_Elem_ks1(key1, table), ind2;
    Node *del = NULL, *ptr;
    KeySpace1 ks;
    if(search1 < 0)
        return -1;
    else if(table->ks1[search1].par == table->ks1[search1].key && search_son(key1, table) >= 0)
        return -3;
    else{
        ind2 = table->ks1[search1].node->item->index2;
        if(table->ks1[search1].node->version == version){
            del = table->ks1[search1].node;
            table->ks2[ind2].node = table->ks2[ind2].node->next;
            table->ks1[search1].node = table->ks1[search1].node->next;
        }
        else{
            ptr = table->ks1[search1].node;
            while(ptr->next != NULL){
                if(ptr->next->version == version){
                    del = ptr->next;
                    ptr->next = ptr->next->next;
                }
                if(ptr->next != NULL)
                    ptr = ptr->next;
            }

        }
        if(del) {
            free(del->item->info);
            free(del->item);
            free(del);
            if(table->ks1[search1].node == NULL){
                table->csize1 --;
                table->csize2 --;
                table->ks2[ind2].busy = 0;
                if(table->csize1 >0){
                    ks = table->ks1[search1];
                    table->ks1[search1] = table->ks1[table->csize1];
                    ks.key = 0, ks.par = 0;
                    table->ks1[table->csize1] = ks;
                }
            }
        }
        else
            return -2;
    }
    return 0;
}

int delete_elem_ks2(char *key2, Table *table, int version){
    int search2 = search_elem_ks2(key2, table), ind1;
    Node *del = NULL, *ptr;
    if(search2 < 0)
        return -1;
    else if(table->ks1[table->ks2[search2].node->item->index1].par == table->ks2[search2].node->item->key1 && search_son(table->ks2[search2].node->item->key1, table) >= 0)
        return -3;
    else{
        ind1 = table->ks2[search2].node->item->index1;
        if(table->ks2[search2].node->version == version){
            del = table->ks2[search2].node;
            table->ks1[ind1].node = table->ks1[ind1].node->next;
            table->ks2[search2].node = table->ks2[search2].node->next;
        }
        else{
            ptr = table->ks2[search2].node;
            while(ptr->next != NULL){
                if(ptr->next->version == version){
                    del = ptr->next;
                    ptr->next = ptr->next->next;
                }
                if(ptr->next != NULL)
                    ptr = ptr->next;
            }

        }
        if(del) {
            free(del->item->info);
            free(del->item);
            free(del);
            if(table->ks2[search2].node == NULL){
                table->csize1 --;
                table->csize2 --;
                table->ks2[search2].busy = 0;
            }
        }
        else
            return -2;
    }
    return 0;
}

void print_all_vers(Node *node){
    Node *ptr;
    ptr = node;
    while(ptr->next != NULL){
        printf("v: %d - %s ", ptr->version, ptr->item->info);
        ptr = ptr->next;
    }
    printf("v: %d - %s ", ptr->version, ptr->item->info);
    printf("\n");
}

int search_elem_composite_key(int key1, char *key2, Table *table){
    int ind1 = Search_Elem_ks1(key1, table);
    if(ind1 >=0 && strcmp(table->ks1[ind1].node->item->key2, key2) == 0)
        return ind1;
    else
        return -1;
}

int print_specific_version(Node *node, int version){
    Node *ptr = node;
    while(ptr != NULL){
        if(ptr->version == version){
            printf("key1: %d, key2: %s\n v: %d - %s\n",ptr->item->key1, ptr->item->key2, ptr->version, ptr->item->info);
            return 0;
        }
        ptr = ptr->next;
    }
    return -1;
}

int search_empty_place_ks2(char *key, Table *table){
    int h, k = (int) strlen(key);
    if(table->csize2 == table->msize2)
        return -3;
    else{
        for(int i=0; i<table->msize2; i++){
            h = h3(k, i, table->msize2);
            if (table->ks2[h].busy == 0)
                return h;
        }
    }
    return -3;
}

Node *create_elem(int key1, char *key2, Table *table, char *info, int index1, int index2, int version){
    Node *node;
    Item *item;
    node = (Node *) calloc(1, sizeof(Node));
    node->version = version;
    node->next = NULL;
    item = (Item *) calloc(1, sizeof(Item));
    item->info = (char *) calloc(strlen(info) + 1, sizeof(char));
    memcpy(item->info, info, strlen(info) * sizeof(char));
    item->key1 = key1;
    memcpy(item->key2, key2, strlen(key2));
    item->index1 = index1, item->index2 = index2;
    node->item = item;
    return node;
}

int Add_Elem(int key1, int par, char *key2, char *info, Table *table){
    int search1, search2, search3, version;
    Node *node;
    search1 = Search_Elem_ks1(key1, table);
    search2 = search_elem_ks2(key2, table);
    search3 = search_empty_place_ks2(key2, table);
    if(table->csize2 == table->msize2 || table->csize1 == table->msize1)
        return 1;
    else if((search1 >= 0 && search2 <0) || (search2 >= 0 && search1 <0) || (search1 >=0 && search2 >=0
    && table->ks1[search1].node != table->ks2[search2].node) || (search1 >=0 && table->ks1[search1].par != par)) {
        return 2;
    }
    else if(search1 >=0 && search2 >=0 && table->ks1[search1].node == table->ks2[search2].node){
        version = table->ks1[search1].node->version +1;
        node = create_elem(key1, key2, table, info, search1, search2, version);
        node->next = table->ks1[search1].node;
        table->ks1[search1].node = node;
        table->ks2[search2].node = node;
        return 3;
    }
    if(search1 <0 && search2 <0){
        version = 1;
        table->ks1[table->csize1].key = key1;
        table->ks1[table->csize1].par = par;
        memcpy(table->ks2[search3].key, key2, strlen(key2) * sizeof(char));
        table->ks2[search3].busy = 1;
        node = create_elem(key1, key2, table, info, table->csize1, search3, version);
        table->ks1[table->csize1].node = node;
        table->ks2[search3].node = node;
        ++table->csize1;
        ++table->csize2;
        return 4;
    }
    return 1;
}

int print_par_key(int par, Table *table){
    int search1;
    search1 = Search_Elem_ks1(par, table);
    if(search1 < 0)
        return -1;
    else{
        printf("parent key: %d\n", par);
        printf("key1: %d, key2: %s\n", table->ks1[search1].key, table->ks1[search1].node->item->key2);
        print_all_vers(table->ks1[search1].node);;
        for(int i=0; i< table->csize1; i++){
            if(table->ks1[i].par == par && table->ks1[i].key != par){
                printf("key1: %d, key2: %s\n", table->ks1[i].key, table->ks1[i].node->item->key2);
                print_all_vers(table->ks1[i].node);
            }
        }
    }
    return 0;
}

void print_Table(Table *table){
    for(int i=0; i<table->csize1; i++){
        printf("parent key: %d, key1: %d, key2: %s\n",table->ks1[i].par, table->ks1[i].node->item->key1, table->ks1[i].node->item->key2);
        print_all_vers(table->ks1[i].node);
    }
}

Table * CreateTable(){
    Table *table = (Table *) calloc(1,sizeof(Table));
    table->msize1 = 31, table->msize2 = 31;
    table->csize1 = 0, table->csize2 = 0;
    table->ks1 = (KeySpace1 *) calloc(table->msize1, sizeof(KeySpace1));
    table->ks2 = (KeySpace2 *) calloc(table->msize2, sizeof(KeySpace2));
    return table;
}

void DeleteTable(Table *table){
    Node *del;
    for(int i=0; i<table->csize1; i++){
        if(table->ks1[i].node->item) {
            while(table->ks1[i].node != NULL){
                del = table->ks1[i].node;
                table->ks2[table->ks1[i].node->item->index2].node = table->ks2[table->ks1[i].node->item->index2].node->next;
                table->ks1[i].node = table->ks1[i].node->next;
                free(del->item->info);
                free(del->item);
                free(del);
            }
        }
    }
    free(table->ks1);
    free(table->ks2);
    free(table);
}
