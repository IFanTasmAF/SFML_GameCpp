#include "Game.h"

#include "../states/GameState.h"
#include "../states/PlayState.h"

Game::Game() : window(sf::VideoMode({800, 600}), "Game") {
  current_state = new PlayState(window, this);
}

Game::~Game() { delete current_state; }

void Game::changeState(GameState* new_state) {
  delete current_state;
  current_state = new_state;
}

void Game::run() {
  sf::Clock clock;

  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    current_state->handleInput(window);
    current_state->update(dt);

    window.clear();
    current_state->render(window);
    window.display();
  }
}

sf::RenderWindow& Game::getWindow() { return window; }
