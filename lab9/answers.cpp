#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
  PrintedMaterial():numOfPages(1){}
  PrintedMaterial(unsigned numPages): numOfPages(numPages){}
  friend ostream& operator<<(ostream& os,const PrintedMaterial& p);
  virtual void displayNumPages() const =0;
protected:
private:
  unsigned numOfPages;
};
void PrintedMaterial::displayNumPages() const{
  cout << numOfPages<<endl;
}

ostream& operator<<(ostream& os, const PrintedMaterial& p){
  os<<p.numOfPages;
  return os;
}
class Magazine : public PrintedMaterial {
public:
  Magazine(unsigned numPages):PrintedMaterial(numPages){}
  void displayNumPages() const{
    PrintedMaterial::displayNumPages();
  }
protected:
private:
};

class Book : public PrintedMaterial {
public:
  Book(unsigned numPages):PrintedMaterial(numPages){}
  void displayNumPages() const{
    PrintedMaterial::displayNumPages();
  }
protected:
private:
};

class TextBook : public Book {
public:
  TextBook(unsigned numPages,unsigned index):Book(numPages),numOfIndexPages(index){}
  void displayNumPages() const {
    cout << "Index: " << numOfIndexPages<<endl;
    cout << "Pages: ";
    PrintedMaterial::displayNumPages();
  }
protected:
private:
  unsigned numOfIndexPages;
};

class Novel : public Book {
public:
  Novel(unsigned numPages):Book(numPages){}
  void displayNumPages() const{
    PrintedMaterial::displayNumPages();
  }
protected:
private:
};

void displayNumberOfPages(const PrintedMaterial& freedom){
  freedom.displayNumPages();
}

// tester/modeler code
int main()
{
  TextBook t(500,20);
  Novel n(200);
  Magazine m(30);

  cout << t<<endl;
  cout << n<<endl;
  cout << m<<endl<<endl;
  
  t.displayNumPages();
  n.displayNumPages();
  m.displayNumPages();
  cout << endl;
  PrintedMaterial* pm = &t;
  pm->displayNumPages();
  cout <<endl<<endl;
  
  displayNumberOfPages(t);
  displayNumberOfPages(n);
  displayNumberOfPages(m);
  cout << endl <<"The Final Frontier!!"<<endl;
  vector<PrintedMaterial*> pvec;
  pvec.push_back(&t);
  pvec.push_back(&n);
  pvec.push_back(&m);
  for( const PrintedMaterial* curr : pvec){
    curr->displayNumPages();
  }

}
