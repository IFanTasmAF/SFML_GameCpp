#pragma once
#include "Entity.h"

class Monster : public Entity {
public:
    Monster(float x, float y) : Entity(x, y) {}

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};