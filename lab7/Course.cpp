#include "student.h"
#include <string>
#include <iostream>
using namespace std;
class Course{
public:
  Course(string name);
  bool registerStudent(Student* stud);
  string getName();
  void deregisterStudents();
  friend ostream& operator<<(ostream& os, const Course& course);
private:
  vector<Student*> registeredStudents;
  string name;
};
Course::Course(string name): name(name){}
bool Course::registerStudent(Student* stud){
  registeredStudents.push_back(stud);
}
string Course::getName(){ return name; }

void Course::deregisterStudents(){
  for(Student* stud : registeredStudents){
    stud->deregister(name);
  }
}
ostream& operator<<(ostream& os, const Course& course){
  os << "Course: " << course.name << endl;
  for(const Student* stud : course.registeredStudents){
    os <<"      -"<< *stud <<endl;
  }
  return os;
}
