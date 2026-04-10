#include "Map.h"

Map::Map() {
  width = 25;
  height = 18;
  tile_size = 32;

  grid.resize(height, std::vector<Tile>(width));

  generate();
}

void Map::generate() {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (rand() % 8 == 0)
        grid[y][x] = Tile(TileType::Wall);
      else
        grid[y][x] = Tile(TileType::Floor);
    }
  }
}

bool Map::isWalkable(int x, int y) const {
  if (x < 0 || y < 0 || x >= width || y >= height) return false;

  return grid[y][x].type == TileType::Floor;
}

void Map::draw(sf::RenderWindow& window) {
  sf::RectangleShape rect({(float)tile_size, (float)tile_size});

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      rect.setPosition({x * (float)tile_size, y * (float)tile_size});

      if (grid[y][x].type == TileType::Wall)
        rect.setFillColor(sf::Color::Blue);
      else
        rect.setFillColor(sf::Color(30, 30, 30));

      window.draw(rect);
    }
  }
}
