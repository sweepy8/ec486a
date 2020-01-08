#include <iostream>
#include <vector>

using namespace std;

class Midshipman{
    int _alpha;
protected:
    string _name;
public:
    int _graduationYear;
    
    Midshipman() : _alpha(0), _name(), _graduationYear(2020) {
        cout << "Create Midshipman\n";
    }
    
    Midshipman(int alpha, string name, int graduationYear) : 
        _alpha(alpha), _name(name), _graduationYear(graduationYear) {}
        
    ~Midshipman() {
        cout << "Destroy Midshipman\n";
    }
        
    virtual void print(){
        cout << _alpha << "," << _name << "," << _graduationYear << "\n";
    }
    
    static void greeting(){
        cout << "Hello\n";
    }
};

class Plebe : public Midshipman{
    
public:
    vector<string> rates;

    Plebe() : Midshipman(0,"Tom",2023) {}
    
    virtual void print(){
        cout << "Sir " << _name << ", Sir " << _graduationYear << " Sir\n";
    }
};

Midshipman *g_midOfTheDay;

void f(){
    Midshipman *m1 = new Midshipman;
    m1->print();
    
    Midshipman m2;
    m2.print();
    
    Midshipman::greeting();
    
    Midshipman *tom = new Plebe;
    
    auto pl = tom;
    
    g_midOfTheDay = &m2;
    g_midOfTheDay->print();
}

int main(){
    cout << "Main Start\n";
    f();
    cout << "Main End\n";
    
    return 0;
}
