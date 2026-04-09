#pragma once
#include "Monster.h"

class AggressiveMonster : public Monster {
public:
    AggressiveMonster(float x, float y);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};