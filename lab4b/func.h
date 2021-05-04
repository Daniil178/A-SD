typedef struct List{
    int release;
    char *info;
    struct List *next;
}List;

typedef struct Node{
    int key;
    List *versions;
    int colour;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
}Node;

int dialog(const char *msgs[], int n);
char *get_str();
List *new_version(List *next, char *info);
int print_tree(Node *ptr);
void print_all_versions(List *versions);
Node * search_nearest_prev(Node *root, int key);
Node * search_nearest_next(Node *root, int key);
int add_elem(Node **ptr, int key, char *info);
Node *search_elem(Node *ptr, int key);
int delete_tree(Node *ptr);
void delete_elem(Node **root, int key);
int loading(Node **root);
void left_rotate(Node *x, Node **root);
void right_rotate(Node *x, Node **root);
int print_beaty_tree(Node *ptr, int probel);
int print(int key1, int key2, Node *ptr);
Node *create_new();
int graphiz(Node *ptr, FILE *graph);
