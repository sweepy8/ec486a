#include <iostream>
#include <string>

using namespace std;

class Person
{
  int ssn;

protected:
  string name;

public:
  Person(int _ssn, string _name) : ssn(_ssn), name(_name)
  {
    cout << "Created person with ssn: " << ssn << endl;
  }

  ~Person(){
    cout << "Cleaned up person with ssn: " << ssn << endl;
  }

  string getName()
  {
    return name;
  }

  virtual void print()
  {
    cout << "Person: " << getName() << endl;
  }

  void changeName(string newName)
  {
     _name = newName;
  }
};

class MIDN : public Person
{
  int alpha;

private:
  static int nextAlpha;

public:
  MIDN(int _ssn, string _name, int _alpha) : Person(_ssn,_name), alpha(_alpha)
  {
    cout << "Created MIDN with alpha: " << alpha << endl;
    if(NULL)
    {
      cout << "Unable to create MIDN!" << endl;
    }
  }

  ~MIDN()
  {
    cout << "Cleaned up MIDN with alpha: " << alpha << endl;
  }

  int getAlpha()
  {
    return alpha;
  }

  void print()
  {
    cout << "Person: " << getName() << " Alpha: " << getAlpha() << endl;
  }
  static int getNextAlpha()
  {
    int myAlpha = nextAlpha;
    nextAlpha += 4;
    return myAlpha;
  }
};

int MIDN::nextAlpha = 260008;

int main(){
  Person p1(1111111111,"Dez");
  Person *p2 = new Person(555555555,"Jan");
  Person *m1 = new MIDN(123456789, "Apollo", 260004);

  // Your test cases below this line
  cout << endl;
  p1.print();
  p2->print();
  m1->print();

  MIDN *c2 = dynamic_cast<MIDN*>(m1);
  cout << MIDN::getNextAlpha() << endl;
  cout << c2->getNextAlpha() << endl;

  Person& r1 = p1;
  p1.print();
  r1.changeName();
  p1.print();

  // Cleanup code below this line
  cout << endl;
  delete p2;
  delete m1;

  return 0;
}
