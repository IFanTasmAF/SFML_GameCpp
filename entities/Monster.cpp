#include "Monster.h"

#include <cmath>

Monster::Monster(float x, float y) : Entity(x, y), speed(100.f) {
  shape.setFillColor(sf::Color::Red);
}

void Monster::update(float dt, const sf::Vector2f& playerPos) {
  sf::Vector2f dir = playerPos - getPosition();

  float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

  if (len > 0) {
    dir /= len;

    // движение с dt
    move(dir * speed * dt);
  }
}
