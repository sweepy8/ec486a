class A{
  int _a;

public:
  virtual void foo(){
  }

  void bar(){
  }
};

class B : public A{
  int _b;

public:
  virtual void foo(){
  }

  void bar(){
  }
};

class C : public A{
  char _c;
public:
  virtual void foo(){
  }

  void bar(){
  }
};

int main(){
  A *obj1 = new A;
  A *obj2 = new B;
  A *obj3 = new C;

  /*
   * For each of the CXXMethod calls below, your tool should
   * print which dynamic method it will call.  (e.g. Line 43 calls A::foo())
   */
  
  obj1->foo();
  obj1->bar();

  obj2->foo();
  obj2->bar();

  obj3->foo();
  obj3->bar();
  
  return 0;
}
