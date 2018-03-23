//Name: Jion Fairchild
//Section: BLab
//Description: a program to model the interactions between a class of students and their lab instructor.

#include <iostream>
#include <vector>
#include <string>
using namespace std;
class LabWorker;
//class Section;
/*class Section{
public:  bool setInstructor(LabWorker);
};*/
//class Student;
//class LabWorker;

class Student{
public:
  Student(const string& name): name(name){
    for( int i=0;i<14;i++){
      grades.push_back(-1);
    }
  }
  
  string getName()const{
    return name;
  }

  bool addGrade(const string& studentName, int grade, int week){
    if(studentName == name){
      grades[week-1] = grade;
      return true;
    }
    return false;
  }
  Student* copy(){
    Student* copy = new Student(name);
    copy->grades = grades;
    return copy;
  }
  friend ostream &operator<<(ostream& os, const Student& stud);
private:
  string name;
  vector<int> grades;
};

class Section{
public:
  Section(const string& name, const string& weekday, int time):
    name(name), weekday(weekday),time(time){    
  }
  ~Section(){
    for( Student* student : students){
      cout << "deleting... " << student->getName() << endl;
      delete student;
    }
  }
  
  Section(const Section& otherSection):time(otherSection.time),name(otherSection.name),weekday(otherSection.weekday){
    for( Student* student : otherSection.students){
      students.push_back(student->copy());
    }
  }
  
  bool setInstructor(LabWorker* newInstructor){
    if(instructor != nullptr){
      return false;
    }
    instructor = newInstructor;
    return true;
  }
  void addGrade(const string& studentName, int grade, int week){
    for(Student* student : students){
      if(student->addGrade(studentName,grade,week)){
	return;
      }
    }
  }
  void addStudent(const string& name){
    Student* newStudent = new Student(name);
    students.push_back(newStudent);
  }
  
  friend ostream &operator<<(ostream& os, const Section& sec);
  
private:
  const LabWorker* instructor;
  const string name;
  const string weekday;
  const int time;
  vector<Student*> students;
};

class LabWorker{
public:
  LabWorker(const string& name): name(name){}

  bool addSection(Section& newSection){
    if( section != nullptr){
      return false;
    }
    if(newSection.setInstructor(this)){
      section = &newSection;
      return true;
    }
    return false;
  }
  
  friend ostream &operator<<(ostream& os, const LabWorker& wrk);
  void addGrade(string studentName, int grade, int week){
    section->addGrade(studentName,grade,week);
  }
  
private:
  Section* section;
  string name;
  
};


ostream &operator<<(ostream& os, const Section& sec){ 
  //Section: A2, Time slot: [Day: Tuesday, Start time: 4pm], Students:
  os << "Section: "<< sec.name << ", Time slot: [Day: "<<
    sec.weekday<<", Start time: ";
  int time12 = sec.time;
  string ampm = "am";
  if(sec.time > 12){
    time12 = sec.time-12;
    ampm = "pm";
  }
  os << time12 << ampm << "], Students:"<<endl;
    //    printf("Section: %s, Time slot: [Day: %s, Start time: %i%s], Students:",
    //name,weekday,time12,ampm);
    for(Student* student : sec.students){
      os<<*student;
    }
  return os;
}

ostream &operator<<(ostream& os, const Student& stud){
  os << "Name: " << stud.name << ", Grades: ";
  for(int grade : stud.grades){
    os << grade<<" ";
  }
  os<<endl;
  return os;
}

ostream &operator<<(ostream& os, const LabWorker& wrk){
  if( wrk.section == nullptr){
    os<< wrk.name <<" does not have a section";
  }
  else{
    os << wrk.name << " has ";
    os << *(wrk.section);
  }
  return os;
}
    

// Test code
void doNothing(Section sec) { cout << sec;}

int main() {

  cout << "Test 1: Defining a section\n";
  Section secA2("A2", "Tuesday", 16);
  cout << secA2;

  cout << "\nTest 2: Adding students to a section\n";
  secA2.addStudent("John");
  secA2.addStudent("George");
  secA2.addStudent("Paul");
  secA2.addStudent("Ringo");
  cout << secA2;

  cout << "\nTest 3: Defining a lab worker.\n";
  LabWorker moe( "Moe" );
  //moe.display();
  cout << moe;

  cout << "\nTest 4: Adding a section to a lab worker.\n";
  moe.addSection( secA2 );
  //moe.display();
  cout << moe;

  cout << "\nTest 5: Adding a second section and lab worker.\n";
  LabWorker jane( "Jane" );
  Section secB3( "B3", "Thursday", 11 );
  secB3.addStudent("Thorin");
  secB3.addStudent("Dwalin");
  secB3.addStudent("Balin");
  secB3.addStudent("Kili");
  secB3.addStudent("Fili");
  secB3.addStudent("Dori");
  secB3.addStudent("Nori");
  secB3.addStudent("Ori");
  secB3.addStudent("Oin");
  secB3.addStudent("Gloin");
  secB3.addStudent("Bifur");
  secB3.addStudent("Bofur");
  secB3.addStudent("Bombur");
  jane.addSection( secB3 );
  cout << jane;

  cout << "\nTest 6: Adding some grades for week one\n";
  moe.addGrade("John", 17, 1);  
  moe.addGrade("Paul", 19, 1);  
  moe.addGrade("George", 16, 1);  
  moe.addGrade("Ringo", 7, 1);  
  cout << moe;

  cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
  moe.addGrade("John", 15, 3);  
  moe.addGrade("Paul", 20, 3);  
  moe.addGrade("Ringo", 0, 3);  
  moe.addGrade("George", 16, 3);  
  cout << moe;

  cout << "\nTest 8: We're done (almost)! \nWhat should happen to all those students (or rather their records?)\n";

  cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, then make sure the following call works\n";
  doNothing(secA2);
  cout << "Back from doNothing\n\n";

} // main
