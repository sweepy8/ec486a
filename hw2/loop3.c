#include <iostream>

#define M 10
#define N 100

int main(){
  int arr[N][N];
  int result[N][N];
  int sum = 0;

  for(int c = 0; c < N; c++){
    for(int d = 0; d < N; d++){
      arr[c][d] = c+d;
    }
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      result[i][j] = 0;
      for(int k = 0; k < N; k++){
	result[i][j] += arr[i][k] * arr[k][j];
      }
    }
  }

  for(int c = 0; c < M; c++){
    sum += result[c][c];
  }

  std::cout << sum << "\n";
  
  return 0;
}
