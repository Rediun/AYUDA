//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "./ActionResult.h"

class Enemy;

class Player: public Character {
protected:
    int experience;
    int level;
    int depression;
public:
    Player(char _name[40], int _health, int _attack, int _defense, int _speed, int _level);
    void doAttack(Character *target, vector<Enemy*> enemies);
    void takeDamage(int damage) override;

    Character* getTarget(vector<Enemy*> enemies);

    void flee(vector<Enemy*> enemies);
    void emote();
    void levelUp(vector<Enemy*> enemies);
    void gainExperience(int, vector<Enemy*> enemies);
    Action takeAction(vector<Enemy*> enemies);

    void Suicide();
    void Depression(int);
};


#endif //RPG_PLAYER_H
