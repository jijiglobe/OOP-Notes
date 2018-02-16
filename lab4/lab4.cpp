#include<vector>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

class Person {  
public:       
  Person( const string& name ) : name(name) {}
  void movesInWith( Person& newRoomate ) {
    if(&newRoomate != this && newRoomate.roomie == nullptr
       && roomie == nullptr){
      roomie = &newRoomate;        // now I have a new roomie            
      newRoomate.roomie = this;    // and now they do too 
    }else{
      cout << "Error, move in could not occur" << endl;
    }
  }       
  string getName() const { return name; }
  void moveOut(){
    roomie->roomie = nullptr;
    roomie = nullptr;
  }
  // Don't need to use getName() below, just there for you to use in debugging.
  string getRoomiesName() const { return roomie->getName(); }  
private:
  Person* roomie;       
  string name;  
};           

class SpeakerSystem {
public:
  void vibrateSpeakerCones( unsigned signal ) const {
    
    cout << "Playing: " << signal << "Hz sound..." << endl;
    cout << "Buzz, buzzy, buzzer, bzap!!!\n";
  }
};



class Amplifier {
public:
  void attachSpeakers( const SpeakerSystem& spkrs )
  {
    if( attachedSpeakers )
      cout << "already have speakers attached!\n";
    else
      attachedSpeakers = &spkrs;
  }
  void detachSpeakers() 
  { attachedSpeakers = nullptr; }
  // should there be an "error" message if not attached?
  void playMusic( ) const {
    if( attachedSpeakers )
      attachedSpeakers -> vibrateSpeakerCones( 440 ); 
    else
      cout << "No speakers attached\n"; 
  }
private:
  //this allows the amp to interact with the speaker but not change it
  const SpeakerSystem* attachedSpeakers = nullptr;
};

class Colour {  
public:       
  Colour( const string& name, unsigned r, unsigned g, unsigned b )       
    : name(name), r(r), g(g), b(b) {}       
  void display() const { 
    cout << name << " (RBG: " << r << "," << g<< "," << b << ")"; 
  }   
private:       
  string   name;    // what we call this colour       
  unsigned r, g, b; // red/green/blue values for displaying  
};         



struct Complex {
  double real;
  double img;
};
/*
class PlainOldClass {
public:
  PlainOldClass() : x(-72) {}
  int getX() const { return x; }
  void setX( int val )  { x = val; }
private:
  int x;
  };*/
class PlainOldClass {  
public:
  PlainOldClass() : x(-72) {}
  int getX() const { return x; }
  void setX( int x )  { this->x = x; } // HMMMM???
private:
  int x;
};

