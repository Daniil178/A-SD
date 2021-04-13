#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

const char *MSGS[] = {"0. Quit", "1. Add element", "2. Load from file",
                      "3. Search element","4. Delete element",
                      "5. Search the nearest element", "6. Print all element", "7. Print tree"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c, result;
    char *info, key[31];
    Node *root = NULL, *prev, *next, *search;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0://Quit
                delete_tree(root);
                break;
            case 1://Add element
                printf("Please, enter key(string <= 30 symbols):\n");
                scanf("%s", key);
                scanf("%*c");
                printf("Please, enter info(string):\n");
                info = get_str();
                result = add_elem(&root, key, info);
                if(result == 0)
                    printf("Element added\n");
                else
                    printf("Element updated\n");
                free(info);
                break;
            case 2:
                result = loading(&root);
                if(result <0)
                    printf("Don`t exist file\n");
                else
                    printf("Successful\n");
                break;
            case 3://Search element
                printf("Please, enter key(string <= 30 symbols):\n");
                scanf("%s", key);
                scanf("%*c");
                search = search_elem(root, key);
                if(search == NULL)
                    printf("This element not found\n");
                else{
                    printf("Key: %s\n", search->key);
                    print_all_versions(search->versions);
                }
                break;
            case 4://Delete element
                printf("Please, enter key(string <= 30 symbols):\n");
                scanf("%s", key);
                scanf("%*c");
                delete_elem(&root, key);
                break;
            case 5://Search the nearest element
                printf("Please, enter key(string <= 30 symbols):\n");
                scanf("%s", key);
                scanf("%*c");
                next = search_nearest_next(root, key);
                prev = search_nearest_prev(root, key);
                if(prev != NULL && next != NULL) {
                    if(abs((int)(strlen(key) - strlen(prev->key))) == abs((int)(strlen(next->key) - strlen(key)))){
                        printf("Nearest elements:\nPrevious: key - %s\n", prev->key);
                        print_all_versions(prev->versions);
                        printf("Next: key - %s\n", next->key);
                        print_all_versions(next->versions);
                    }
                    else if(abs((int)(strlen(key) - strlen(prev->key))) > abs((int)(strlen(next->key) - strlen(key)))) {
                        printf("Nearest element:\nNext: key - %s\n", next->key);
                        print_all_versions(next->versions);
                    }
                    else{
                        printf("Nearest element:\nPrevious: key - %s\n", prev->key);
                        print_all_versions(prev->versions);
                    }
                }
                else if(prev != NULL || next != NULL){
                    if(next != NULL) {
                        printf("Nearest element:\nNext: key - %s\n", next->key);
                        print_all_versions(next->versions);
                    }
                    else{
                        printf("Nearest element:\nPrevious: key - %s\n", prev->key);
                        print_all_versions(prev->versions);
                    }
                }
                else
                    printf("Not found");
                break;
            case 6://Print all
                if(root)
                    print_tree(root);
                else
                    printf("Empty\n");
                break;
            case 7:// Print tree
                print_beaty_tree(root, 0);
                break;
        }
    } while (c != 0);
    return 0;
}
