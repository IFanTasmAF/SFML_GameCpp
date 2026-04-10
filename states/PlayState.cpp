#include "PlayState.h"

#include <cmath>

#include "../entities/AggressiveMonster.h"
#include "../entities/PassiveMonster.h"

bool isCollidingWithWall(const Map& map, const sf::FloatRect& bounds) {
  int left = static_cast<int>(bounds.position.x) / 32;
  int right = static_cast<int>(bounds.position.x + bounds.size.x) / 32;
  int top = static_cast<int>(bounds.position.y) / 32;
  int bottom = static_cast<int>(bounds.position.y + bounds.size.y) / 32;

  return !map.isWalkable(left, top) || !map.isWalkable(right, top) ||
         !map.isWalkable(left, bottom) || !map.isWalkable(right, bottom);
}

PlayState::PlayState() {
  monsters.push_back(new AggressiveMonster(300.f, 300.f));
  monsters.push_back(new PassiveMonster(500.f, 200.f));
}

void PlayState::handleInput(sf::RenderWindow& window) {
  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) window.close();
  }
}

void PlayState::update(float dt) {
  // ===== ÈÃÐÎÊ =====
  sf::Vector2f oldPos = player.getPosition();

  player.update(dt);

  if (isCollidingWithWall(map, player.getBounds())) {
    player.setPosition(oldPos);
  }

  // ===== ÂÐÀÃÈ =====
  for (auto monster : monsters) {
    sf::Vector2f oldPosM = monster->getPosition();

    monster->update(dt, player.getPosition());

    if (isCollidingWithWall(map, monster->getBounds())) {
      monster->setPosition(oldPosM);
    }
  }

  // ===== ÑÒÎËÊÍÎÂÅÍÈß Ñ ÈÃÐÎÊÎÌ =====
  for (auto monster : monsters) {
    auto intersection =
        monster->getBounds().findIntersection(player.getBounds());

    if (intersection.has_value()) {
      sf::Vector2f dir = player.getPosition() - monster->getPosition();

      float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

      if (len > 0.f) {
        dir /= len;
        monster->move(-dir * 150.f * dt);
      }
    }
  }
}

void PlayState::render(sf::RenderWindow& window) {
  map.draw(window);

  player.draw(window);

  for (auto monster : monsters) monster->draw(window);

  ui.draw(player, window);
}
