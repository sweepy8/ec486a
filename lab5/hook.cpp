#include <stdio.h>

extern "C" void begin(char *str){
  printf("Begin %s\n",str);
}

extern "C" void end(char *str){
  printf("End %s\n",str);
}
