#include <vector>
#include <iostream>
using namespace std;

class Instrument{
public:
  virtual void makeSound() const =0;
private:
  
};

void Instrument::makeSound() const{
  cout << "To make a sound... ";
}


class Brass : public Instrument{
public:
  Brass(unsigned size): mouthPieceSize(size){}
  //virtual ~Brass() =0;
  void makeSound() const{
    Instrument::makeSound();
    cout << "blow on a mouthpiece of size " << mouthPieceSize;
  }
private:
  unsigned mouthPieceSize;
};
class Trumpet : public Brass{
public:
  Trumpet(unsigned size): Brass(size){}
 private:
};
class Trombone: public Brass{
public:
  Trombone(unsigned size): Brass(size){}
private:
};

class String : public Instrument{
public:
  String(unsigned pitch): stringPitch(pitch){}
  //virtual ~String() =0;
  void makeSound() const{
    Instrument::makeSound();
    cout << "bow a string with pitch "<< stringPitch;
  }
private:
  unsigned stringPitch;
};
class Violin : public String{
public:
  Violin(unsigned pitch): String(pitch){}
private:
};
class Cello : public String{
public:
  Cello(unsigned pitch): String(pitch){}
private:
};

class Percussion : public Instrument{
public:
  //virtual ~Percussion() =0;
  void makeSound() const{
    Instrument::makeSound();
    cout << "hit me!";
  }
  
private:
};

class Cymbal : public Percussion{
public:
private:
};

class Drum : public Percussion{
public:
private:
};

class Musician {
public:
  Musician() : instr(nullptr) {}
  
  void acceptInstr(Instrument* instPtr) { instr = instPtr; }
  
  Instrument* giveBackInstr() { 
    Instrument* result(instr); 
    instr = nullptr;
    return result;
  }
  
  void testPlay() const {
    if (instr) instr->makeSound(); 
    else cerr << "have no instr\n";
  }
  
private:
  Instrument* instr;
};

class MILL{
public:
  MILL(){}
  
  void receiveInstr(Instrument& newInstr){
    for(int i = 0;i<instrumentRack.size();i++){
      if(instrumentRack[i] == nullptr){
	instrumentRack[i] = &newInstr;
	return;
      }
    }
    instrumentRack.push_back(&newInstr);
  }
  
  void dailyTestPlay() const{
    for(Instrument* current : instrumentRack){
      if(current != nullptr){
	//cout << "playing..."<<endl;
	current->makeSound();
	cout << endl;
      }
    }
  }

  Instrument* loanOut(){
    for(int i = 0;i<instrumentRack.size();i++){
      if(instrumentRack[i] != nullptr){
	Instrument* holder = instrumentRack[i];
	instrumentRack[i] = nullptr;
	return holder;
      }
    }
    return nullptr;
  }
private:
  vector<Instrument*> instrumentRack;
};

// PART ONE
int main() {
  
    cout << "Define some instruments ----------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL ------------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
  
    cout << "Daily test -----------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians-------------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());-----------------------\n";
    groucho.testPlay();	
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
  
    groucho.testPlay();	
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ----------\n";
  
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << endl;

}

