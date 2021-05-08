#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "func.h"

int min(int a, int b){
    if(a <= b || b < 0)
        return a;
    else
        return b;
}

Queue *queue_new() {
    return (Queue *) calloc(1, sizeof(Queue));
}

void queue_delete(Queue *queue) {
    list *ptr = queue->head, *ptr_prev;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(queue);
}

int queue_put(Queue *queue, int ind) {
    list *new = (list *) malloc(sizeof(list));
    if (!new) {
        return -1;
    }
    new->index = ind;
    new->next = NULL;
    if (!queue->head) {
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }
    return 0;
}

int queue_get(Queue *queue, int *output) {
    if (!queue->head) {
        return -1;
    }
    *output = queue->head->index;
    if (queue->head == queue->tail) {
        queue->tail = NULL;
    }
    list *head = queue->head;
    queue->head = head->next;
    free(head);
    return 0;
}

int min_heapify(int *S, int *d, int i, int n){
    int l,r,largest, q;
    l = 2*i + 1;
    r = 2*i + 2;
    if(l >= n)
        return 0;
    else if(r >= n){
        if(d[S[i]] <= d[S[l]])
            largest = i;
        else
            largest = l;
    }
    else {
        if (d[S[i]] <= d[S[r]] && d[S[i]] <= d[S[l]])
            largest = i;
        else if (d[S[r]] < d[S[l]])
            largest = r;
        else
            largest = l;
    }
    if(largest != i){
        q = S[i];
        S[i] = S[largest];
        S[largest] = q;
        min_heapify(S,d, largest,n);
    }
    return 0;
}

int increase_key(int *S,int *d, int i, int k,int n){
    int q;
    if(d[i] < k)
        return 1;
    d[i] = k;
    int j=n/2;
    while(j>=0){
        min_heapify(S,d,j,n);
        --j;
    }
    return 0;
}

int extract_min(int **S, int *d, int *n){
    int res;
    if(*n == 0 || *S == NULL)
        return -1;
    res = (*S)[0];
    (*S)[0] = (*S)[*n-1];
    if(*n > 1){
		*S = (int *) realloc(*S, (*n-1)*sizeof(int));
    	*n = *n-1;
    	min_heapify(*S,d,0,*n);
	}
	else{
		free(*S);
		*S = NULL;
		*n = 0;
	}	
    return res;
}

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
        scanf("%d", &choice);
        //choice = getchar() - '0';
        while (getchar() != '\n') {}
    } while (choice < 0 || choice >= n);
    return choice;
}

int search_short_paths(int **d, int **p,vertex *adj, int n){
    int a[3]={INT_MAX,INT_MAX,INT_MAX},i,j,*path,s;
    coordinats min[3];
    for(i=1; i<=n; i++){
        for(j=1; j<=n; j++){
            if(i != j && d[i][j] != INT_MAX){
                if(d[i][j] < a[0]) {
                    a[2] = a[1];
                    min[2].x = min[1].x, min[2].y = min[1].y;
                    a[1] = a[0];
                    min[1].x = min[0].x, min[1].y = min[0].y;
                    a[0] = d[i][j];
                    min[0].x = i, min[0].y = j;
                }
                else if(d[i][j] < a[1]){
                    a[2] = a[1];
                    min[2].x = min[1].x, min[2].y = min[1].y;
                    a[1] = d[i][j];
                    min[1].x = i, min[1].y = j;
                }
                else if(d[i][j] < a[2]){
                    a[2] = d[i][j];
                    min[2].x = i, min[2].y = j;
                }
            }
        }
    }
    if(a[0] == INT_MAX){
        return -1;
    }
    for(i=0; i<3; i++){
        if(a[i] != INT_MAX) {
            printf("Path1 %d -> %d:\n", min[i].x, min[i].y);
            j = min[i].y;
            s = d[min[i].x][min[i].y];
            path = (int *) malloc((s + 1) * sizeof(int));
            path[0] = min[i].x - 1;
            path[s] = min[i].y - 1;
            s--;
            while (p[min[i].x][j] != min[i].x) {
                path[s] = p[min[i].x][j] - 1;
                s--;
                j = p[min[i].x][j];
            }
            for (j = 0; j < d[min[i].x][min[i].y]; j++) {
                printf("%d->", adj[path[j]].id);
            }
            printf("%d", adj[min[i].y - 1].id);
            printf(", d = %d\n", d[min[i].x][min[i].y]);
            free(path);
        }
        else{
            printf("Sorry, you don`t have any path\n");
            return 0;
        }
    }
    return 0;
}

int search_vert(int id, vertex *adj, int n){
    int ind=-1;
    for(int i=0; i<n && ind == -1; i++)
        if(adj[i].id == id)
            ind = i;
    return ind;
}

