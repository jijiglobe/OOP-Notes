#include <iostream>
using namespace std;

class PrintedMaterial {
public:
  PrintedMaterial(unsigned numPages):numOfPages(numPages){}
protected:
private:
  unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
protected:
private:
};

class Book : public PrintedMaterial {
public:
protected:
private:
};

class TextBook : public Book {
public:
protected:
private:
};

class Novel : public Book {
public:
protected:
private:
};

// tester/modeler code
int main()
{
  TextBook t(500);
  Novel n(200);
  Magazine m(30);
}
