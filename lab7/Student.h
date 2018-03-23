//#include "course.h"
#include <iostream>
#include <string>
#include <vector>
class Course;
class Student{
 public:
  Student(std::string name);
  bool registerCourse(Course* course);
  std::string getName();
  void deregister(std::string courseName);
  friend std::ostream& operator<<(std::ostream& os, const Student& stud);
};
