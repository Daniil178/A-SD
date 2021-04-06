#ifndef LAB3_MYLIB_H
#define LAB3_MYLIB_H

typedef struct Item{
    char *info;
    int key1;
    char key2[30];
    int index1;
    int index2;
}Item;

typedef struct Node{
    int version;
    Item *item;
    struct Node *next;
}Node;

typedef struct KeySpace1{
    int key;
    int par;
    Node *node;
}KeySpace1;

typedef struct KeySpace2{
    int busy;
    char key[30];
    Node *node;
}KeySpace2;

typedef struct Table{
    KeySpace1 *ks1;
    KeySpace2 *ks2;
    int msize1;
    int msize2;
    int csize1;
    int csize2;
}Table;

int dialog(const char *msgs[], int n);

char *get_str();

void getInt(int *a);

Table * CreateTable();

void DeleteTable(Table *table);

int Add_Elem(int key1,int par, char *key2, char *info, Table *table);

int Search_Elem_ks1(int key, Table *table);

int search_elem_ks2(char *key, Table *table);

void print_all_vers(Node *node);

int search_elem_composite_key(int key1, char *key2, Table *table);

int print_specific_version(Node *node, int version);

int search_empty_place_ks2(char *key, Table *table);

Node *create_elem(int key1, char *key2, Table *table, char *info, int index1, int index2, int version);

int delete_elem_ks1(int key, Table *table, int version);

int delete_elem_ks2(char *key2, Table *table, int version);

int delete_all_version(Node *node, Table *table);

int print_par_key(int par, Table *table);

void print_Table(Table *table);

#endif //LAB3_MYLIB_H

