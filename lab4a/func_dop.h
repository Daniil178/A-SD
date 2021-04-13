typedef struct Node{
    char key[50];
    int version;
    struct Node *left;
    struct Node *right;
}Node;

int add_elem(Node **ptr, char *key);
int delete_tree(Node *ptr);
int load_tree(Node *ptr, FILE *output);
int print_beaty_tree(Node *ptr, int i);
Node *create_new();
