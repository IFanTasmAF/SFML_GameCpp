#include "PlayState.h"

#include "../entities/AggressiveMonster.h"
#include "../entities/PassiveMonster.h"

PlayState::PlayState() : player(100.f, 100.f) {
  monsters.push_back(new AggressiveMonster(300.f, 200.f));
  monsters.push_back(new PassiveMonster(500.f, 300.f));
}

void PlayState::update(float dt) {
  player.update(dt);

  for (auto monster : monsters) {
    monster->update(dt);
  }
}

void PlayState::draw(sf::RenderWindow& window) {
  player.draw(window);

  for (auto monster : monsters) {
    monster->draw(window);
  }
}
