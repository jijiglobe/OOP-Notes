#include <fstream>
#include <string>
#include <vector>

vector<int> v;
for(size_t i = v.size; i > 0;--i){ //you cant go until i is negative because size_t is unsigned
  cout << v[i-1];//remember to shift one since your loop starts at v.size, not v.size-1
 }

struct Person{ // define types(classes or structs) capitalize the first letter
  string name;
  int age;
};

void structExamples(){
  Person someone;
  int x;
  string s;
  
  someone.name = "Fred";
  someone.age = 17;
  
  Person someoneElse;
  //if (someone == someoneElse){you cannot do this}
  someoneElse = someone; // this is a copy operation (kinda like a deepcopy)
  

  ifstream ifs("people.txt");
  //file formatted as "name age\n"

  string name;
  int age;
  while (ifs >> name >> age){//reads out string then int
    Person p1;
    p1.name = name;
    p1.age = age;
    //pushback to vector
  }

  for(const Person& p: vector){
    //passing by reference saves runtime by preventing unnecessary copy operations
  }
}

void prototype(int input); // prototype defined here so it can be used

int main(){
  prototype();// we can reference prototype without writing it yet
}

void prototype(int input){
  cout << input;// now we write prototype so the compiler can have something to put in
}
