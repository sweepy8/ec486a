#include <iostream>

using namespace std;

class Person{
public:
  string getClassName(){
    return "Person";
  }
};

class MIDN{
public:
  string getClassName(){
    return "MIDN";
  }
};

class Logger{
  Person *obj;

public:
  Logger(Person *_obj) : obj(_obj) {
  }

  ~Logger(){
  }
  
  void log(){
    cout << obj->getClassName() << endl;
  }
};

int main(){
  Person *p = new Person();
  MIDN *m = new MIDN();
  Logger *l1 = new Logger(p);

  l1->log();
  
  return 0;
}
