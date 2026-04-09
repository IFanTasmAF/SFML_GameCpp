#include "PlayState.h"

#include "../core/Game.h"
#include "../entities/AggressiveMonster.h"
#include "../entities/PassiveMonster.h"
#include "GameOverState.h"

PlayState::PlayState(sf::RenderWindow& window, Game* game)
    : game(game), move_delay(0.15f), move_timer(0.f) {
  monsters.push_back(new AggressiveMonster(200, 200));
  monsters.push_back(new PassiveMonster(300, 300));
}

void PlayState::handleInput(sf::RenderWindow& window) {
  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
  }

  if (move_timer < move_delay) return;

  float dx = 0, dy = 0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) dy = -32;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) dy = 32;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) dx = -32;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) dx = 32;

  if (dx != 0 || dy != 0) {
    player.move(dx, dy, map);
    move_timer = 0;
  }
}

void PlayState::update(float dt) {
  move_timer += dt;

  for (auto m : monsters) {
    m->update(player, map);
  }

  if (player.getHp() <= 0) {
    game->changeState(new GameOverState(game->getWindow()));
  }
}

void PlayState::render(sf::RenderWindow& window) {
  map.draw(window);
  player.draw(window);

  for (auto m : monsters) {
    m->draw(window);
  }

  ui.draw(window, player);
}
