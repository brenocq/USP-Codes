#include <stdlib.h>
#include <stdio.h>

#define SIZE 10

int binarySearch(int *vec, int num, int start, int end);

int main(int argc, char const *argv[])
{
    int vec[SIZE] = {1,3,4,6,7,8,9,10,15,17};
   
    int res = binarySearch(vec, 9, 0, SIZE-1);
    printf("%d\n",res);
    return 0;
}

int binarySearch(int *vec, int num, int start=0, int end=SIZE-1){
    if(start==end)
        return start;
    else{
        int middle = (start+end)/2;
        if(vec[middle]>=num){
            return binarySearch(vec, num,start, middle);
        }else{
            return binarySearch(vec, num,middle+1, end);
        }
    }
}