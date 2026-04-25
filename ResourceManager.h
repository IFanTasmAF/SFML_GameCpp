#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "Constants.h"

class ResourceManager {
 public:
  static ResourceManager& getInstance();
  sf::Texture& getTexture(const std::string& key);
  sf::Font& getFont();

 private:
  ResourceManager();
  std::map<std::string, sf::Texture> textures_;
  sf::Font font_;
};
