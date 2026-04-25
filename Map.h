#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Constants.h"

enum class TileType { Wall, Floor };

class Map {
 public:
  Map(int width, int height);
  void loadFromPrefab();
  bool isWalkable(int x, int y) const;
  bool isWall(int x, int y) const;
  void setTile(int x, int y, TileType type);
  void draw(sf::RenderWindow& window, const sf::Texture& wallTex,
            const sf::Texture& floor1Tex, const sf::Texture& floor2Tex,
            const sf::Texture& floor3Tex);
  int getWidth() const { return width_; }
  int getHeight() const { return height_; }

  bool isExplored(int x, int y) const;
  void setExplored(int x, int y, bool explored);
  void updateExploredAround(sf::Vector2i center, int radius);

 private:
  int width_, height_;
  std::vector<std::vector<TileType>> tiles_;
  std::vector<std::vector<bool>> explored_;
  std::vector<std::vector<int>> floorVariant_;
};
