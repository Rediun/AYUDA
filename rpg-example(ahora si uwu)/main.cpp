#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"

int main() {
                                 
    Player *player = new Player("Gringo", 20, 10, 5, 1, 1);
    Enemy *enemy = new Enemy("Maldito SAT como te odio", 20, 6, 3, 7, 1);
    Enemy *enemy2 = new Enemy("SATan", 30, 8, 5, 2, 1);

    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;
    return 0;
}
