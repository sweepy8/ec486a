#include <stdio.h>
#include <stdlib.h>

int main(){
  int *p = (int*)malloc(sizeof(int));
  *p = 5;
  
  switch(*p){
  case 0:
    printf("0");
    break;
  case 1:
  case 2:
    printf("1,2");
    break;
  case 3:
  case 4:
  case 5:
    printf("3,4,5");
    break;
  default:
    printf("Other");
  }
  
  return 0;
}
