/*
  Recitation 06
  CS2124
 
  Focus: Dynamic arrays and copy control.
*/

#include <string>
#include <iostream>
using namespace std;

class Position {
public:
  Position(const string& aTitle, double aSalary)
    : title(aTitle), salary(aSalary) {}
  const string& getTitle() const { return title; }
  double getSalary() const { return salary; }
  void changeSalaryTo(double d) { salary = d; }
  void display(ostream& os = cout) const {
    os << '[' << title << ',' << salary << ']';
  }
  friend ostream &operator<<(ostream& os, const Position& pos);
private:
  string title;
  double salary;
}; // class Position
ostream &operator<<(ostream& os, const Position& pos){
  os << '[' << pos.title << ',' << pos.salary << ']';
  return os;
}  

class Entry {
public:
  Entry(const string& aName, unsigned aRoom, unsigned aPhone,
	Position& aPosition) 
    : name(aName), room(aRoom), phone(aPhone), pos(&aPosition) {
  }
  Entry(const Entry& other): name(other.name), room(other.room),
		      phone(other.phone),pos(other.pos){
  }
  friend ostream &operator<<(ostream& os, const Entry& entry);
  void display(ostream& os = cout) const {
    os << name << ' ' << room << ' ' << phone << ", ";
    pos->display(os);
  }
  const string& getName() const { return name; }
  const unsigned& getPhone() const { return phone; }
private:
  string name;
  unsigned room;
  unsigned phone;
  Position* pos;
}; // class Entry
ostream &operator<<(ostream& os, const Entry& entry){
  os << entry.name << ' ' << entry.room << ' ' << entry.phone << ", ";
  os<<*(entry.pos);
  return os;
}
class Directory {
public:
  
  Directory(): size(0), capacity(10){
    entries = new Entry*[capacity];
  }
  
  ~Directory(){
    cout << "destructing...\n";
    for(int i = 0;i<size;i++){//clear entries
      delete entries[i];
    }
    delete[] entries;//clear array
  }
  
  Directory(const Directory& other): size(other.size),capacity(other.capacity){
    cout << "copying...\n";
    entries = new Entry*[capacity];
    for(int i = 0; i < size;i++){//copy all entries
      entries[i] = new Entry(*(other.entries[i]));
    }
  }
  
  Directory& operator=(const Directory& other){
    cout << "assigning...\n";
    if(this == &other){
      return *this;
    }
    //free space
    for(int i = 0;i<size;i++){
      delete entries[i];
    }
    delete[] entries;

    //copy fields
    size = other.size;
    capacity = other.capacity;

    //copy capacity
    entries = new Entry*[capacity];
    for(int i = 0; i < size;i++){
      entries[i] = new Entry(*(other.entries[i]));
    }
    return *this;
  }
  
  int operator[](string name){
    for( int i = 0; i<size;i++){
      if(entries[i]->getName() == name){
	return entries[i]->getPhone();
      }
    }
    return 0000;
  }
  
  void add(const string& name, unsigned room, unsigned ph, Position& pos) {
    if (size == capacity){
      // something is missing!!!  Add it!
      Entry** newEntries = new Entry*[capacity * 2];
      for(int i = 0; i < capacity;i++){
	newEntries[i] = entries[i];
	//delete entries[i];
      }
      delete[] entries;
      entries = newEntries;
      
    } // if
    entries[size] = new Entry(name, room, ph, pos);
    ++size;
  } // add
  friend ostream &operator<<(ostream& os, const Directory& dir);
  void display(ostream& os = cout) const {
    for (size_t i = 0; i < size; ++i) {
      entries[i]->display(os);
      os << endl;
    }
  }

private:
  Entry** entries = nullptr;
  size_t size = 0;
  size_t capacity = 0;
}; // class Directory

ostream &operator<<(ostream& os, const Directory& dir){
    for (size_t i = 0; i < dir.size; ++i) {
      os << *dir.entries[i];
      os << endl;
    }
    return os;
}

void doNothing(Directory dir) { cout << dir; }

int main() {
  
  // Note that the Postion objects are NOT on the heap.
  Position boss("Boss", 3141.59);
  Position pointyHair("Pointy Hair", 271.83);
  Position techie("Techie", 14142.13);
  Position peon("Peonissimo", 34.79);
  
  // Create a Directory
  Directory d;
  d.add("Marilyn", 123, 4567, boss);
  //d.display();
  cout << d;

  Directory d2 = d;// What function is being used??
  d2.add("Gallagher", 111, 2222, techie);
  d2.add("Carmack", 314, 1592, techie);
  //d2.display();
  cout << d2;

  cout << "Calling doNothing\n";
  doNothing(d2);
  cout << "Back from doNothing\n";

  Directory d3;
  d3 = d2;

  // Should display 1592
  cout << d2["Carmack"] << endl;
  
} // main
