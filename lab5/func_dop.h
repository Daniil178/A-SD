typedef struct coordinats{
    float x;
    float y;
}coordinats;

typedef struct list{
    int index;
    struct list *next;
}list;

typedef struct Queue {
    list *head;
    list *tail;
} Queue;

typedef struct vertex{
    int id;
    coordinats coord;
    list *adj;
}vertex;

int dialog(const char *msgs[], int n);
int add_vert(int id, coordinats v, vertex **adj, int n);
int add_edge(int id1, int id2, vertex **adj, int n);
int BFS(int id1, int id2, vertex *adj, int n);
int Dijkstra(int id1, int id2, vertex *adj, int n);
int Floyd_Warshall(vertex *adj, int n);
void print_graph(vertex *adj, int n);
int search_nodes(vertex **adj, int *n);
void delete_graph(vertex *adj, int n);
