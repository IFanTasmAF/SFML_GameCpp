#include "PassiveMonster.h"

PassiveMonster::PassiveMonster(float x, float y) : Entity(x, y) {
  shape.setSize({40.f, 40.f});
  shape.setFillColor(sf::Color::Blue);
}

void PassiveMonster::update(float dt) {
  // ничего не делает
}
