#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

const char *MSGS[] = {"0. Quit", "1. Add new element", "2. Search element with composite key",
                      "3. Delete element with composite key", "4. Search element with 1 key",
                      "5. Delete element with 1 key", "6. Print Table",
                      "7. Search all elements with parent`s key"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c,k,q, result, version;
    Table *table = CreateTable();
    int key1, par, ind;
    char key2[30];
    char *info=NULL;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                DeleteTable(table);
                break;
            case 1://Add new element
                printf("Please, enter key1(integer):\n");
                getInt(&key1);
                printf("Please, enter parent key1(integer):\n");
                getInt(&par);
                printf("Please, enter key2(string <30 symbols):\n");
                scanf("%s", key2);
                scanf("%*c");
                printf("Please, enter info(string):\n");
                info = get_str();
                result = Add_Elem(key1, par, key2, info, table);
                if(result == 1)
                    printf("Error, maximum elements");
                else{
                    if(result == 2)
                        printf("Error, don`t have two same keys");
                    else if(result == 4)
                        printf("Element added");
                    else
                        printf("Element updated");
                }
                free(info);
                break;
            case 2://Search a specific version of element with 2 keys
                printf("Please, enter key1(integer):\n");
                getInt(&key1);
                printf("Please, enter key2(string <30 symbols):\n");
                scanf("%s", key2);
                scanf("%*c");
                result = search_elem_composite_key(key1, key2, table);
                if(result < 0){
                    printf("Element with this keys does not exist");
                }
                else {
                    do {
                        printf("How you search element:\n1.specific version\n2.all version\n");
                        getInt(&q);
                        if (q < 1 || q > 2)
                            printf("We don`t have this command, try again\n");
                    } while (q < 1 || q > 2);
                    if (q == 2) {
                        printf("key1: %d, key2: %s\n", table->ks1[result].key, table->ks1[result].node->item->key2);
                        print_all_vers(table->ks1[result].node);
                    }
                    else{
                        printf("Please, enter version element(integer):\n");
                        getInt(&version);
                        if(print_specific_version(table->ks1[result].node, version) < 0)
                            printf("This version is not found\n");
                    }
                }
                break;
            case 3://Delete element with 2 keys
                printf("Please, enter key1(integer):\n");
                getInt(&key1);
                printf("Please, enter key2(string <30 symbols):\n");
                scanf("%s", key2);
                scanf("%*c");
                result = search_elem_composite_key(key1, key2, table);
                if(result < 0){
                    printf("Element with this keys does not exist");
                }
                else {
                    do {
                        printf("How you delete element:\n1.specific version\n2.all version\n");
                        getInt(&q);
                        if (q < 1 || q > 2)
                            printf("We don`t have this command, try again\n");
                    } while (q < 1 || q > 2);
                    if (q == 2) {
                        ind = table->ks1[result].node->item->index2;
                        if (delete_all_version(table->ks1[result].node, table) >= 0) {
                            table->ks2[ind].busy = 0;
                            table->ks2[ind].node = NULL;
                            printf("Element deleted\n");
                        } else
                            printf("This element has son\n");
                    }
                    else{
                        printf("Please, enter version element(integer):\n");
                        getInt(&version);
                        result = delete_elem_ks1(key1, table, version);
                        if (result < 0 && result > -3)
                            printf("We don`t have this version of element\n");
                        else if (result <= -3)
                            printf("Sorry, this element has sons\n");
                        else
                            printf("This version deleted\n");
                    }
                }
                break;
            case 4://Search element with 1 key
                do {
                    printf("How you search element:\n1.key1\n2.key2\n");
                    getInt(&k);
                    if(k<1 || k > 2)
                        printf("We don`t have this command, try again\n");
                }while(k<1 || k > 2);
                do {
                    printf("How you search element:\n1.specific version\n2.all version\n");
                    getInt(&q);
                    if(q<1 || q > 2)
                        printf("We don`t have this command, try again\n");
                }while(q<1 || q > 2);
                if(k==1) {
                    printf("Please, enter key1(integer):\n");
                    getInt(&key1);
                    result = Search_Elem_ks1(key1, table);
                    if(result < 0)
                        printf("We don`t have this element\n");
                    else {
                        if(q==2) {
                            printf("key1: %d, key2: %s\n", table->ks1[result].key, table->ks1[result].node->item->key2);
                            print_all_vers(table->ks1[result].node);
                        }
                        else{
                            printf("Please, enter version element(integer):\n");
                            getInt(&version);
                            if(print_specific_version(table->ks1[result].node, version) < 0)
                                printf("This version is not found\n");
                        }
                    }
                }
                if(k==2){
                    printf("Please, enter key2(string <30 symbols):\n");
                    scanf("%s", key2);
                    scanf("%*c");
                    result = search_elem_ks2(key2, table);
                    if(result < 0)
                        printf("We don`t have this element\n");
                    else {
                        if(q==2) {
                            printf("key1: %d, key2: %s\n", table->ks2[result].node->item->key1, table->ks2[result].key);
                            print_all_vers(table->ks2[result].node);
                        }
                        else{
                            printf("Please, enter version element(integer):\n");
                            getInt(&version);
                            if(print_specific_version(table->ks2[result].node, version) < 0)
                                printf("This version is not found\n");
                        }
                    }
                }
                break;
            case 5://Delete specific version element with 1 key
                do {
                    printf("How you delete element:\n1.key1\n2.key2\n");
                    getInt(&k);
                    if(k<1 || k > 2)
                        printf("We don`t have this command, try again\n");
                }while(k<1 || k > 2);
                do {
                    printf("How you delete element:\n1.specific version\n2.all version\n");
                    getInt(&q);
                    if(q<1 || q > 2)
                        printf("We don`t have this command, try again\n");
                }while(q<1 || q > 2);
                if(k==1) {
                    printf("Please, enter key1(integer):\n");
                    getInt(&key1);
                    if (q == 2) {
                        result = Search_Elem_ks1(key1, table);
                        if (result < 0)
                            printf("This element not found");
                        else {
                            ind = table->ks1[result].node->item->index2;
                            if (delete_all_version(table->ks1[result].node, table) >= 0) {
                                table->ks2[ind].busy = 0;
                                table->ks2[ind].node = NULL;
                                printf("Element deleted\n");
                            } else
                                printf("This element has son\n");
                        }
                    }
                    else {
                        printf("Please, enter version element(integer):\n");
                        getInt(&version);
                        result = delete_elem_ks1(key1, table, version);
                        if (result < 0 && result > -3)
                            printf("We don`t have this version of element\n");
                        else if (result <= -3)
                            printf("Sorry, this element has sons\n");
                        else
                            printf("This version deleted\n");
                    }
                }
                else{
                    printf("Please, enter key2(string <30 symbols):\n");
                    scanf("%s", key2);
                    scanf("%*c");
                    if (q == 2) {
                        result = search_elem_ks2(key2, table);
                        if (result < 0)
                            printf("This element not found");
                        else {
                            ind = table->ks2[result].node->item->index1;
                            if (delete_all_version(table->ks2[result].node, table) >= 0) {
                                table->ks2[result].busy = 0;
                                table->ks1[ind].node = NULL;
                                table->ks1[ind].par = 0;
                                table->ks1[ind].key = 0;
                                printf("Element deleted\n");
                            } else
                                printf("This element has son\n");
                        }
                    }
                    else {
                        printf("Please, enter version element(integer):\n");
                        getInt(&version);
                        result = delete_elem_ks1(key1, table, version);
                        if (result < 0 && result > -3)
                            printf("We don`t have this version of element\n");
                        else if (result <= -3)
                            printf("Sorry, this element has sons\n");
                        else
                            printf("This version deleted\n");
                    }
                }
                break;
            case 6://Print Table
                if(table->csize1 == 0)
                    printf("This table is empty\n");
                else
                    print_Table(table);
                break;
            case 7://Search all elements with parent`s key
                printf("Please, enter parent key(integer):\n");
                getInt(&par);
                if(print_par_key(par, table) < 0)
                    printf("Elements with this parent`s key, don`t have");
                break;
        }
    } while (c != 0);
    return 0;
}
