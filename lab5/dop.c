#include <stdio.h>
#include "func_dop.h"

const char *MSGS[] = {"0. Quit","1. Load graph from file", "2. Numbers vertex between cities",
                      "3. Print graph"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    vertex *adj = NULL;
    int c, n=0,q, id1, id2;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                delete_graph(adj, n);
                break;
            case 1:
                if(search_nodes(&adj, &n) == -1)
                    printf("Error, file don`t exist\n");
                else
                    printf("Successful\n");
                break;
            case 2:
                printf("Please, enter id v1:\n");
                scanf("%d", &id1);
                getchar();
                printf("Please, enter id v2:\n");
                scanf("%d", &id2);
                getchar();
                q = BFS(id1, id2, adj, n);
                if (q == -1)
                    printf("Error, this city don`t exist\n");
                else if (q == -2)
                    printf("There is no path from v1 to v2\n");
                else {
                    printf("The numbers nodes between %d and %d is %d\n", id1, id2, q);
                }
                break;
            case 3:
                print_graph(adj, n);
                break;
        }
    } while (c != 0);
    return 0;
}
