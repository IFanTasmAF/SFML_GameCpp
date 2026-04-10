#pragma once
#include "Entity.h"

class Player : public Entity {
 private:
  float speed;
  int hp;

 public:
  Player();

  void update(float dt) override;

  int getHp() const;

  sf::Vector2f getVelocity() const;
};