int add_elem(list **head, int ind2){
    list *ptr, *new;
    new = (list *) calloc(1, sizeof(list));
    new->index = ind2;
    if(*head == NULL) {
        *head = new;
    }
    else{
        ptr = *head;
        while(ptr->next != NULL){
            if(ptr->index == ind2){
                free(new);
				return 1;
			}	
            ptr = ptr->next;
        }
        if(ptr->index == ind2){
            free(new);
			return 1;
		}	
        else {
            ptr->next = new;
        }
    }
    return 0;
}

int delete_elem(list **head, int ind){
    list *ptr = *head, *del;
    if(*head == NULL)
        return -1;
    else if((*head)->index == ind){
        del = *head;
        *head = del->next;
        free(del);
    }
    else {
        while (ptr->next->index != ind) {
            if(ptr->next == NULL)
                return -1;
            ptr = ptr->next;
        }
        del = ptr->next;
        ptr->next = del->next;
        free(del);
    }
    return 0;
}

int add_vert(int id, coordinats v, vertex **adj, int n){
    if(n == 0){
        *adj = (vertex *) calloc(1, sizeof(vertex));
        (*adj)[0].id = id, (*adj)[0].coord = v;
		(*adj)[0].adj = NULL;
    }
    else{
        for(int i=0; i< n; i++){
            if((*adj)[i].id == id)
                return 1;
        }
        *adj = (vertex *) realloc(*adj, (n+1)*sizeof(vertex));
        (*adj)[n].id = id;
        (*adj)[n].coord = v;
        (*adj)[n].adj = NULL;
    }
    return 0;
}

int delete_vert(int id, coordinats v, vertex **adj, int *n){
    list *ptr, *ptr2, *del;
    int ind1 = -1, ind2 = -1, i;
    if(*n == 0)
        return -1;
    else {
        for (i = 0; i< *n && ind1 == -1; i++){
            if((*adj)[i].id == id)
                ind1 = i;
        }
        if(ind1 == -1)
            return -2;
        ptr = (*adj)[ind1].adj;
        while(ptr != NULL){
            if(ptr->index != ind1)
                delete_elem(&(*adj)[ptr->index].adj, ind1);
            del = ptr;
            ptr = del->next;
            free(del);
        }
        if(*n == 1) {
            free(*adj);
            *n = 0;
        }
        else{
            if(ind1 != *n -1) {
                (*adj)[ind1] = (*adj)[*n - 1];
                ind2 = *n - 1;
                ptr = (*adj)[ind1].adj;
                while (ptr != NULL) {
                    if (ptr->index == ind2)
                        ptr->index = ind1;
                    else {
                        ptr2 = (*adj)[ptr->index].adj;
                        while (ptr2->index != ind2)
                            ptr2 = ptr2->next;
                        ptr2->index = ind1;
                    }
                    ptr = ptr->next;
                }
            }
            *adj = (vertex *) realloc(*adj, (*n-1)*sizeof(vertex));
            *n = *n-1;
        }
    }
    return 0;
}

int delete_edge(int id1, int id2, vertex *adj, int n){
    int ind1=-1, ind2=-1, i;
    if(n == 0)
        return -1;
    else {
        for(i=0; i<n && (ind1 == -1 || ind2 == -1);i++){
            if(adj[i].id == id1)
                ind1 = i;
            if(adj[i].id == id2)
                ind2 = i;
        }
        if(ind1 == -1 || ind2 == -1)
            return -2;
        if(delete_elem(&adj[ind1].adj, ind2) == -1)
            return -2;
        if(ind1 != ind2)
            if(delete_elem(&adj[ind2].adj, ind1) == -1)
                return -2;
    }
    return 0;
}

int add_edge(int id1, int id2, vertex **adj, int n){
    int ind1=-1, ind2=-1, i;
    list *ptr;
    if(n == 0)
        return -1;
    else{
        for(i=0; i<n && (ind1 == -1 || ind2 == -1);i++){
            if((*adj)[i].id == id1)
                ind1 = i;
            if((*adj)[i].id == id2)
                ind2 = i;
        }
        if(ind1 == -1 || ind2 == -1)
            return -2;
        if(add_elem(&(*adj)[ind1].adj, ind2) == 1)
            return 1;
        if(ind1 != ind2)
            if(add_elem(&(*adj)[ind2].adj, ind1) == 1)
            return 1;
    }
    return 0;
}

