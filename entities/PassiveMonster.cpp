#include "PassiveMonster.h"

PassiveMonster::PassiveMonster(float x, float y) : Monster(x, y) {
  shape.setSize(sf::Vector2f(40.f, 40.f));
  shape.setFillColor(sf::Color::Blue);
}

void PassiveMonster::update(float dt) {
  // стоит на месте
}

void PassiveMonster::draw(sf::RenderWindow& window) { window.draw(shape); }
