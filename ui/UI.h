#pragma once
#include <SFML/Graphics.hpp>

#include "../entities/Player.h"

class UI {
 public:
  void draw(Player& player, sf::RenderWindow& window);
};
