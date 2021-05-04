#include <stdio.h>
#include <stdlib.h>
#include "func.h"

const char *MSGS[] = {"0. Quit", "1. Add element", "2. Load from file",
                      "3. Search element","4. Delete element",
                      "5. Search previous element", "6. Print elements between key1, key2",
                      "7. Print all element", "8. Print tree", "9. For graphiz"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c, result;
    char *info;
    int key, key2;
    Node *root = NULL, *prev, *next, *search;
    FILE *graph;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0://Quit
                delete_tree(root);
                break;
            case 1://Add element
                printf("Please, enter key(integer):\n");
                scanf("%d", &key);
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
                printf("Please, enter key(integer):\n");
                scanf("%d", &key);
                scanf("%*c");
                search = search_elem(root, key);
                if(search == NULL)
                    printf("This element not found\n");
                else{
                    printf("Key: %d\n", search->key);
                    print_all_versions(search->versions);
                }
                break;
            case 4://Delete element
                printf("Please, enter key(integer):\n");
                scanf("%d", &key);
                scanf("%*c");
                delete_elem(&root, key);
                break;
            case 5://Search the nearest element
                printf("Please, enter key(integer):\n");
                scanf("%d", &key);
                scanf("%*c");
                ///next = search_nearest_next(root, key);
                prev = search_nearest_prev(root, key);
                if(prev != NULL){
                        printf("Nearest previous element:\nkey - %d\n", prev->key);
                        print_all_versions(prev->versions);
                }
                else
                    printf("Not found");
                break;
            case 6://Print all
                printf("Please, enter key1, key2(integer):\n");
                scanf("%d %d", &key, &key2);
                scanf("%*c");
                if(root)
					print(key, key2, root);
				else
					printf("Empty\n");
                break;
            case 7:// Print tree
                if(root)
                    print_tree(root);
                else
                    printf("Empty\n");
                break;
            case 8:// Print tree
                if(root)
                    print_beaty_tree(root, 0);
                else
                    printf("Empty\n");
                break;
            case 9:
                graph = fopen("graph.txt", "w");
                if(root) {
                    fprintf(graph, "digraph G {\n");
                    graphiz(root, graph);
                    fprintf(graph, "}");
                    printf("Successful\n");
                }
                else
                    printf("Empty\n");
                fclose(graph);
                break;
        }
    } while (c != 0);
    return 0;
}
