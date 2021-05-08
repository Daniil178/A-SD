#include <stdio.h>
#include "func.h"

const char *MSGS[] = {"0. Quit", "1. Add vertex", "2. Add edge","3. Delete vertex",
                      "4. Delete edge", "5. Print Graph", "6. Generate Graph",
                      "7. Search path from v1 to v2", "8. The shortest path from v1 to v2",
                      "9. Search 3 the shortest paths", "10. Load graph from file", "11. Graphiz"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    vertex *adj = NULL;
    coordinats v1;
    int c, n=0,q, id1, id2;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                delete_graph(adj, n);
                break;
            case 1:
                printf("Please, enter id:\n");
                scanf("%d", &id1);
                printf("Please, enter coordinates x, y:\n");
                scanf("%d %d", &v1.x, &v1.y);
                getchar();
                q = add_vert(id1, v1, &adj, n);
                if(q == 0){
                    ++n;
                    printf("Vertex added\nDo you want write correct to the file?\n(YES - 1, NO - 0)\n");
                    scanf("%d", &q);
                    if(q == 1)
                        load_to_file(adj, n);
                }
                else
                    printf("Error, this vertex exist\n");
                break;
            case 2:
                printf("Please, enter id v1:\n");
                scanf("%d", &id1);
                getchar();
                printf("Please, enter id v2:\n");
                scanf("%d", &id2);
                getchar();
                q=add_edge(id1, id2, &adj, n);
                if(q == -1)
                    printf("Error, this graph is empty\n");
                else if(q == -2)
                    printf("Error, this vertex don`t exist\n");
                else if(q == 1)
                    printf("Error, this edge exist\n");
                else {
                    printf("Edge added\nDo you want write correct to the file?\n(YES - 1, NO - 0)\n");
                    scanf("%d", &q);
                    if (q == 1)
                        load_to_file(adj, n);
                }
                break;
            case 3:
                printf("Please, enter id:\n");
                scanf("%d", &id1);
                printf("Please, enter coordinates x, y:\n");
                scanf("%d %d", &v1.x, &v1.y);
                getchar();
                q = delete_vert(id1, v1, &adj, &n);
                if(q == -1)
                    printf("Error graph is empty\n");
                else if(q == -2)
                    printf("Error, this vertex don`t exist\n");
                else {
                    printf("Vertex deleted\nDo you want write correct to the file?\n(YES - 1, NO - 0)\n");
                    scanf("%d", &q);
                    if(q == 1)
                        load_to_file(adj, n);
                }
                break;
            case 4:
                printf("Please, enter id v1:\n");
                scanf("%d", &id1);
                getchar();
                printf("Please, enter id v2:\n");
                scanf("%d", &id2);
                getchar();
                q = delete_edge(id1, id2, adj, n);
                if(q == -1)
                    printf("Error, graph is empty\n");
                else if(q == -2)
                    printf("Error, this edge don`t exist\n");
                else {
                    printf("Edge deleted\nDo you want write correct to the file?\n(YES - 1, NO - 0)\n");
                    scanf("%d", &q);
                    if (q == 1)
                        load_to_file(adj, n);
                }
                break;
            case 5:
                print_graph(adj, n);
                break;
            case 6:
                q = n;
				printf("Please, enter size graph:\n");
                scanf("%d", &n);
                getchar();
                generate_graph(&adj, n, q);
                printf("Successful\nDo you want write graph to the file?\n(YES - 1, NO - 0)\n");
                scanf("%d", &q);
                if(q == 1)
                    load_to_file(adj, n);
                break;
            case 7:
                printf("Please, enter id v1:\n");
                scanf("%d", &id1);
                getchar();
                printf("Please, enter id v2:\n");
                scanf("%d", &id2);
                getchar();
                q = BFS(id1, id2, adj, n);
                if(q == -1)
                    printf("Error, this vertex don`t exist\n");
                else if(q == -2)
                    printf("There is no path from v1 to v2\n");
                else{
                    printf("The distance from v1 to v2 is %d\n", q);
                }
                break;
            case 8:
                printf("Please, enter id v1:\n");
                scanf("%d", &id1);
                getchar();
                printf("Please, enter id v2:\n");
                scanf("%d", &id2);
                getchar();
                q = Dijkstra(id1, id2, adj, n);
                if(q == -1)
                    printf("Error, this vertex don`t exist\n");
                else if(q == -2)
                    printf("There is no path from v1 to v2\n");
                else{
                    printf("The distance from v1 to v2 is %d\n", q);
                }
                break;
            case 9:
                if(Floyd_Warshall(adj, n) == -1)
                    printf("You don`t have any edge\n");
                break;
            case 10:
                if(load_from_file(&adj, &n) == -1)
                    printf("Error, file don`t exist\n");
                else
                    printf("Successful\n");
                break;
            case 11:
                if(graphiz(adj, n) == 0)
                    printf("Successful\n");
                break;
        }
    } while (c != 0);
    return 0;
}
