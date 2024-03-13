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

Player::Player(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, true) {
    experience = 0;
    level = 1;
    depression = 0;
}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    if (health <= 0) {
        cout << RED<< "\t------X You have died, You are a really Crap X------" << RESET<< endl;
        cout << "\n";
        cin.get();
    }
    else {
        cout << CYAN << "\t-----> You have taken "  << damage << " damage <-----" << RESET << endl;
        cout << "\n";
        Depression(5);
        cin.get();
    }
}
         

   


bool Player::flee(vector<Enemy*> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy* fastestEnemy = enemies[0];
    bool fleed = false;
    if(this->getSpeed() > fastestEnemy->getSpeed()) {
        fleed =  true;
    }
    else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout<< "chance: " << chance << endl;
        fleed = chance > 99;
    }

    return fleed;
}

void Player::emote() {
    cout<<"Jokes on you" << endl;
}

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 5);
    setSpeed(getSpeed() + 5);

    cout << YELLOW << "\t>>>>>>>>> Level up bro!!!! Your level current: " << level << " <<<<<<<<<<<<" << RESET << endl;
    cout << "\n\n";
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 0;
    }
}

Character* Player::getTarget(vector<Enemy*> enemies) {
    int targetIndex = 0;
    while (true) {
        cout << "Choose your Victim" << endl;
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

ActionResult Player::takeAction(vector<Enemy*> enemies) {
    int option = 0;
    bool oks = false;
    Character* target = nullptr;
    bool fleed = false;
    
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
            doAttack(target);
            gainExperience(33);
            oks = true;
            break;
        case 2:
            fleed = flee(enemies);
            if (fleed) {
                cout << MAGENTA << "\t>>> You have fled <<<" << RESET << endl;
                cout << "\n";
                cin.get();
            }
            else {
                cout << RED << "\t>>> You couldn't flee <<<" << RESET << endl;
                cout << "\n";
                cin.get();
            }
            oks = true;
            break;
        default:
            cout << RED << "\t!!!!!!!!! Invalid option !!!!!!!!!" << RESET << endl;
            cout << "\n";
            break;
        }
    }
    return ActionResult(target, fleed);
}
void Player::Depression(int depre){
    depression = depression + depre;
    if ((depression > 50) && (rand() % 100 > 90)) {
        if (rand() % 100 > 10) {
            Suicide();
        }
    }
}
void Player::Suicide() {
        setHealth(getHealth() == 0);
        cout << "\n"; 
        cout << "\t>>>>>>> You, just kill yourself..XD <<<<<<<" << endl;
        cout << "\n";
   

}