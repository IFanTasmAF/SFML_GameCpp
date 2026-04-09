#include "AggressiveMonster.h"

#include "../entities/Player.h"
#include "../world/Map.h"

AggressiveMonster::AggressiveMonster(int x, int y) : Entity(x, y, 30, 10) {}

void AggressiveMonster::update(Player& player, Map& map) {
  int dx = 0;
  int dy = 0;

  if (player.getX() > x)
    dx = 1;
  else if (player.getX() < x)
    dx = -1;

  if (player.getY() > y)
    dy = 1;
  else if (player.getY() < y)
    dy = -1;

  int new_x = x + dx;
  int new_y = y + dy;

  if (map.isWalkable(new_x, new_y)) {
    x = new_x;
    y = new_y;
  }
}

void AggressiveMonster::draw(sf::RenderWindow& window) {
  sf::RectangleShape rect({32.f, 32.f});
  rect.setPosition({x * 32.f, y * 32.f});
  rect.setFillColor(sf::Color::Red);
  window.draw(rect);
}
