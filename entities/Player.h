#pragma once
#include "Entity.h"

class Player : public Entity {
 private:
  float speed = 200.f;
  int hp = 100;

 public:
  Player(float x, float y);

  void update(float dt) override;

  int getHp() const { return hp; }
};
