#pragma once
#include "Entity.h"

class Player : public Entity {
 public:
  Player(float x, float y);

  void move(float dx, float dy, Map& map);

  void update(float dt) override;
  void draw(sf::RenderWindow& window) override;

  int getHp() const;

 private:
  int hp;
};
