#include <iostream>
#include <string>

using namespace std;

class Person{
  int ssn;

protected:
  string name;

public:
  Person(int _ssn, string _name) : ssn(_ssn), name(_name) {
    cout << "Created person with ssn: " << ssn << endl;
  }

  ~Person(){
    cout << "Cleaned up person with ssn: " << ssn << endl;
  }
  
  string getName(){
    return name;
  }
};

class MIDN{
  int alpha;
  
public:
  MIDN(int _alpha) : alpha(_alpha) {
    cout << "Created MIDN with alpha: " << alpha << endl;
  }

  ~MIDN(){
    cout << "Cleaned up MIDN with alpha: " << alpha << endl;
  }
  
  int getAlpha(){
    return alpha;
  }
};

int main(){
  Person p1(1111111111,"Dez");  
  Person *p2 = new Person(555555555,"Jan");
  MIDN *m1 = new MIDN(260004);
  
  // Your test cases below this line


  // Cleanup code below this line

  
  return 0;
}
