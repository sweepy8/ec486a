#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main(){
  std::vector<int> v;
  std::set<int> s;
  std::list<int> l;
  std::map<string,int> m;

  v.push_back(5);
  v.push_back(10);
  v.push_back(15);

  for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
    cout << *it << endl;
  }

  l.push_back(2);
  l.push_back(4);
  l.push_back(6);
  l.push_back(8);

  // Add the for loop that iterates through the list here


  
  m["IfStmt"] = 0;
  m["Stmt"] = 20;
  m["ForStmt"] = 4;

  // Add the for loop that iterates over the map here


  s.insert(20);
  s.insert(45);

  // Add the for loop that iterates over the set here
  // READ THE Auto NOTES FIRST

  
  
  return 0;
}
