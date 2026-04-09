#include "PlayState.h"

PlayState::PlayState() : player(100.f, 100.f) {
  monsters.push_back(new AggressiveMonster(200.f, 200.f));
  monsters.push_back(new PassiveMonster(300.f, 300.f));
}

void PlayState::update(float dt) {
  player.update(dt);

  for (auto m : monsters) m->update(dt);
}

void PlayState::draw(sf::RenderWindow& window) {
  player.draw(window);

  for (auto m : monsters) m->draw(window);
}
