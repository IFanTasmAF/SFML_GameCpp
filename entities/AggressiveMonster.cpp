#include "AggressiveMonster.h"

AggressiveMonster::AggressiveMonster(float x, float y) : Monster(x, y) {
  shape.setSize(sf::Vector2f(40.f, 40.f));
  shape.setFillColor(sf::Color::Red);
}

void AggressiveMonster::update(float dt) {
  // простое движение (пока заглушка)
  shape.move(50.f * dt, 0);
}

void AggressiveMonster::draw(sf::RenderWindow& window) { window.draw(shape); }
