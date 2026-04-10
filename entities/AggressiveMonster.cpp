#include "AggressiveMonster.h"

#include <cmath>

AggressiveMonster::AggressiveMonster(float x, float y) : Monster(x, y) {
  shape.setFillColor(sf::Color::Red);
}

void AggressiveMonster::update(float dt, const sf::Vector2f& playerPos) {
  sf::Vector2f dir = playerPos - getPosition();

  float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

  if (len > 0) {
    dir /= len;

    // держим дистанцию (фикс прилипания)
    if (len > 25.f) {
      move(dir * 120.f * dt);
    }
  }
}
