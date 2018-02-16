#include <stuff>
using namespace std;

struct Type{
  int value;
};

class Person{
public:
  
  //this function shouldn't be void type; it fails silently
  //users of this class should be able to know if it failed
  //void marries(Person& betrothed){
  bool marries(Person& betrothed){
    if(betrothed.spouse == nullptr &&
       spouse == nullptr){
      spouse = &betrothed;
      betrothed.spouse = this; //private fields are private within a class
      return true;
    }
    return false;
  }
private:
  string name;
  int age;
  Person* spouse;
};

int main(){
  Type* p;
  Type** q = &p;

  //&variableName = the memory address of variableName
  //*pointerName = the data at the address referenced by pointerName
  
  int* numFriends = nullptr;
  //nullptr is the null pointer: 0X0
  
  Person oneFriend;
  //cout << *oneFriend.name; //Doesn't work because order of operations
  cout << (*oneFriend).name;// works but is bad form
  cout << oneFriend->name; //this is the generally correct way to do it

  int* p;
  const in y = 28;
  p = &y;
  *p = 6; //you can't cheat const like this
  //you cannot store the pointer to a const, it will compiletime error

  //instead:
  const int* q = &y;

  int& p;
  p = new int(17);
  delete p; //clears value at p

  vector<int*> ints;
  for(int x = 0;x<10;x++){
    ints.push_back(new int(x));
  }
  ints.clear();//ACK MEMORY LEAK
  
  //you need to
  for(int x = 0;x<ints.size();x++){
    delete ints[x];
  }
  
}