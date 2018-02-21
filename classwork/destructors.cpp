#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Thing {
public:
  Thing(){
    //create a new Integer and allocate memory for it
    p = new int(0)
  }

  Thing(Thing otherThing){
    p = new int(*(otherThing.p));
    
  }
  
  ~Thing(){
    //When a thing object is deleted, p is not freed
    //^this tilda notation is a destructor, is called when the
    //scope of object is left (IE if it's made in a function)
    //or if the object is deleted.
    delete p;
  }
private:
  int* p;
};
