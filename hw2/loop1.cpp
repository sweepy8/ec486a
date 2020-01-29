#include <iostream>

#define M 10
#define N 100

int main(){
  int arr[N];
  int sum = 0;

  for(int c = 0; c < N; c++){
    arr[c] = c;
  }

  for(int c = 0; c < M; c++){
    sum += arr[c];
  }

  std::cout << sum << "\n";
  
  return 0;
}