int BFS(int id1, int id2, vertex *adj, int n){
    int color[n], pred[n], d[n], u, *path, i;
    int ind = search_vert(id1, adj,n), v = search_vert(id2, adj, n);
    if(ind == -1 || v == -1)
        return -1;
    list *ptr;
    Queue *q = queue_new();
    for(i=0;i<n; i++){
        color[i] = 0; ///white
        d[i] = INT_MAX;
        pred[i] = -1;
    }
    color[ind] = 1; ///grey
    d[ind] = 0;
    queue_put(q, ind);
    while(queue_get(q, &u) != -1){
        ptr = adj[u].adj;
        while(ptr != NULL){
            if(color[ptr->index] == 0){
                color[ptr->index] = 1;
                d[ptr->index] = d[u] +1;
                pred[ptr->index] = u;
                queue_put(q, ptr->index);
            }
            ptr = ptr->next;
        }
        color[u] = 2; ///black
    }
    queue_delete(q);
    if(d[v] == INT_MAX)
        return -2;
    path = (int *)calloc(d[v]+1, sizeof(int));
    ind = v;
    path[d[ind]] = adj[ind].id;
    while(d[ind] != 0){
        path[d[ind]-1] = adj[pred[ind]].id;
        ind = pred[ind];
    }
    for(i=0; i<d[v]; i++)
        printf("%d->", path[i]);
    printf("%d\n",path[d[v]]);
    free(path);
    i = d[v];
    //free(pred), free(d), free(color);
    return i;
}

int Dijkstra(int id1, int id2, vertex *adj, int n){
    int *S, *pred, *d, *Q, u, *path, i, k = n, ind;
    int s = search_vert(id1, adj,n), v = search_vert(id2, adj, n);
    list *ptr;
    if(s == -1 || v == -1)
		return -1;
	S = (int *) calloc(n, sizeof(int));
	pred = (int *) calloc(n, sizeof(int));
	d = (int *) calloc(n, sizeof(int));
	Q = (int *) calloc(n, sizeof(int));
    for(i=0; i<n; i++){
        d[i] = INT_MAX;
        pred[i] = -1;
    }
    for(i =0; i< k; Q[i] = i, i++);
    increase_key(Q,d,s,0,k);
    while( k > 0){
        u = extract_min(&Q, d, &k);
        S[k] = u;
        ptr = adj[u].adj;
        while(ptr != NULL){
            if(d[ptr->index] - 1 > d[u]) {
                increase_key(Q, d, ptr->index, d[u]+1,k);
                pred[ptr->index] = u;
            }
            ptr = ptr->next;
        }
    }
    if(d[v] == INT_MAX){
        free(pred), free(S), free(d);
		return -2;
	}	
    path = (int *)calloc(d[v]+1, sizeof(int));
    ind = v;
    path[d[ind]] = adj[ind].id;
    while(d[ind] != 0){
        path[d[ind]-1] = adj[pred[ind]].id;
        ind = pred[ind];
    }
    for(i=0; i<d[v]; i++)
        printf("%d->", path[i]);
    printf("%d\n",path[d[v]]);
    free(path);
    //free(Q);
    i = d[v];
    free(pred), free(S), free(d);
    return i;
}

