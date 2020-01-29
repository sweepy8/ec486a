#include <iostream>

#define M 10
#define N 100

int main(){
  int arr[N][N];
  int sum = 0;

  for(int c = 0; c < N; c++){
    for(int d = 0; d < N; d++){
      arr[c][d] = c+d;
    }
  }

  for(int c = 0; c < M; c++){
    sum += arr[c][c];
  }

  std::cout << sum << "\n";
  
  return 0;
}
