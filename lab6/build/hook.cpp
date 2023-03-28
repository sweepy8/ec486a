#include <cstdio>

extern "C" void begin(char *name){
  printf("Starting function %s\n",name);
}

extern "C" void end(char *name){
  printf("Ending function %s\n",name);
}