int Floyd_Warshall(vertex *adj, int n){
    int **d, **p, **d1, **p1, k, i, j;
    d = (int **) calloc(n+1, sizeof(int *));
    d1 = (int **) calloc(n+1, sizeof(int *));
    p = (int **) calloc(n+1, sizeof(int *));
    p1 = (int **) calloc(n+1, sizeof(int *));
    for(i=0; i<=n; i++){
        d[i] = (int *) calloc(n+1, sizeof(int));
        d1[i] = (int *) calloc(n+1, sizeof(int));
        p[i] = (int *) calloc(n+1, sizeof(int));
        p1[i] = (int *) calloc(n+1, sizeof(int));
    }
    list *ptr;
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            if(i != j)
                d[i][j] = INT_MAX;
    for(i=1; i<=n; i++){
        ptr = adj[i-1].adj;
        while(ptr != NULL) {
            d[i][ptr->index+1] = 1;
            ptr = ptr->next;
        }
    }
    for(i=1; i<=n; i++){
        for(j=1; j<=n; j++){
            if(d[i][j] == INT_MAX || i==j)
                p[i][j] = -1;
            else
                p[i][j] = i;
        }
    }
    for(k=1; k<=n; k++){
        for(i=1; i<=n; i++){
            for(j=1; j<=n; j++){
                if(k % 2 != 0){
                    if(d[i][j] == INT_MAX && (d[i][k] == INT_MAX || d[k][j] == INT_MAX))
                        d1[i][j] = INT_MAX;
                    else
                        d1[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    if(d1[i][j] == d[i][j])
                        p1[i][j] = p[i][j];
                    else
                        p1[i][j] = p[k][j];
                }
                else{
                    if(d1[i][j] == INT_MAX && (d1[i][k] == INT_MAX || d1[k][j] == INT_MAX))
                        d[i][j] = INT_MAX;
                    else
                        d[i][j] = min(d1[i][j], d1[i][k] + d[k][j]);
                    if(d[i][j] == d1[i][j])
                        p[i][j] = p1[i][j];
                    else
                        p[i][j] = p1[k][j];
                }
            }
        }
    }

    if(n % 2 != 0) {
        j = search_short_paths(d1, p1, adj, n);
    }
    else {
        j = search_short_paths(d, p, adj, n);
    }
    for(i=0; i<=n; i++) {
        free(d[i]), free(d1[i]), free(p[i]), free(p1[i]);
    }
    free(d), free(d1), free(p), free(p1);
    return j;
}

void print_graph(vertex *adj, int n){
    list *ptr;
    if(n == 0)
        printf("Empty\n");
    else {
        for (int i = 0; i < n; i++) {
            printf("%d: (%d,%d) ",adj[i].id, adj[i].coord.x, adj[i].coord.y);
            ptr = adj[i].adj;
            if(ptr != NULL)
                printf("-> ");
            while (ptr != NULL) {
                printf("%d; ", adj[ptr->index].id);
                ptr = ptr->next;
            }
            printf("\n");
        }
        printf("\n");
    }
}

void generate_graph(vertex **adj, int n, int q){
    int size = 0,E=0, i = n*(n-1)/2, id1, id2;
    coordinats v1;
    if((*adj) != NULL ){
		delete_graph(*adj, q);
    	*adj = NULL;
	}
    srand(time(NULL));
    while(size != n){
        v1.x = (rand() % (2*n)) - n;
        v1.y = (rand() % (2*n)) - n;
        id1 = size+1;
        if(add_vert(id1, v1, adj, size) == 0)
            size ++;
    }
    i = rand() % (i+1);
    while(E < i){
        id1 = (*adj)[rand() % n].id;
        id2 = (*adj)[rand() % n].id;
        if(add_edge(id1, id2, adj, n) == 0)
            E ++;
    }
}

int load_from_file(vertex **adj, int *n){
    int i, id1, id2, size=0;
    coordinats v;
    FILE *input;
    if(*adj != NULL){
		free(*adj);
    	*adj = NULL;
	}
    input = fopen("graph.bin", "r+b");
    if(input == NULL)
        return -1;
    fread(n, sizeof(int), 1, input);
    for(i = 0; i < *n; i++){
        fread(&id1, sizeof(int), 1, input);
        fread(&v.x, sizeof(int), 1, input);
        fread(&v.y, sizeof(int), 1, input);
        add_vert(id1, v, adj, size);
        size ++;
    }
    do{
        fread(&id1, sizeof(int), 1, input);
        fread(&id2, sizeof(int), 1, input);
        if(!feof(input))
            add_edge(id1, id2, adj, *n);
    }while(!feof(input));
    fclose(input);
    return 0;
}

void load_to_file(vertex *adj, int n){
    int i;
    list *ptr;
    FILE *input;
    input = fopen("graph.bin", "wb");
    fwrite(&n, sizeof(int), 1, input);
    for(i=0; i<n; i++){
        fwrite(&adj[i].id, sizeof(int), 1, input);
        fwrite(&adj[i].coord.x, sizeof(int), 1, input);
        fwrite(&adj[i].coord.y, sizeof(int), 1, input);
    }
    for(i=0; i<n; i++){
        ptr = adj[i].adj;
        while(ptr != NULL){
            if(ptr->index >= i){
                fwrite(&adj[i].id, sizeof(int), 1, input);
                fwrite(&adj[ptr->index].id, sizeof(int), 1, input);
            }
            ptr = ptr->next;
        }
    }
    fclose(input);
}

int graphiz(vertex *adj, int n){
    int i,q;
    list *ptr;
    FILE *input;
    input = fopen("graphiz.txt", "w");
    fprintf( input, "Graph{\n");
    for(i=0; i<n; i++){
        fprintf(input, "%d", adj[i].id);
        ptr = adj[i].adj;
        q = 0;
        while(ptr != NULL){
            if(ptr->index >= i){
                if(q == 0) {
                    q = 1;
                    fprintf(input, " -- ");
                }
                fprintf(input, "%d", adj[ptr->index].id);
                if(ptr->next != NULL)
                    fprintf(input, ", ");
            }
            ptr = ptr->next;
        }
        fprintf(input, ";\n");
    }
    fprintf(input, "}");
    fclose(input);
    return 0;
}

void delete_graph(vertex *adj, int n){
    list *ptr;
	if(n != 0){
    	for (int i = 0; i < n; i++) {
        	if(adj[i].adj != NULL) {
            	while (adj[i].adj->next != NULL) {
                	ptr = adj[i].adj->next;
                	adj[i].adj->next = ptr->next;
                	free(ptr);
            	}
            	free(adj[i].adj);
        	}
    	}
    	free(adj);
	}
}
