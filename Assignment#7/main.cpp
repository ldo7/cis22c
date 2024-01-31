/*
 CIS22B
 03/20/23
 Create & implement Base and derived classes as characters in a battle game
 */
#include <iostream>
#include <time.h>
using namespace std;

/*
 ============================================
               Creature Class
 ============================================
 */
class Creature {
private:
    int strength;
    int hitpoints;
public:
    Creature();                                 //default constr.
    Creature(int newStrength, int newHit);   //overloaded constr.
    virtual string getSpecies();
    virtual int getDamage();
    int getStrength() const;    //getters & setters
    int getHit() const;
    void setStrength(int);
    void setHit(int);
};
/*
 default constructor
 */
Creature::Creature(){
    strength = 10;
    hitpoints = 10;
}
/*
 overloaded constructor
 */
Creature::Creature(int newStrength, int newHi){
    strength = newStrength;
    hitpoints = newHi;
}
/*
 Parameters: none
 Returns: how much damage creature can inflict in 1 round of combat
 Summary: calculates damage randomly based on creature type
 */
int Creature::getDamage(){
    int damage = (rand() % strength) + 1;
    cout << getSpecies() << " attacks for "
         << damage << " points!" << endl;
    return damage;
}
/*
 getters & setters
 */
string Creature::getSpecies(){
    return "Unknown";
}
int Creature::getStrength() const{
    return strength;
}
int Creature::getHit() const{
    return hitpoints;
}
void Creature::setStrength(int x){
    strength = x;
}
void Creature::setHit(int x){
    hitpoints = x;
}
/*
 ============================================
                  Elf Class
 ============================================
 */
class Elf : public Creature {
public:
    Elf():Creature(){}
    Elf(int s,int h):Creature(s,h){}
    string getSpecies()
    {
        return "Elf";
    }
    int getDamage()
    {
        int damage = Creature::getDamage();
        // Elves inflict double magical damage with a 10% chance
        if ((rand() % 10) == 0){
            cout << "Magical attack inflicts " << damage
                 << " additional damage points!" << endl;
            damage = damage * 2;
        }
        return damage;
    }
};
/*
 ============================================
                Human Class
 ============================================
 */
class Human : public Creature{
public:
    Human():Creature(){};
    Human(int s,int h):Creature(s,h){};
    string getSpecies()
    {
        return "Human";
    }
    int getDamage()
    {
        return Creature::getDamage();
    }
};
/*
 ============================================
                 Demon Class
 ============================================
 */
class Demon : public Creature {
public:
    Demon():Creature(){};
    Demon(int s,int h):Creature(s,h){};
    string getSpecies()
    {
        return "Demon";
    }
    int getDamage()
    {
        int damage = Creature::getDamage();
        // Demons can inflict damage of 50 with a 5% chance
        if ((rand() % 100) < 5){
            damage = damage + 50;
            cout << "Demonic attack inflicts 50 "
                 << " additional damage points!" << endl;
        }
        return damage;
    }
};
/*
 ============================================
            Cyberdemon Class
 ============================================
 */
class Cyberdemon : public Demon{
public:
    Cyberdemon():Demon(){};
    Cyberdemon(int s,int h):Demon(s,h){};
    string getSpecies()
    {
        return "CyberDemon";
    }
    int getDamage()
    {
        return Demon::getDamage();
    }
};
/*
 ============================================
                Balrog Class
 ============================================
 */
class Balrog : public Demon{
public:
    Balrog():Demon(){};
    Balrog(int s,int h):Demon(s,h){};
    string getSpecies()
    {
        return "Balrog";
    }
    int getDamage()
    {
        int damage = Demon::getDamage();
        int damage2 = (rand() % this->getStrength()) + 1; //Demon::getStrength()
        // Balrogs are so fast they get to attack twice
        cout << "Balrog speed attack inflicts " << damage2
             << " additional damage points!" << endl;
        damage = damage + damage2;
        return damage;
    }
};
/*
 ====================================================
                     Battle Arena
 Parameters: two Creature objects
 Returns: none
 Summary: Calculate the damage done by each creature
          choose winner based on hit points remaining
 ====================================================
 */
void battleArena(Creature& c1, Creature& c2){
    while(c1.getHit()>0 && c2.getHit()>0)
    {
        //attack#1
        c2.setHit(c2.getHit() - c1.getDamage());
        cout << "Creature 2 has "<< c2.getHit()
             << " hit points." << endl;
        if(c1.getHit() > 0 && c2.getHit() < 0){
            cout << "\nCreature 1 wins!" << endl;
            break;
        }
        //attack#2
        c1.setHit(c1.getHit() - c2.getDamage());
        cout << "Creature 1 has "<< c1.getHit()
             << " hit points." << endl;
        if(c2.getHit() > 0 && c1.getHit() <= 0){
            cout << "\nCreature 2 wins!\n" << endl;
            break;
        }
        //tie
        if(c2.getHit() < 0 && c1.getHit() <= 0)
            cout << "\nTie between Creature 1 & 2!" << endl;
    }
}
/*
 ============================================
                    Main
 ============================================
 */
int main() {
    srand(static_cast<int>(time(NULL)));
    Human human1(30, 10);
    human1.getDamage();
    cout << endl;
    Elf elf1;
    elf1.getDamage();
    cout << endl;
    Balrog balrog1(50, 50);;
    balrog1.getDamage();
    cout << endl;
    Cyberdemon cdemon(30, 40);
    cdemon.getDamage();
    cout << endl;
    Elf elf2(50, 50);
    Balrog balrog2(50, 50);
    cout << endl;
    battleArena(elf2, balrog2);
    
    return 0;
}
/* SAMPLE RUN
 Human attacks for 21 points!

 Elf attacks for 2 points!

 Balrog attacks for 43 points!
 Balrog speed attack inflicts 50 additional damage points!

 CyberDemon attacks for 16 points!


 Elf attacks for 2 points!
 Creature 2 has 48 hit points.
 Balrog attacks for 36 points!
 Balrog speed attack inflicts 7 additional damage points!
 Creature 1 has 7 hit points.
 Elf attacks for 5 points!
 Creature 2 has 43 hit points.
 Balrog attacks for 9 points!
 Balrog speed attack inflicts 1 additional damage points!
 Creature 1 has -3 hit points.

 Creature 2 wins!

 Program ended with exit code: 0
 */
