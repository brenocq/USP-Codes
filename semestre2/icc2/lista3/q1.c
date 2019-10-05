#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

#define N 3

void comb(int n, char* str){
    char* str2 = (char*)malloc(sizeof(char)*(N+1));
    int size;

    strcpy(str2, str);
    size = strlen(str2);

    if(n==size){
        printf("%s\n", str2);
        free(str2);
        return;
    }
    
    for(int i=0;i<n;i++){
        char letra = 'A'+i;

        char *p = strchr( str, letra);
        if(p==NULL){
            str2[size]=letra;
            str2[size+1]='\0';
            comb(n, str2);
        }
    }
    free(str2);
}

int main(int argc, char const *argv[])
{
    char* str = (char*)malloc(sizeof(char)*(N+1));
    comb(N, str);
    free(str);
    return 0;
}
