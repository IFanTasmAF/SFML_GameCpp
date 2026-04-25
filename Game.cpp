#include "Game.h"

#include "Constants.h"
#include "ExploringState.h"

Game::Game()
    : window_(sf::VideoMode({static_cast<unsigned int>(WINDOW_WIDTH),
                             static_cast<unsigned int>(WINDOW_HEIGHT)}),
              "Cosmic Horror Dungeon") {
  window_.setFramerateLimit(60);
  stateStack_.push_back(std::make_unique<ExploringState>(*this));
}

void Game::run() {
  while (window_.isOpen()) {
    while (auto event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window_.close();
      if (!stateStack_.empty()) stateStack_.back()->handleInput(*event, *this);
    }
    float dt = clock_.restart().asSeconds();
    if (!stateStack_.empty()) stateStack_.back()->update(dt);
    window_.clear(sf::Color::Black);
    if (!stateStack_.empty()) stateStack_.back()->draw(window_);
    window_.display();
  }
}

void Game::changeState(std::unique_ptr<GameState> newState) {
  stateStack_.push_back(std::move(newState));
}

void Game::popState() {
  if (stateStack_.size() > 1)
    stateStack_.pop_back();
  else
    window_.close();
}
