#include "course.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Student{
public:
  Student(string name);
  bool registerCourse(Course* course);
  string getName();
  void deregister(string courseName);
  friend ostream& operator<<(ostream& os, const Student& course);
private:
  string name;
  vector<Course*> registeredCourses;
};
Student::Student(string name): name(name){}
bool Student::registerCourse( Course* course){
  registeredCourses.push_back(course);
  return true;
}
string Student::getName(){ return name; }
void Student::deregister(string courseName){
  for(int i = 0; i < registeredCourses.size();i++){
    if(registeredCourses[i]->getName() == courseName){
      registeredCourses.erase(registeredCourses.begin()+i);
      return;
    }
  }
}

ostream& operator<<(ostream& os, const Student& stud){
  os << stud.name;
  return os;
}
