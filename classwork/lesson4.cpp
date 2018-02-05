#inclide <iostream>
#include <string>
using namespace std;

cla¨ss Person {
public:
  Person(const string& name, int age : name(theName), age(age){
      //name = theName;
      //^this causes the variable to be initialized twice
    }
    void display() const {//the const allows you to use this in const contexts

      //do something
    }
private:
    string name;
    int age;
    //SIDE NOTE; INTS ARE ALLOCATED RANDOMLY LIKE IN C
    double pi = 3.14195; //only works in new versions of c++
};
