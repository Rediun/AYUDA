//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"
#include <iostream>

#define RESET   "\033[0m"      
#define RED     "\033[31m"      
#define GREEN   "\033[32m"     
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"     

using namespace std;

//TODO: Check the circular dependency
int maxHealth = 0;

int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, false) {
    maxHealth = health;
}

int Enemy::getMaxHealth (){
    return maxHealth;
}

void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    bool wow = false;
    if (getAttack() > 15) {
        wow = true;
    }
    setHealth(getHealth() - damage);

    if(getHealth() <= 0) {
        if (wow = false) {
            cout << RED << "\t------X" << getName() << " has died" << " X------" << RESET << endl;
            cout << "\n\n";
            cin.get();
        }
        if (wow = true) {
            cout << RED << "\t------X " << getName() << " has died"<<" X------" << " [You destroid him!!!!]" << RESET << endl;
            cout << "\n\n";
            cin.get();
        }
    }
    else {
        if (wow = false) {
            cout << GREEN <<"\t---->" << getName() << " has taken " << damage << " damage" <<"<----" << RESET << endl;
            cout << "\n\n";
            cin.get();
        }
        if (wow = true) {
            cout << GREEN << "\t----> " << getName() << " has taken " << damage << " damage" << " <----" << " [Nice Hit bro]" << RESET << endl;
            cout << "\n\n";
            cin.get();
        }
    }
}

Character* Enemy::getTarget(vector<Player *> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for (int i = 0; i < teamMembers.size(); i++) {
        ;
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

Action Enemy::takeAction(vector<Player*> player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = getTarget(player);
    myAction.target = target;
    myAction.action = [this, target]() {
        doAttack(target);
    };
    return myAction;
}
bool Enemy::flee() {
    cout << YELLOW << "\t:D     " << this->getName() << " go for milk ((s)he never comeback)     D:" << RESET << endl;
    cout << "\n";
    cin.get();
    return true;
}

Action Enemy::Chicken(vector<Player*> teamMembers) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = nullptr;
    myAction.target = nullptr;
    myAction.action = [this, target] {
        if ((this->getMaxHealth() * 0.40 >= this->getHealth()) && rand() % 100 < 90) {
             this->flee();
        }
        
    };
    return myAction;
}