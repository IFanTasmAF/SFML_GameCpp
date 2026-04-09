#include "AggressiveMonster.h"

AggressiveMonster::AggressiveMonster(float x, float y) : Entity(x, y) {
  shape.setSize({40.f, 40.f});
  shape.setFillColor(sf::Color::Red);
}

void AggressiveMonster::update(float dt) { shape.move({50.f * dt, 0.f}); }
