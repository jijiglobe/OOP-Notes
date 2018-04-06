#include "Protector.h"
using namespace WarriorCraft;
namespace WarriorCraft{
  Class Noble{
  public:
    virtual void battle(Noble& enemy) =0;
  private:
    string name;
    int strength;
  };
  
  Class Lord : public Noble{
  public:
    Lord(string name);
    void hires(Protector& applicant);
    void battle(Noble& enemy);
  private:
    bool isDead;
    vector<Warrior*> army;
  };
  
  Class PersonWithStrengthToFight :  public Noble{
  public:
    PersonWithStrengthToFight(string name,int strength);
    void battle(Noble& enemy);
  private:
  }

}
