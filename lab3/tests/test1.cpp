#include <cstdlib>
#include <iostream>
#include <vector>

#define BIGN 50000
#define SMALLN 10

using namespace std;

void bubbleSort(vector<int> v, int n) { 
  if (n == 1){
    return;
  }
  
  for (int c = 0; c < n-1; c++){
    if (v[c] > v[c+1]){
      int tmp = v[c];
      v[c] = v[c+1];
      v[c+1] = tmp;
    }
  }
  
  bubbleSort(v, n-1); 
} 

int main(){
  vector<int> v1;
  vector<int> v2;

  for(int c = 0; c < BIGN; c++){
    v1.push_back(rand() % 1000);
  }

  for(int c = 0; c < SMALLN; c++){
    v2.push_back(rand() % 1000);
  }

  bubbleSort(v1,v1.size());
  bubbleSort(v2,v2.size());

  // This line is here to keep the compiler from
  // optimizing away all of the work
  cout << v1[0] << "," << v2[0] << "\n";
  
  return 0;
}
