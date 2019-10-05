#include <stdlib.h>
#include <stdio.h>

#define SIZE 10

int ternarySearch(int *vec, int num, int start, int end);

int main(int argc, char const *argv[])
{
    int vec[SIZE] = {1,3,4,6,7,8,9,10,15,17};
   
    int res = ternarySearch(vec, 9, 0, SIZE-1);
    printf("%d\n",res);
    return 0;
}

int ternarySearch(int *vec, int num, int start, int end){
    if(start>=end)
        return end;
    else{
        int middle1 = (start+end)/3;
        int middle2 = (start+end)/3*2;
        middle1<start?middle1=start:middle1;
        middle2>end?middle2=end:middle2;
        //printf("[%d-%d] m1:%d m2:%d\n",start,end,middle1,middle2);
        if(vec[middle1]>=num){
            //printf("1\n");
            return ternarySearch(vec, num,start, middle1);
        }else if(vec[middle2]>=num){
            //printf("2\n");
            return ternarySearch(vec, num,middle1+1, middle2);
        }else{
            //printf("3\n");
            return ternarySearch(vec, num,middle2+1, end);
        }
    }
    return 0;
}