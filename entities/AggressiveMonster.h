#pragma once
#include "Monster.h"

class AggressiveMonster : public Monster {
 public:
  AggressiveMonster(float x, float y);

  void update(float dt, const sf::Vector2f& playerPos) override;
};
