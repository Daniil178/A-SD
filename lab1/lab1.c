#include <stdio.h>
#include <stdlib.h>

typedef struct line{
    int n;
    int *row;
}line;

typedef struct matrix{
    int rows;
    line *matr;
}matrix;

void vect_A(int *A, matrix mat){
    for(int  i = 0; i< mat.rows; ++i){
        A[i] = 0;
        for(int j = 0; j< mat.matr[i].n; ++j){
            if(mat.matr[i].row[j] % 2 ==0)
                A[i] += mat.matr[i].row[j];
        }
    }

}

void vect_B(int *A, matrix mat){
    int i,j,k = 0;
    for(i = 0; i< mat.rows; ++i){
        A[i] = 0;
        for(j = 0; j< mat.matr[i].n; ++j){
            k = mat.matr[i].row[j];
            while(k != 0 && k%10 != 0){
                k /=10;
            }
            if(k == 0)
                A[i] += mat.matr[i].row[j];
        }
    }
}

void del_mat(matrix mat){
    for(int i = 0; i < mat.rows; ++i)
        free(mat.matr[i].row);
    free(mat.matr);
}

void print_mat(matrix mat){
    int i,j;
    for(i = 0; i < mat.rows; ++i){
        for(j = 0; j < mat.matr[i].n; ++j){
            printf("%d ", mat.matr[i].row[j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_v(int *A, int rows){
    for(int i=0; i<rows; ++i)
        printf("%d ", A[i]);
    printf("\n");
}

void getInt(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if( n <= 0){
            while(getchar() != '\n');
            printf("Error, try again: ");
        }
    }while(n <= 0);
}

void input(matrix mat){
    int i,j,m=0;
    for(i = 0; i < mat.rows; i++){
        printf("Please, enter n%d: ", i+1);
        do{
            getInt(&m);
            if(m <= 0)
                printf("Error, try again: ");
        }while(m <= 0);
        mat.matr[i].n = m;
        mat.matr[i].row = (int *) calloc(m, sizeof(int));
        printf("Please, enter row %d: ", i+1);
        for(j = 0; j < m; ++j){
            getInt(&mat.matr[i].row[j]);
        }
    }
    printf("Matrix:\n");
    print_mat(mat);
}

int main(){
    int *A;
    int *B;
    int m=0;
    matrix mat;
    printf("Please, enter number rows: ");
    do{
        getInt(&m);
        if(m <= 0)
            printf("Error, try again: ");
    }while(m <= 0);
    mat.rows = m;
    mat.matr = (line *) calloc(mat.rows, sizeof(line));
    input(mat);
    A = calloc(mat.rows, sizeof(int));
    vect_A(A, mat);
    printf("Vector chetn number:\n");
    print_v(A, mat.rows);
    B = calloc(mat.rows, sizeof(int));
    vect_B(B, mat);
    printf("Vector without zero in number:\n");
    print_v(B, mat.rows);
    del_mat(mat);
    free(A);
    free(B);
    return 0;
}
