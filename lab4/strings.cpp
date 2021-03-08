#include <cstring>
#include <iostream>

using namespace std;

int main(){
  char src[12] = "Test String";
  char dst[5];

  strcpy(dst,src);
  cout << dst << "\n";
  
  return 0;
}
