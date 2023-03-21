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

template <class T> class Logger
{
  T *obj;

public:
  Logger(T *_obj) : obj(_obj) {
  }

  ~Logger(){
  }

  void log(){
    cout << obj->getClassName() << endl;
  }
};

template <> class Logger<int>
{
  public:
    Logger(int *x) {}

    ~Logger() {}

    void log()
    {
      cout << "int" << endl;
    }
};

int main(){
  Person *p = new Person();
  MIDN *m = new MIDN();
  Logger<Person> *l1 = new Logger<Person>(p);
  Logger<MIDN> *l2 = new Logger<MIDN>(m);

  l1->log();
  l2->log();

  return 0;
}
