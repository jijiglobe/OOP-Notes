#include "student.h"
#include "course.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Registrar{
public:
  friend ostream& operator<<(ostream& os, const Registrar& reg);
  void addStudent(string name);
  void addCourse(string name);
  void enrollStudentInCourse(const string& studName, const string& courseName);
  void cancelCourse(const string& courseName);
  void purge();
private:
  vector<Student*> students;
  vector<Course*> courses;
};


void Registrar::addStudent(string name){
  Student* stud = new Student(name);
  students.push_back(stud);
  //cout << *stud<<endl;
}
void Registrar::addCourse(string name){
  os<< "students: " <<students.size()<<endl;
  os<< "courses: " << courses.size()<<endl;

  Course* course = new Course(name);
  courses.push_back(course);
  //cout << *course<<endl;
  os<< "students: " <<students.size()<<endl;
  os<< "courses: " << courses.size()<<endl;
}
void Registrar::enrollStudentInCourse(const string& studName, const string& courseName){
  Student* stud = nullptr;
  
  for(Student* currStud : students){
    if(currStud->getName() == studName){
      stud = currStud;
      break;
    }
  }
  Course* course = nullptr;
  for(Course* currCourse : courses){
    if(currCourse->getName() == courseName){
      course = currCourse;
      break;
    }
  }
  if(stud == nullptr){
    cout << "Error: Student "<<studName<<" not found!" <<endl;
    return;
  }
  if(course == nullptr){
    cout << "Error: Course "<<courseName<<" not found!" <<endl;
    return;
  }
  stud->registerCourse(course);
  course->registerStudent(stud);
}

void Registrar::cancelCourse(const string& courseName){
  Course* course = nullptr;
  int counter = 0;
  for(Course* currCourse : courses){
    if(currCourse->getName() == courseName){
      course = currCourse;
      break;
    }
    counter++;
  }
  if(course == nullptr){
    cout << "Error: Course "<<courseName<<" not found!" <<endl;
    return;
  }
  course->deregisterStudents();
  delete courses[counter];
  courses.erase(courses.begin()+counter);
}
void Registrar::purge(){
  for( Student* stud: students){
    delete stud;
  }
  for( Course* course: courses){
    delete course;
  }
  students.clear();
  courses.clear();
}

ostream& operator<<(ostream& os, const Registrar& reg){
  os << "Students: "<<endl;
  os<< "students: " << reg.students.size()<<endl;
  os<< "courses: " << reg.courses.size()<<endl;
  //os<< "THIS"<<endl;
  //os<< &reg.students<<endl;
  if(reg.students.size() != 0){
    os<<"trying to shenanigan"<<endl;
    os << &reg.students[0]<<endl;
    os<< "shenanigans managed"<<endl;
  }
  /*for(const Student* stud : reg.students){
    cout<< " THIS" <<endl;
    os <<"   -"<< *stud <<endl;
    //cout <<  "THAT" << endl;
  }
  os << endl << "Courses:" << endl;
  for( const Course* course : reg.courses){
    os << *course <<endl;
    }*/
  os<< "students: " << reg.students.size()<<endl;
  os<< "courses: " << reg.courses.size()<<endl;

  return os;
}
