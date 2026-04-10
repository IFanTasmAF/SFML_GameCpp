#pragma once
#include "Entity.h"

class Monster : public Entity {
 protected:
  float speed;

 public:
  Monster(float x, float y);

  virtual void update(float dt, const sf::Vector2f& playerPos);
};
