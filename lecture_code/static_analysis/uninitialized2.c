#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int x;
  int y;

  if(argc < 2){
    printf("Usage: %s [number]\n",argv[0]);
    return 1;
  }

  int value = atoi(argv[1]);

  if(value < 10){
    x = 2;
  }
  
  y = x + 5;
  
  return 0;
}
