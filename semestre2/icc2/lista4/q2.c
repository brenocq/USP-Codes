#include <stdlib.h>
#include <stdio.h>

int maximo(int vec[], int ini, int fim);

int max(int a, int b){return a>=b?a:b;}

#define SIZE 5

int main(int argc, char const *argv[])
{
    int vec[SIZE] = {5,2,9,1,0};
    printf("%d\n",maximo(vec,0,SIZE-1));
    return 0;
}

int maximo(int vec[], int ini, int fim){
    if(ini==fim){
        return vec[ini];
    }else{
        int meio = (ini+fim)/2;
        int a = maximo(vec, ini, meio);
        int b = maximo(vec, meio+1, fim);
        return max(a,b);
    }
}
