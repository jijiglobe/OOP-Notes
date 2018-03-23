#include <iostream>
#include <string>
#include <vector>
//using namespace std;

class Registrar{
 public:
  friend std::ostream& operator<<(std::ostream& os, const Registrar& reg);
  Registrar(){}
  void addStudent(std::string name);
  void addCourse(std::string name);
  void enrollStudentInCourse(const std::string& studName, const std::string& courseName);
  void cancelCourse(const std::string& courseName);
  void purge();
};
