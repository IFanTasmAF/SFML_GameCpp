#pragma once
#include "Monster.h"

class PassiveMonster : public Monster {
 public:
  PassiveMonster(float x, float y);

  void update(float dt, const sf::Vector2f& playerPos) override;
};
