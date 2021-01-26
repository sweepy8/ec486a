#include <chrono>
#include <iostream>
#include <cstdlib>

class Vector{
protected:
  float x;
  float y;
  float z;
  
public:
  Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  
  virtual void add(Vector *other){
    x = x + other->getX();
    y = y + other->getY();
    z = z + other->getZ();
  }

  float getX(){
    return x;
  }

  float getY(){
    return y;
  }

  float getZ(){
    return z;
  }

  float sum(){
    return x + y + z;
  }
};

// This is just here to force virtual methods for performance and code tracking
class NormalizedVector : public Vector{
public:
  NormalizedVector(float _x, float _y, float _z) : Vector(_x,_y,_z) {}
  
  void add(Vector *other){
    x = x + other->getX();
    y = y + other->getY();
    z = z + other->getZ();
  }
};

int main(int argc, char **argv){
  if(argc < 2){
    std::cout << "Usage: " << argv[0] << " [iterations]\n";
    return 1;
  }

  int N = atoi(argv[1]);

  Vector **v = new Vector*[N];
  
  for(int c = 0; c < N; c++){
    v[c] = new NormalizedVector(rand()%10,rand()%10,rand()%10);
  }

  Vector plus1(1,1,1);
  
  // TODO: Time just this part
  for(int c = 1; c < N; c++){
    v[c]->add(&plus1);
  }
  // TODO: Stop timing here
  
  // This is here to prevent optimization
  float total = 0.0;
  for(int c = 0; c < N; c++){
    total += v[c]->sum();
  }
  std::cout << total << "\n";
  
  return 0;
}
