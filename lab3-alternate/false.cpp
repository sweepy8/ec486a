#include <iostream>
#include <thread>

using namespace std;

#define ITERS 2000000000

typedef struct vector3{
  int _x;
  int _y;
  int _z;
} Vector3;

void countN(int *p, int N){
  for(int c = 0; c < N; c++){
    (*p)++;
  }
}

int main(){
  vector3 v;
  v._x = 0;
  v._y = 0;
  v._z = 0;
  std::thread t1(countN,&v._x,ITERS);
  std::thread t2(countN,&v._y,ITERS);
  std::thread t3(countN,&v._z,ITERS);

  t1.join();
  t2.join();
  t3.join();

  cout << "(" << v._x << "," << v._y << "," << v._z << ")\n";
  
  return 0;
}
