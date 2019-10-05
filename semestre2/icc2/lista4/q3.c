#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void sort(char *vec);

int main(int argc, char const *argv[])
{
    char vec[] = "ABBBBBAABBBB";
    printf("%s\n",vec);
    sort(vec);
    printf("%s\n",vec);
    return 0;
}

void sort(char *vec){
    int size = strlen(vec);
    int i = 0;
    int j = size-1;
    while(i<j){
        while(vec[i]!='B' && i<size-1){
            i++;
        }
        while(vec[j]!='A' && j>0){
            j--;
        }
        if(i<j){
            vec[i]='A';
            vec[j]='B';
        }
    }
}
