#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.h"

class Map {
 private:
  std::vector<std::vector<Tile>> grid;
  int width;
  int height;
  int tile_size;

 public:
  Map();

  void generate();
  void draw(sf::RenderWindow& window);

  bool isWalkable(int x, int y);
};
