#pragma once
#include "Entity.h"

class Player : public Entity {
 private:
  sf::Vector2f velocity;

  float acceleration = 800.f;
  float maxSpeed = 300.f;
  float friction = 600.f;

 public:
  Player(float x, float y);

  void update(float dt) override;
  void draw(sf::RenderWindow& window) override;
};
