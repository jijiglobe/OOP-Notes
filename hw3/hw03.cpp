//Name: Jion Fairchild
//Section: C
//Description: This is a program that takes an input file "warriors.txt" of commands and uses that to simulate a sequence of battles between warriors

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Warrior{
public:
  //constructor for warrior class, also constructs its weapon
  Warrior(const string& name, const string& weaponName, const int& strength):
    name(name), myWeapon(weaponName,strength){
    
  }
  //getter for the strength of this warrior's weapon
  int getStrength(){ return myWeapon.getStrength();}
  //getter for htis warriors name
  string getName(){ return name;}
  //getter for this warrior's weapon's name
  string getWeaponName(){ return myWeapon.getName(); }
  //setter for the strength of this warrior's weapon
  void setStrength(int newStrength){
    myWeapon.setStrength(newStrength);
  }
private:
  //a class to describe the information about this warrior's weapon
  class Weapon{
  public:
    Weapon(const string& name, const int& strength): name(name), strength(strength){
    }
    //getter for this weapon's strength
    int getStrength(){
      return strength;
    }
    //getter for this weapon's name
    string getName(){
      return name;
    }
    //setter for this weapon's strength
    void setStrength(int newStrength){
      strength = newStrength;
    }
  private:
    string name;
    int strength;
  };
  string name;
  //this warriors weapon
  Weapon myWeapon;
};


//given two warrior objects, performs a battle between them
void battleByObj(Warrior& warrior1, Warrior& warrior2){
  //print battle initiation message
  cout << warrior1.getName() << " battles " << warrior2.getName() << endl;
  if(warrior1.getStrength() <= 0 && warrior2.getStrength() <= 0){
    //both combatents are already dead
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
    return;
  }else if(warrior1.getStrength() <= 0){
    //warrior 1 is already dead
    cout << "He's dead, " << warrior2.getName() << endl;
    return;
  }else if(warrior2.getStrength() <=0){
    //warrior2 is already dead;
    cout << "He's dead, " << warrior1.getName() << endl;
    return;
  }

  //this is the actual combat
  int warrior1StrengthHolder = warrior1.getStrength();
  warrior1.setStrength(warrior1.getStrength()-warrior2.getStrength());
  warrior2.setStrength(warrior2.getStrength()-warrior1StrengthHolder);

  //this code finds out who won and sets dead warrior's strength to 0
  if(warrior1.getStrength() <= 0 && warrior2.getStrength() <= 0){
    //mutual annihilation
    warrior1.setStrength(0);
    warrior2.setStrength(0);
    cout << "Mutual Annihilation: " << warrior1.getName() << " and "
	 <<warrior2.getName() << " die at each other's hands" << endl;
  }else if(warrior1.getStrength() <= 0){
    //warrior2 wins
    warrior1.setStrength(0);
    cout << warrior2.getName() << " defeats " << warrior1.getName()<< endl;
  }else if(warrior2.getStrength() <=0){
    //warrior1 wins
    warrior2.setStrength(0);
    cout << warrior1.getName() << " defeats " << warrior2.getName() << endl;
  }else{
    //this should never happen
    cout << "Error2. Battle could not be condluded properly" << endl;
    exit(1);
  }
}

//given the names of two warriors, and a list of all warriors
//performs a battle between the corresponding warriors
void battleByName(vector<Warrior>& warriorList, const string& name1, const string& name2){
  //first find the indicies of each warrior
  int warrior1;
  int warrior2;
  for( size_t i = 0; i < warriorList.size(); i++){
    if(name1 == warriorList[i].getName()){
      warrior1 = i;
    }else if(name2 == warriorList[i].getName()){
      warrior2 = i;
    }
  }
  //now make them battle
  battleByObj(warriorList[warrior1],warriorList[warrior2]);
}

//outputs the status of all warriors to stdout
void printStatus(vector<Warrior> warriorList){
  //print number of warriors
  cout << "There are: " << warriorList.size() << " warriors" << endl;
  
  //for each warrior, print it's status
  for(Warrior currentWarrior: warriorList){
    cout << "Warrior: " << currentWarrior.getName()
	 <<", Weapon: " << currentWarrior.getWeaponName()
	 << ", " << currentWarrior.getStrength() <<endl;
  }
}

int main(){
  //open file
  ifstream ifs("warriors.txt");
  if(!ifs){
    cout << "File could not be opened" << endl;
    exit(1);
  }
  
  string command;//holds the current command
  string param1;//holds the first parameter of that command (if possible)
  string param2;//holds the second parameter of that command (if possible)
  string param3;// holds the third parameter (if possible)
  vector<Warrior> warriorList;//a list of all warriors
  while( ifs >> command){//read in the first command
    if(command == "Status"){
      //status command called
      printStatus(warriorList);
    }else{
      //the other commands have at least 2 parameters so those are read
      ifs >> param1;
      ifs >> param2;
      
      if(command == "Warrior"){
	//initialize a warrior
	//this command has an additional paramater so we'll read it
	ifs >> param3;
	//create a warrior according to these parameters
	Warrior newWarrior(param1,param2,stoi(param3));
	warriorList.push_back(newWarrior);
      }else if(command == "Battle"){
	//engage 2 warriors in battle
	battleByName(warriorList,param1,param2);
      }else{
	//this should never happen
	cout << "Error: Command could not be recognized";
	exit(1);
      }
    }
  }
}
