#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <string>
#include <vector>
using namespace WarriorCraft;
using namespace std;

Lord::Lord(string name): name(name), isDead(false){}
Lord::hires(Protector& applicant){
  applicant.getHiredBy(self);
  army.push_back(&applicant);
}
Lord::battle(Noble& enemy){
  //do stuff
}

PersonWithStrengthToFight::PersonWithStrengthToFight(string name, int strength):
  name(name),strength(strength){}

PersonWithStrengthToFight::battle(Noble& enemy){
  //do stuff
}

