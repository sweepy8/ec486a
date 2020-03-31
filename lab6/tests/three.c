#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  if(argc < 2){
    printf("Usage: %s [x]\n",argv[0]);
    return 1;
  }

  int result;
  int x = atoi(argv[1]);
  int y = 6;
  int z = 3;

  x = x * 2;
  z = z - y;
  result = x + y + z;

  printf("%d\n",result);

  return 0;
}
