#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int fib(int fib0, int fib1, int n){
    if(n==0)
        return fib0;
    if(n==1)
        return fib1;

    return fib(fib0, fib1, n-1)+fib(fib0, fib1, n-2);
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < N; i++) {
        int val = fib(1,1,i);
        printf("fib(%d)=%d\n", i, val);
    }
    return 0;
}
