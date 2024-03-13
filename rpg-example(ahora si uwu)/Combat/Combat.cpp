//
// Created by Victor Navarro on 19/02/24.
//
#include "Combat.h"
#include <iostream>
#include <algorithm>

using namespace std;

#define RESET   "\033[0m"      
#define RED     "\033[31m"      
#define GREEN   "\033[32m"     
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"    

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant: participants) {
        if(participant->getIsPlayer()) {
            teamMembers.push_back((Player*)participant);
        }
        else {
            enemies.push_back((Enemy*)participant);
        }
    }
}

Combat::Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies) {
    teamMembers = std::move(_teamMembers);
    enemies = std::move(_enemies);
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()) {
        teamMembers.push_back((Player*)participant);
    }
    else {
        enemies.push_back((Enemy*)participant);
    }
}

void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed);
}

void Combat::doCombat() {
    prepareCombat();

    //Este while es 1 iteracion por ronda
    while (enemies.size() != 0 && teamMembers.size() != 0) {
        registerActions();
        executeActions();
    }

    //No se imprime el nombre del ganador
    if (enemies.size() == 0) {
        cout << YELLOW << "\t///////////// You win bastard /////////////" << RESET << endl;
    }
    else {
        cout << RED<< "\t///////////// The enemies have won the combat - Game Over /////////////" << RESET << endl;
    }
}

string Combat::participantsToString() {
    string result = "";
    for (int i = 0; i < participants.size(); i++) {
        result += participants[i]->toString() + "\n";
    }
    return result;
}

void Combat::registerActions() {
    vector<Character*>::iterator participant = participants.begin();
    //Una iteracion por turno de cada participante (player y enemigo)
    while (participant != participants.end()) {
        Character* target = nullptr;
        Action currentAction;
        if ((*participant)->getIsPlayer()) {
            currentAction = ((Player*)*participant)->takeAction(enemies);
        }
        else {
            currentAction = ((Enemy*)*participant)->takeAction(teamMembers);
        }
        actions.push(currentAction);
        participant++;
    }
}

void Combat::executeActions() {
    //Aqui se ejecutan las acciones
    while (!actions.empty()) {
        Action currentAction = actions.top();
        currentAction.action();
        checkForFlee(currentAction.subscriber);
        if (currentAction.target != nullptr) {
            checkParticipantStatus(currentAction.subscriber);
            checkParticipantStatus(currentAction.target);
            actions.pop();
        }
        else {
            while (!actions.empty()) {
                actions.pop();
            }
        }
    }
}
void Combat::checkParticipantStatus(Character* participant) {
    if (participant->getHealth() <= 0) {
        if (participant->getIsPlayer()) {
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), participant), teamMembers.end());
        }
        else {
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::checkForFlee(Character* character) {
    bool fleed = character->hasFleed();
    if (character->getHealth() != 0 && character->getHealth() > 0) {
        if (fleed) {
            if (character->getIsPlayer()) {
                cout << CYAN << "\t>>>> You are a good Chicken you have fleed the combat <<<<" << RESET << endl;
                cout << "\n\n";
                teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), character), teamMembers.end());
            }
            else {
                cout << MAGENTA << "\t:D     " << character->getName() << " Go for milk (never come back)     D:" << RESET << endl;
                cout << "\n\n";
                enemies.erase(remove(enemies.begin(), enemies.end(), character), enemies.end());
            }
            participants.erase(remove(participants.begin(), participants.end(), character), participants.end());
        }
    }
}