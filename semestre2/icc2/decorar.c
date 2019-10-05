#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void inserçãoSimples(int vec[]);
void quickSort(int vec[], int begin, int end);
int binarySearch(int vec[], int begin, int end, int find);

int main(int argc, char const *argv[])
{
    int vec[SIZE] = {5,2,4,3,1};

    for (int i = 0; i < SIZE; i++)
    printf("%s%d%s",i==0?"(":"",vec[i],i==SIZE-1?")\n":", ");

    //shellSort(vec);
    quickSort(vec, 0, SIZE);

    for (int i = 0; i < SIZE; i++)
    printf("%s%d%s",i==0?"(":"",vec[i],i==SIZE-1?")\n":", ");

    printf("BINARY: %d\n",  binarySearch(vec, 0, SIZE-1, 1));

    return 0;
}

void inserçãoSimples(int vec[]){
    int i,j,x;
    for (int i = 1; i < SIZE; i++){
        j = i-1;
        x = vec[i];
        while(j>=0 && vec[j]>x){
            vec[j+1]=vec[j];
            j--;
        }
        vec[j+1]=x;
    }
}

void quickSort(int vec[], int begin, int end){
    int i = begin;
    int j = end-1;
    int pivo = vec[(i+j)/2];
    while(i<=j){
        while(i<end && vec[i]<pivo){
            i++;
        }
        while(j>begin && vec[j]>pivo){
            j--;
        }
        if(i<=j){
            int aux = vec[i];
            vec[i]=vec[j];
            vec[j]=aux;
            j--;
            i++;
        }
    }
    if(j>begin){
        quickSort(vec, begin, j+1);
    }
    if(i<end){
        quickSort(vec, i, end);
    }
}

int binarySearch(int vec[], int begin, int end, int find){
    int middle = (begin+end)/2;
    if(end==begin){
        if(vec[begin]==find)
            return begin;
        else return -1;
    }
    else if(vec[middle]<find){
        binarySearch(vec, middle+1, end,find);
    }else{
        binarySearch(vec, begin, middle,find);
    }
}