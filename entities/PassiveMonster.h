#pragma once
#include "Monster.h"

class PassiveMonster : public Monster {
 public:
  PassiveMonster(float x, float y);

  void update(float dt) override;
  void draw(sf::RenderWindow& window) override;
};
