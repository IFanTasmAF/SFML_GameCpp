#include "PassiveMonster.h"

PassiveMonster::PassiveMonster(float x, float y) : Monster(x, y) {
  shape.setFillColor(sf::Color::Yellow);
}

void PassiveMonster::update(float dt, const sf::Vector2f& playerPos) {
  // ничего не делает
}
