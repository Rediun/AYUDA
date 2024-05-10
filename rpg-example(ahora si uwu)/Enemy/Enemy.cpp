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

Enemy::Enemy(char name[40], int health, int attack, int defense, int speed, int level) : Character(name, health, attack, defense, speed, false, level) {
    maxHealth = health;
    level = 1;
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
        if (this->fleed != true) {
            if (wow = false) {
                cout << GREEN << "\t---->" << getName() << " has taken " << damage << " damage" << "<----" << RESET << endl;
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
    if ((this->getMaxHealth() * 0.50 >= this->getHealth()) && rand() % 100 < 10) {
        myAction.action = [this, target]() {
            this->fleed = true;
        };
    }
    else {
        myAction.action = [this, target]() {
            doAttack(target);
        };
    }

    return myAction;
}

void Enemy::levelup() {
    int hppls = this -> getHealth() * .50;
    int atkpls = this-> getAttack() * .50;
    int defpls = this-> getDefense() * .50;
    int spdpls = this-> getSpeed() * .50;
        this-> setLevel(getLevel() + 1);
        this -> setHealth(getHealth() + hppls);
        this-> setAttack(getAttack() + atkpls);
        this-> setDefense(getDefense() + defpls);
        this-> setSpeed(getSpeed() + spdpls);


        cout << RED << "\t>>>>>>>>> The enemy [" << MAGENTA << getName() << RESET << RED << "] just level up bro!!!!level current to destroy you : " << getLevel() << " <<<<<<<<<<<<" << RESET << endl;
        cout << "\n\n";
    }

