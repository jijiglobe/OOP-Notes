//Name: Jion Fairchild
//Section: C
//Description: This is a program that takes an input file "warriors.txt" of commands and uses that to simulate a sequence of battles between warriors

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Warrior{
  string name;
  int strength;
};

//creates and returns warrior with name = name and strength = strength
Warrior createWarrior(const string& name, int strength){
  Warrior thisWarrior;
  thisWarrior.name = name;
  thisWarrior.strength = strength;
  return thisWarrior;
}

//given two warrior structs, performs a battle between them
void battleByStruct(Warrior& warrior1, Warrior& warrior2){
  //print battle initiation message
  cout << warrior1.name << " battles " << warrior2.name << endl;
  if(warrior1.strength <= 0 && warrior2.strength <= 0){
    //both combatents are already dead
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
    return;
  }else if(warrior1.strength <= 0){
    //warrior 1 is already dead
    cout << "He's dead, " << warrior2.name << endl;
    return;
  }else if(warrior2.strength <=0){
    //warrior2 is already dead;
    cout << "He's dead, " << warrior1.name << endl;
    return;
  }

  //this is the actual combat
  int warrior1StrengthHolder = warrior1.strength;
  warrior1.strength -= warrior2.strength;
  warrior2.strength -= warrior1StrengthHolder;

  //this code finds out who won and sets dead warrior's strength to 0
  if(warrior1.strength <= 0 && warrior2.strength <= 0){
    //mutual annihilation
    warrior1.strength = 0;
    warrior2.strength = 0;
    cout << "Mutual Annihilation: " << warrior1.name << " and "
	 <<warrior2.name << " die at each other's hands" << endl;
  }else if(warrior1.strength <= 0){
    //warrior2 wins
    warrior1.strength = 0;
    cout << warrior2.name << " defeats " << warrior1.name<< endl;
  }else if(warrior2.strength <=0){
    //warrior1 wins
    warrior2.strength = 0;
    cout << warrior1.name << " defeats " << warrior2.name << endl;
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
    if(name1 == warriorList[i].name){
      warrior1 = i;
    }else if(name2 == warriorList[i].name){
      warrior2 = i;
    }
  }
  //now make them battle
  battleByStruct(warriorList[warrior1],warriorList[warrior2]);
}

//outputs the status of all warriors to stdout
void printStatus(vector<Warrior> warriorList){
  //print number of warriors
  cout << "There are: " << warriorList.size() << " warriors" << endl;
  
  //for each warrior, print it's status
  for(Warrior currentWarrior: warriorList){
    cout << "Warrior: " << currentWarrior.name
	 <<", strength: " << currentWarrior.strength << endl;
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
  vector<Warrior> warriorList;//a list of all warriors
  while( ifs >> command){//read in the first command
    if(command == "Status"){
      //status command called
      printStatus(warriorList);
    }else{
      //the other commands have 2 parameters so those are read
      ifs >> param1;
      ifs >> param2;
      
      if(command == "Warrior"){
	//initialize a warrior
	Warrior newWarrior = createWarrior(param1,stoi(param2));
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