int main(){
 
  int x;  
  x = 10;  
  cout << "x = " << x << endl;

  int* p;  
  p = &x;  
  //p = 0x7fff5fbffc3c;
  cout << "p = " << p << endl;
  
  cout << "p points to where " << *p << " is stored\n";  
  cout << "*p contains " << *p << endl;
  
  *p = -2763;  
  cout << "p points to where " << *p << " is      stored\n";  
  cout << "*p now contains " << *p << endl;  
  cout << "x now contains " << x << endl;

  int* q;      
  q = p;      
  cout << "q points to where " << *q << " is stored\n";      
  cout << "*q contains " << *q << endl;

  //The above does what it says and the debugger indicates the same data
  double d(33.44);      
  double* pD(&d);      
  *pD = *p;
  *pD = 73.2343;      
  *p  = *pD;      
  *q  = *p;
  
  //pointers cannot be cast whatsoever
  //pD  = p;
  //p   = pD;

  int joe( 24 );  
  const int sal( 19 );    
  int*  pI;  
  pI = &joe;  
  *pI = 234;  
  //the below isn't allowed because it could result in changing sal
  //pI = &sal;  
  // *pI = 7623;    
  
  /*
  const int* pcI;
  pcI = &joe;  
  // *pcI = 234;  
  //the below works becuase it promises not to change Sal
  pcI = &sal;  
  //the below breaks that promise
  // *pcI = 7623;    
  */

  //int* const cpI;
  //the value of the pointer itself is const, not the value at that pointer
  // int* const cpI(&joe);
  //int* const cpI(&sal);
  //breaks const-ness
  //cpI = &joe;  
  // *cpI = 234;  
  //  cpI = &sal;  
  // *cpI = 7623;    
  
  //the below is pointless
  //const int* const cpcI;
  
  //these declarations work but none of the modifiers do
  const int* const cpcI(&joe);
  //const int* const cpcI(&sal);
  // cpcI = &joe;
  // *cpcI = 234;  
  //  cpcI = &sal;  
  // *cpcI = 7623;  
  
  
  Complex c = {11.23,45.67};      
  Complex* pC(&c);
  //the below doesn't work because order of operations
  //cout << "real: " << pC.real << "\nimaginary: " << pC.img << endl;
  cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

  PlainOldClass poc;
  PlainOldClass* ppoc( &poc );
  cout << ppoc->getX() << endl;
  ppoc->setX( 2837 );
  cout << ppoc->getX() << endl;

  int* pDyn = new int(3); // p points to an int initialized to 3 on the heap      
  *pDyn = 17;

  //once again this data can be retrieved from the debugger
  cout << "The " << *pDyn
       << " is stored at address " << pDyn
       << " which is in the heap\n";

  cout << pDyn << endl;  
  delete pDyn;  
  cout << pDyn << endl;

  //cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";  
  //cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n"; //this line is for if you like playing with fire
  //in our first test it paid off though

  
  pDyn = nullptr;

  double* pDouble( nullptr );


  //NEVER DO THIS
  //I'M HAVING OS PROGRAMMING PTSD
  /*
  cout << "Can we dereference nullptr?  " << *pDyn << endl;      
  cout << "Can we dereference nullptr?  " << *pDouble << endl;*/

  //good form incoming
  double* pTest = new double( 12 );      
  delete pTest;      
  pTest = nullptr;      
  delete pTest; // safe
  
  //don't touch this. It's not ours
  //this did actually compile though so that's cute
  //it crashed though, don't worry
  /*
  short* pShrt = new short( 5 );      
  delete pShrt;      
  delete pShrt;*/

  long jumper( 12238743 );      
  //delete jumper;
  
  long* ptrTolong( &jumper );      
  //delete ptrTolong;        
  Complex cmplx;      
  //delete cmplx;


  vector<Complex*> complV; // can hold pointers to Complex objects
  Complex* tmpPCmplx;      // space for a Complex pointer
  for ( size_t ndx = 0 ; ndx < 3 ; ++ndx ) {
    tmpPCmplx = new Complex; // create a new Complex object on the heap
    tmpPCmplx->real = ndx;   // set real and img to be the
    tmpPCmplx->img  = ndx;   // value of the current ndx
    complV.push_back( tmpPCmplx ); // store the ADDRESS of the object in a vector or pointer to Complex
  }      
  // display the objects using the pointers stored in the vector
  for ( size_t ndx = 0 ; ndx < 3 ; ++ndx ) {         
    cout << complV[ ndx ]->real << endl;         
    cout << complV[ ndx ]->img  << endl;      
  }      
  // release the heap space pointed at by the pointers in the vector      
  for ( size_t ndx = 0 ; ndx < 3 ; ++ndx ) {         
    delete complV[ ndx ];      
  }      
  // clear the vector      
  complV.clear();    



  vector< Colour* > colours;         
  string inputName;       
  unsigned inputR, inputG, inputB;

  //EOF by entering ctrl - d
  //commented out so I don't have to keep entering inputs
  /*while ( cin >> inputName >> inputR >> inputG >> inputB ) {            
     colours.push_back( new Colour(inputName, inputR, inputG, inputB) );       
   }         

   // display all the Colours in the vector:       
   for ( size_t ndx = 0; ndx < colours.size(); ++ndx ) {            
     colours[ndx]->display();            
     cout << endl;       
     }*/
  Amplifier amp;
  SpeakerSystem speaker;
  amp.attachSpeakers(speaker);
  amp.playMusic();
  
  
  // write code to model two people in this world       
  Person joeBob("Joe Bob"), billyJane("Billy Jane");         
  // now model these two becoming roommates       
  joeBob.movesInWith( billyJane );         
  // did this work out?       
  cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
  cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
  joeBob.movesInWith( billyJane );         
  cout << "move out" << endl;
  joeBob.moveOut();
  cout << "move back in" << endl;
  joeBob.movesInWith( billyJane );
  cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
  cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
  cout << "move back out" << endl;
  joeBob.moveOut();
  cout << "move in with myself" << endl;
  joeBob.movesInWith( joeBob );         


  
}
