//Вариант 11, алгоритм Round-Robin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

int num(int number){
    int a,b=0;
    a = number;
    while(a != 0){
        a /= 10;
        b++;
    }
    return b;
}

char *get_str() {
    char buf[81] = {0};
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
            int chunk_len = (int) strlen(buf);
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

int obrabotka(Fare* passanger)
{
    char *ptr1 = get_str();
    char *ptr = ptr1;
    printf("%s\n",ptr);
    int p, number, k;
    sscanf(ptr, "%d", &number);
    k = num(number) +1;
    int len= (int) strlen(ptr);
    ptr=ptr+k;
    for (int i=0;k<len;i++)
    {
        for (int j=0;(*ptr)!='/';ptr++,j++)
        {
            k++;
            passanger[i].id[j] = *ptr;
        }
        ptr++;
        k++;
        sscanf(ptr,"%d",&p);
        while(*ptr!='/')
        {
            ptr++;
            k++;
        }
        ptr++;
        k++;

        passanger[i].ta=p;
        p=0;
        sscanf(ptr,"%d",&p);
        while(*ptr!=' ' && *(ptr + 1))
        {
            ptr++;
            k++;
        }
        ptr++, k++;
        passanger[i].ts=p;

    }
    free(ptr1);
    return number;
}

void insertionSort(Fare *ptr){
    Fare temp;
    int item;
    for (int counter = 1; ptr[counter].ta != 0 ; counter++){
        temp = ptr[counter];
        item = counter-1;
        while(item >= 0 && ptr[item].ta > temp.ta){
            ptr[item + 1] = ptr[item];
            ptr[item] = temp;
            item--;
        }
    }
}

void airport(Queue ** queues, Fare *p, int n){
    int numb =0;
    Fare *pas;
    for(int i=1, reg = 0, flag=0; p->ta != 0 || numb != 0; i++, flag = 0){
        while(p->ta != 0 && p->ta == i){
            queue_put(queues[reg], *p);
            p++;
            reg = (reg + 1) % n;
            numb++;
            flag = 1;
        }
        for(int registr=0; registr < n; registr++){
            if(queues[registr]->num) {
                pas = queue_get(queues[registr]);
                if(pas->ta + pas->ts == i) {
                    queue_pop(queues[registr]);
                    if(queues[registr]->num)
                        pas = queue_get(queues[registr]);
                    pas->ta = i;
                    numb--;
                    flag = 1;
                }
            }
        }
        if(flag == 1){
            printf("\n%d\n", i);
            for(int registr=0; registr < n; registr++) {
                printf("#%d ", registr+1);
                queue_print(queues[registr]);
            }
        }
    }
}

int main() {
    int n;
    Fare passanger[100] = {};
    n = obrabotka(passanger);
    insertionSort(passanger);
    Fare *p = passanger;
    Queue ** queues;
    queues = (Queue **) calloc(n, sizeof(Queue*));
    for(int i = 0; i < n; i++){
        queues[i] = queue_new();
    }

    airport(queues, p, n);

    for(int i = 0; i < n; i++){
        queue_delete(queues[i]);
    }
    free(queues);
    return 0;
}
