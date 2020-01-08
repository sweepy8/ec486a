#include <iostream>

using namespace std;

class A{
  int _a;

public:
  virtual void foo(){
    cout << "FooA";
  }

  void bar(){
    cout << "BarA";
  }
};

class B : public A{
  int _b;

public:
  virtual void foo(){
    cout << "FooB";
  }

  void bar(){
    cout << "BarB";
  }
};

class C : public A{
  char _c;
public:
  virtual void foo(){
    cout << "FooC";
  }

  void bar(){
    cout << "BarC";
  }
};

int main(){
  A *obj1 = new A;
  A *obj2 = new B;
  A *obj3 = new C;

  // Answer each question based on adding the specified line(s) of code here
  
  return 0;
}
