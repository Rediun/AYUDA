//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include <algorithm>
#include "../Utils.h"

#define RESET   "\033[0m"      
#define RED     "\033[31m"      
#define GREEN   "\033[32m"     
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
     
      

using namespace std;
using namespace combat_utils;

bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

Player::Player(char name[40], int health, int attack, int defense, int speed, int level) : Character(name, health, attack, defense, speed, true, level) {
    experience = 0;
    level = 1;
    depression = 0;
}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
    if (target -> getHealth() <= 0) {
        gainExperience(67);
    }
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    if (health <= 0) {
        cout << RED<< "\t------X You have died, You are a really Crap X------" << RESET<< endl;
        cout << "\n";
        cin.get();
        exit(-1);
    }
    else {
        cout << CYAN << "\t-----> You have taken "  << damage << " damage <-----" << RESET << endl;
        cout << "\n";
        Depression(2);
        cin.get();
    }
}
         

   


void Player::flee(vector<Enemy*> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy* fastestEnemy = enemies[0];
    bool fleed = false;
    if(this->getSpeed() > fastestEnemy->getSpeed()) {
        fleed =  true;
    }
    else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout<< "chance to be a Chicken: " << chance << endl;
        cout << "\n";
        if (fleed = chance > 90) {
            fleed = true;
        }
        else {
            cout << RED << "\t>>>> You can't be a Chicken <<<<" << RESET << endl;
            cout << "\n\n";
        }
    }

    this->fleed = fleed;
}

void Player::emote() {
    cout<<"Jokes on you" << endl;
}

void Player::levelUp() {
    setLevel(getLevel() + 1);
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 5);
    setSpeed(getSpeed() + 5);



    cout << YELLOW << "\t>>>>>>>>> Level up bro!!!! Your level current: " << getLevel() << " <<<<<<<<<<<<" << RESET << endl;
    cout << "\n\n";


}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        int trash = experience - 100;
        levelUp();
        experience = trash;
    }
}

Character* Player::getTarget(vector<Enemy*> enemies) {
    int targetIndex = 0;
    while (true) {
        cout << "Choose your Victim <<<<" << endl;
        for (int i = 0; i < enemies.size(); i++) {
            cout << i  << ". " << enemies[i]->getName() << endl;
        } 
        cout << "> ";
        cin >> targetIndex;
        cout << "\n";
        if (targetIndex  >= enemies.size() || targetIndex < 0) {
            cout << BLUE << "\t!!!!!!!!! Invalid Option, Noob !!!!!!!!!" << RESET << endl;
            cout << "\n";
        }
        else break;
    }   
    return enemies[targetIndex];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int option = 0;
    bool oks = false;
    Character* target = nullptr;
    bool fleed = false;
    Action myAction;
    
    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    while (oks == false){
        cout << "Choose your action <<<<<<<<<<<<" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Flee" << endl;
        cout << "> ";
        cin >> option;
        cout << "\n";
        switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            myAction.action = [this, target]() {
                doAttack(target);
                gainExperience(30);
                cout << experience << endl;
                cout << getLevel() << endl;
            };
            oks = true;
            break;
        case 2:
            myAction.action = [this, enemies]() {
                flee(enemies);
            };
            oks = true;
            break;
        default:
            cout << RED << "\t!!!!!!!!! Invalid option !!!!!!!!!" << RESET << endl;
            cout << "\n";
            break;
        }
    }
    return myAction;
}
void Player::Depression(int depre){
    depression = depression + depre;
    if ((depression > 50) && (rand() % 100 > 90)) {
        if (rand() % 100 > 50) {
            Suicide();
        }
    }
}
void Player::Suicide() {
        setHealth(getHealth() == 0);
        cout << "\n"; 
        cout << "\t>>>>>>> You, just kill yourself..XD <<<<<<<" << endl;
        cout << "\n";
        cin.get();
        exit(-1);
   

}