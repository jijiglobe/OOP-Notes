#include "Noble.h"
using namespace WarriorCraft;
namespace WarriorCraft{
  class Protector{
  public:
    virtual void printBattleDialogue()const =0;
    bool getHiredBy(Lord& newEmployer);
    int getStrength();
    string getName();
  private:
    string name;
    int strength;
    Lord* Employer;
  };

  Class Wizard : public Protector{
  public:
    Wizard(string name, int strength);
    void printBattleDialogue const;
  private:
    
  };
  Class Warrior : public Protector{
  public:
    virtual void printBattleDialogue()const = 0;
  private:
    
  };
  Class Swordsman : public Warrior{
  public:
    Swordsman(string name, int strength);
    void printBattleDialogue() const;
  private:
    
  };
  Class Archer : public Warrior{
  public:
    Archer(string name, int strength);
    void printBattleDialogue() const;
  private:
    
  };
}
