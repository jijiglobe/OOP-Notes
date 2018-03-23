//Name: Jion Fairchild
//Section: C
//Description: A simulation of medieval battles involving warriors and nobles
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior{
public:
  Warrior(const string& name, int strength): name(name), strength(strength), isFree(true){
  }
  //set this warrior to part of an army;
  bool hire(){
    if(isFree){
      isFree = false;
      return true;
    }
    return false;
  }
  int getStrength() const{
    return strength;
  }
  //free this warrior
  void setFree(){
    isFree = true;
  }
  //weaken this warrior by an amount calculated based off the ratio
  //between the strength of the two combatting armies
  void weaken(int ratio){
    strength *= (1-ratio);
  }
  void die(){
    strength = 0;
  }
  void display(){
    cout << "        "<<name<<": "<<strength<<endl;
  }
  string getName()const{
    return name;
  }
private:
  const string name;
  int strength;
  //false if this unit is in an army
  //true otherwise
  bool isFree;
};

class Noble{
public:
  Noble(const string& name): name(name){
  }
  //hires a recruit passed in by reference.
  bool hire(Warrior& newRecruit){
    if(newRecruit.hire()){
      army.push_back(&newRecruit);
      return true;
    }
    //cout <<"NOOOOOOOOOOO"<<endl;
    return false;
  }
  
  //removes a recruit from this noble's army
  bool fire(Warrior& recruit){
    cout << recruit.getName() <<" you're fired! -- "<<name<<endl;
    bool found = false;
    int i;
    for( i = 0; i < army.size() && !found;i++){
      if(army[i] == &recruit){
	found = true;
	break;
      }
    }
    if(!found){
      //cout << "NOPE";
      return false;
    }//shift over all warriors in the army
    for(;i<army.size()-1;i++){
      army[i] = army[i+1];
    }
    army[i]->setFree();
    army.pop_back();//delete the last warrior pointer(it's a copy)
  }
  
  int getStrength() const{
    int ans = 0;
    for(Warrior* warrior : army){
      //cout<<warrior->getStrength()<<endl;
      ans += warrior->getStrength();
    }
    return ans;
  }
  
  //battle an enemy noble
  void battle(Noble& enemy){
    cout << name << " battles " << enemy.name << endl;
    if(isDead && enemy.isDead){
      //both nobles are dead
      cout << "Oh, NO!  They're both dead!  Yuck!"<<endl;
      return;
    }else if(isDead){
      //this noble is dead
      cout << "He's dead, " << enemy.name << endl;
      return;
    }
    else if(enemy.isDead){
      //enemy is already dead
      cout << "He's dead, " << name << endl;
      return;
    }
    
    int myStrength = getStrength();
    int theirStrength = enemy.getStrength();
    
    if(myStrength <  theirStrength){
      //this noble loses the battle
      cout << enemy.name << " defeats " << name<< endl;
      double ratio = double(myStrength) / theirStrength;
      die();
      enemy.weaken(ratio);
    }else if(theirStrength < myStrength){
      //enemy noble loses the battle
      cout << name << " defeats " << enemy.name << endl;
      double ratio = double(theirStrength) / myStrength;
      enemy.die();
      weaken(ratio);
    }else if(theirStrength == myStrength){
      //mutual annihilation

      cout << "Mutual Annihilation: " << name  << " and "
	   <<enemy.name << " die at each other's hands" << endl;
      die();
      enemy.die();
    }
  }
  void display(){
    cout << name<< " has an army of "<<army.size()<<endl;
    for(Warrior* warrior : army){
      warrior->display();
    }
  }
    
private:
  //cause this unit and its army to be dead
  void die(){
    isDead = true;
    for(Warrior* warrior : army){
      warrior->die();
    }
  }
  //weaken this nobles army by an amount calculated based off
  //the ratio beteen army strengths
  void weaken(double ratio){
    for(Warrior* warrior : army){
      warrior->weaken(ratio);
    }
  }
  const string name;
  vector<Warrior*> army;
  bool isDead;
};

int main() {
  Noble art("King Arthur");
  Noble lance("Lancelot du Lac");
  Noble jim("Jim");
  Noble linus("Linus Torvalds");
  Noble billie("Bill Gates");
  
  Warrior cheetah("Tarzan", 10);
  Warrior wizard("Merlin", 15);
  Warrior theGovernator("Conan", 12);
  Warrior nimoy("Spock", 15);
  Warrior lawless("Xena", 20);
  Warrior mrGreen("Hulk", 8);
  Warrior dylan("Hercules", 3);
  
  jim.hire(nimoy);
  lance.hire(theGovernator);
  art.hire(wizard);
  lance.hire(dylan);
  linus.hire(lawless);
  billie.hire(mrGreen);
  art.hire(cheetah);
  
  jim.display();
  lance.display();
  art.display();
  linus.display();
  billie.display();
  
  art.fire(cheetah);
  art.display();
  
  art.battle(lance);
  jim.battle(lance);
  linus.battle(billie);
  billie.battle(lance);
}
