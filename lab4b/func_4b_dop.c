#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_4b_dop.h"

Node Elist = {2147483647, NULL, 1, &Elist, &Elist, NULL};

int dialog(const char *msgs[], int n) {
    char *error = "";
    int choice;
    do {
        puts(error);
        error = "You're wrong. Try again!";
        for (int i = 0; i < n; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice: ");
        choice = getchar() - '0';
        while (getchar() != '\n') {}
    } while (choice < 0 || choice >= n);
    return choice;
}

char *get_str() {
    char buf[81] = {};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len =(int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

void left_rotate(Node *x, Node **root){
    Node *y = x->right, *par = x->parent;
    x->right = y->left;
    if(y->left != &Elist)
        y->left->parent = x;
    y->parent = par;
    if(par == &Elist)
        *root = y;
    else{
        if(par->left == x)
            par->left = y;
        else
            par->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(Node *x, Node **root){
    Node *y = x->left, *par = x->parent;
    x->left = y->right;
    if(y->right != &Elist)
        y->right->parent = x;
    y->parent = par;
    if(par == &Elist)
        *root = y;
    else{
        if(par->left == x)
            par->left = y;
        else
            par->right = y;
    }
    y->right = x;
    x->parent = y;
}

void rb_insert_fixup(Node *x, Node **root){
    Node *p1, *pp, *p2;
    while(x->parent->colour == 0) {
        p1 = x->parent, pp = p1->parent;
        if (p1 == pp->left) {
            p2 = pp->right;
            if (p2->colour == 0) { ///Случай 1
                p1->colour = 1;
                p2->colour = 1;
                pp->colour = 0;
                x = pp;
            }
            else if(x == p1->right){///Случай 2
                left_rotate(p1, root);
                x = p1;
                p1 = x->parent;
            }
            else{///Случай 3
                p1->colour = 1;
                pp->colour = 0;
                right_rotate(pp, root);
            }
        } else {
            p2 = pp->left;
            if (p2->colour == 0) { ///Случай 1a
                p1->colour = 1;
                p2->colour = 1;
                pp->colour = 0;
                x = pp;
            }
            else if(x == p1->left){///Случай 2a
                right_rotate(p1, root);
                x = p1;
                p1 = x->parent;
            }
            else{///Случай 3a
                p1->colour = 1;
                pp->colour = 0;
                left_rotate(pp, root);
            }
        }
    }
    (*root)->colour = 1;
}

void rb_delete_fixup(Node *x, Node **root){
    Node *p, *w;
    while(x != *root && x->colour == 1){
        p = x->parent;
        if(x == p->left){
            w = p->right;
            if(w->colour == 0){/// Случай 1
                w->colour = 1;
                p->colour = 0;
                left_rotate(p,root);
                w = p->right;
            }
            if(w->left->colour == 1 && w->right->colour == 1){/// Случай 2
                w->colour = 0;
                x = p;
            }
            else{
                if(w->right->colour == 1){/// Случай 3
                    w->colour = 0;
                    w->left->colour = 1;
                    right_rotate(w, root);
                    w = p->right;
                }
                else{/// Случай 4
                    w->colour = p->colour;
                    p->colour = 1;
                    w->right->colour = 1;
                    left_rotate(p, root);
                    x = *root;
                }
            }
        }
        else{
            w = p->left;
            if(w->colour == 0){/// Случай 1a
                w->colour = 1;
                p->colour = 0;
                right_rotate(p,root);
                w = p->left;
            }
            if(w->left->colour == 1 && w->right->colour == 1){/// Случай 2a
                w->colour = 0;
                x = p;
            }
            else{
                if(w->left->colour == 1){/// Случай 3a
                    w->colour = 0;
                    w->right->colour = 1;
                    left_rotate(w, root);
                    w = p->left;
                }
                else{/// Случай 4a
                    w->colour = p->colour;
                    p->colour = 1;
                    w->left->colour = 1;
                    right_rotate(p, root);
                    x = *root;
                }
            }
        }
    }
    x->colour = 1;
}

List *new_version(List *next, long info){
    List *head;
    head = (List *) calloc(1, sizeof(List));
    head->next = next;
    head->info = info;
    if(next == NULL)
        head->release = 1;
    else
        head->release = head->next->release + 1;
    return head;
}

int add_elem(Node **root, int key, long info){
    Node *par = *root;
    Node *ptr = *root;
    Node *new = create_new();
    new->key = key;
    new->versions = new_version(new->versions, info);
    if(ptr == NULL) {
        *root = new;
        (*root)->colour = 1;
    }
    else {
        while (ptr != &Elist) {
            if (key < ptr->key) {
                par = ptr;
                ptr = ptr->left;
            } else if (key > ptr->key) {
                par = ptr;
                ptr = ptr->right;
            } else {
                ptr->versions = new_version(ptr->versions, info);
				free(new->versions);
				free(new);
                return 1;//updated
            }
        }
        if (key < par->key){
            par->left = new;
            new->parent = par;
        }
        else {
            par->right = new;
            new->parent = par;
        }
    }
    rb_insert_fixup(new, root);
    return 0;//added
}

void print_all_versions(List *versions){
    List *ptr = versions;
    printf("Info: ");
    long vers[versions->release];
    while(ptr->next != NULL){
        vers[ptr->release - 1] = ptr->info;
        ptr = ptr->next;
    }
    vers[0] = ptr->info;
    for(int i = 0; i < versions->release; i++)
        printf("%ld; ", vers[i]);
    printf("\n");
}

int print_tree(Node *ptr){
    if(ptr == &Elist || ptr == NULL)
        return 0;
    print_tree(ptr->left);
    printf("Key: %d\n", ptr->key);
    print_all_versions(ptr->versions);
    print_tree(ptr->right);
    return 0;
}

Node *search_elem(Node *ptr, int key){
    Node *search = NULL;
    while(ptr != &Elist && search == NULL){
        if(key < ptr->key)
            ptr = ptr->left;
        else if(key > ptr->key)
            ptr = ptr->right;
        else
            search = ptr;
    }
    return search;
}

Node * search_nearest_next(Node *root, int key){
    Node *ptr = root, *next = NULL;
    while(ptr != &Elist){
        if(key < ptr->key){
            next = ptr;
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }
    return next;
}

Node * search_nearest_prev(Node *root, int key){
    Node *ptr = root, *prev = NULL;
    while(ptr != &Elist){
        if(ptr->key < key){
            prev = ptr;
            ptr = ptr->right;
        }
        else{
            ptr = ptr->left;
        }
    }
    if(prev == &Elist)
        return prev;
    return prev;
}

void delete_list(List *head){
    List *ptr = head, *del;
    while (ptr->next != NULL) {
        del = ptr->next;
        ptr->next = ptr->next->next;
        free(del);
    }
    free(ptr);
}

void delete_last_list(List *head){
    List *ptr = head, *del = head;
    while (del->next != NULL) {
        ptr = del;
        del = del->next;
    }
    ptr->next = del->next;
    free(del);
}

void delete_elem(Node **root, int key){
    Node *delete = search_elem(*root, key);
    Node *par = delete->parent;
    Node *next;
    int colour, lf;
    if(delete == NULL)
        printf("This element not found\n");
    else if(delete->versions->next != NULL){
        delete_last_list(delete->versions);
        printf("First version deleted\n");
    }
    else{
        if(delete->left == &Elist && delete->right == &Elist){
            if(par != &Elist) {
                if (par->left == delete) {
                    par->left = &Elist;
                    Elist.parent = par;
                } else if (par->right == delete) {
                    par->right = &Elist;
                    Elist.parent = par;
                }
            }
            colour = delete->colour;
            delete->parent = NULL;
            delete_list(delete->versions);
            free(delete);
            if(colour == 1 && (par->right != &Elist || par->left != &Elist))
                rb_delete_fixup(&Elist, root);
            if(par == &Elist)
                *root = NULL;
        }
        else if(delete->left == &Elist || delete->right == &Elist){
            if(delete->left == &Elist){
                if(par != &Elist) {
                    if (par->left == delete) {
                        par->left = delete->right;
                        delete->right->parent = par;
                        lf = 0;
                    }
                    else if (par->right == delete) {
                        par->right = delete->right;
                        delete->right->parent = par;
                        lf = 1;
                    }
                }
                else{
                    *root = delete->right;
                    delete->right->parent = NULL;
                }
            }
            else{
                if(par != &Elist) {
                    if (par->left == delete) {
                        par->left = delete->left;
                        delete->left->parent = par;
                        lf = 0;
                    } else if (par->right == delete) {
                        par->right = delete->left;
                        delete->left->parent = par;
                        lf = 1;
                    }
                }
                else {
                    *root = delete->left;
                    delete->left->parent = NULL;
                }
            }
            colour = delete->colour;
            delete_list(delete->versions);
            free(delete);
            if(colour == 1) {
                if (lf == 0)
                    rb_delete_fixup(par->left, root);
                else
                    rb_delete_fixup(par->right, root);
            }
        }
        else{
            next = search_nearest_next(*root, key);
            delete->key = next->key;
            delete_list(delete->versions);
            delete->versions = next->versions;
            if(next->parent->left == next)
                next->parent->left = next->right;
            else
                next->parent->right = next->right;
            colour = next->colour;
            par = next->parent;
            next->parent = NULL;
            free(next);
            Elist.parent = par;
            if(colour == 1)
                rb_delete_fixup(&Elist, root);
        }
        printf("Element deleted\n");
    }
}

int delete_tree(Node *ptr){
    if(ptr == &Elist)
        return 0;
    delete_tree(ptr->left);
    delete_tree(ptr->right);
    delete_list(ptr->versions);
    free(ptr);
    return 0;
}

int print(int key1, int key2, Node *ptr){
    if(ptr == &Elist)
        return 0;
    print(key1, key2, ptr->right);
    if(ptr->key <= key2 && ptr->key >= key1) {
        printf("key: %d\n", ptr->key);
        print_all_versions(ptr->versions);
    }
    print(key1, key2, ptr->left);
    return 0;
}

int print_beaty_tree(Node *ptr, int probel){
    if(ptr == &Elist)
        return 0;
    print_beaty_tree(ptr->right, probel + 1);
    for(int i=0; i<probel;i++, printf("  "));
    printf("%d\n", ptr->key);
    print_beaty_tree(ptr->left, probel + 1);
    return 0;
}

Node *create_new(){
    Node *node;
    node = (Node *) calloc(1, sizeof(Node));
    node->colour = 0;
    node->left = &Elist;
    node->right = &Elist;
    node->parent = &Elist;
    return node;
}
