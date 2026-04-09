#include "PassiveMonster.h"

#include <cstdlib>

#include "../world/Map.h"

PassiveMonster::PassiveMonster(int x, int y) : Entity(x, y, 20, 5) {}

void PassiveMonster::update(Player&, Map& map) {
  if (rand() % 5 != 0) return;

  int dx = (rand() % 3) - 1;
  int dy = (rand() % 3) - 1;

  int new_x = x + dx;
  int new_y = y + dy;

  if (map.isWalkable(new_x, new_y)) {
    x = new_x;
    y = new_y;
  }
}

void PassiveMonster::draw(sf::RenderWindow& window) {
  sf::RectangleShape rect({32.f, 32.f});
  rect.setPosition({x * 32.f, y * 32.f});
  rect.setFillColor(sf::Color::Yellow);
  window.draw(rect);
}
