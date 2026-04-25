#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Hero;

class UIManager {
 public:
  UIManager(sf::Font& font);
  void draw(sf::RenderWindow& window, const Hero& hero,
            const std::string& message = "");

 private:
  sf::Font& font;
  sf::Text healthText, potionText, messageText;
};
