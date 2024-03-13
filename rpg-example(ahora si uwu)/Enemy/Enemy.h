//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Player/ActionResult.h"

class Player;

class Enemy: public Character {
public:
    Enemy(string, int, int, int, int);
    int getMaxHealth();
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* getTarget(vector<Player*> teamMembers);
    Action takeAction(vector<Player*> teamMembers);
};


#endif //RPG_ENEMY_H
