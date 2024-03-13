//
// Created by Victor Navarro on 26/02/24.
//

#ifndef RPG_ACTIONRESULT_H
#define RPG_ACTIONRESULT_H
#include "../Character/Character.h"
#include <functional>

struct Action {
    int speed = 0;
    Character* subscriber = nullptr;
    Character* target = nullptr;
    std::function<void(void)> action = nullptr;

    Action(std::function<void(void)> _action, int _speed, Character* _subscriber, Character* _target) {
        action = _action;
        speed = _speed;
        subscriber = _subscriber;
        target = _target;
    }
    Action() {};

    bool operator<(const Action& p) const
    {
        return this->speed < p.speed;
    }
};

#endif //RPG_ACTIONRESULT_H
