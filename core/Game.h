#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class GameState;

class Game {
 public:
  Game();
  ~Game();

  void run();
  void changeState(GameState* new_state);

  sf::RenderWindow& getWindow();

 private:
  sf::RenderWindow window;
  GameState* current_state;
};

#endif
