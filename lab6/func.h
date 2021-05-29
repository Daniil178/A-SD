#define MAX_LEVEL 4


typedef struct Item{
    int key;
    int level;
    struct Item *forwards[MAX_LEVEL];
}Item;


typedef struct Skiplist{
    int level;
    Item *head;
}Skiplist;

int dialog(const char *msgs[], int n);
Item *search_elem(int key, Skiplist *list);
int insert(int key, Skiplist *list);
int delete(int key, Skiplist *list);
void delete_list(Skiplist *list);
int print(Skiplist *list);
int print_list(Skiplist *list);
