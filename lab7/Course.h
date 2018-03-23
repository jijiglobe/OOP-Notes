#include <iostream>
#include <string>
class Student;
class Course{
 public:
  Course(std::string name);
  bool registerStudent(Student* stud);
  std::string getName();
  friend std::ostream& operator<<(std::ostream& os, const Course& course);
  void deregisterStudents();
};
