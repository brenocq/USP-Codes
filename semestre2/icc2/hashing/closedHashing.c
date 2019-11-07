#include <stdlib.h>
#include <stdio.h>

#define SIZE 100
#define EMPTY -32000

int hash[SIZE];

void insert(int val);
int search(int val);
void print();

int main(int argc, char const *argv[]) {
  for (size_t i = 0; i < SIZE; i++) {
    hash[i]=EMPTY;
  }
  insert(100);
  insert(1);
  insert(2);
  insert(5);
  insert(51);
  insert(101);
  insert(102);
  print();
  printf("Key: %d\n", search(51));

  return 0;
}

void insert(int val){
  int hashKey = val%SIZE;
  for (; hash[hashKey]!=EMPTY; hashKey++);
  hash[hashKey]=val;
}

int search(int val){
  int ini = val%SIZE;
  int hashKey = val%SIZE;
  while(hash[hashKey]!=EMPTY){
    if(hash[hashKey]==val)
      return hashKey;
    hashKey++;
    if(hashKey==ini){
      return -1;
    }
  }
  return -1;
}

void print(){
  for (int i = 0; i < SIZE; i++) {
    if(hash[i]==EMPTY)
      printf(".\t");
    else
      printf("%d\t", hash[i]);
    if((i+1)%10==0)
      printf("\n");
  }
  printf("\n");
}
