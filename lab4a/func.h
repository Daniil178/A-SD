typedef struct List{
    int release;
    char *info;
    struct List *next;
}List;

typedef struct Node{
    char key[31];
    List *versions;
    struct Node *left;
    struct Node *right;
}Node;

int dialog(const char *msgs[], int n);
char *get_str();
List *new_version(List *next, char *info);
int print_tree(Node *ptr);
void print_all_versions(List *versions);
Node * search_nearest_prev(Node *root, char *key);
Node * search_nearest_next(Node *root, char *key);
int add_elem(Node **ptr, char *key, char *info);
Node *search_elem(Node *ptr, char *key);
int delete_tree(Node *ptr);
void delete_elem(Node **root, char *key);
int loading(Node **root);
Node *search_elem_par(Node *ptr, char *key);
int print_beaty_tree(Node *ptr, int probel);
Node *create_new();
