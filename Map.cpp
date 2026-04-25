#include "Map.h"

#include <queue>
#include <random>

static std::mt19937 rng(std::random_device{}());  // генератор случайных чисел

Map::Map(int width, int height) : width(width), height(height) {
  tiles.resize(height, std::vector<TileType>(width, TileType::Wall));
  explored.resize(height, std::vector<bool>(width, false));
  floorVariant.resize(height, std::vector<int>(width, 0));
}

struct Room {
  int x1, y1, x2, y2;
};

void Map::loadFromPrefab() {
  // заполняем все клетки стенами
  for (int y = 0; y < height; ++y)
    for (int x = 0; x < width; ++x) tiles[y][x] = TileType::Wall;

  int roomCount = 20 + rng() % 15;
  std::vector<Room> rooms;

  // generate rooms
  for (int i = 0; i < roomCount; ++i) {
    int w = 4 + rng() % 6;
    int h = 4 + rng() % 6;
    int x = 2 + rng() % (width - w - 2);
    int y = 2 + rng() % (height - h - 2);
    bool overlap = false;
    for (const auto& r : rooms) {
      if (x < r.x2 + 2 && x + w > r.x1 - 2 && y < r.y2 + 2 &&
          y + h > r.y1 - 2) {
        overlap = true;
        break;
      }
    }
    if (!overlap) {
      rooms.push_back({x, y, x + w - 1, y + h - 1});
      for (int ry = y; ry <= y + h - 1; ++ry)
        for (int rx = x; rx <= x + w - 1; ++rx) tiles[ry][rx] = TileType::Floor;
    }
  }
  if (rooms.empty()) rooms.push_back({5, 5, 10, 10});

  // соединяем комнаты коридорами (ширина 2)
  for (size_t i = 0; i < rooms.size() - 1; ++i) {
    const auto& a = rooms[i];
    const auto& b = rooms[i + 1];
    int cx = (a.x1 + a.x2) / 2;
    int cy = (a.y1 + a.y2) / 2;
    int cx2 = (b.x1 + b.x2) / 2;
    int cy2 = (b.y1 + b.y2) / 2;
    for (int x = std::min(cx, cx2); x <= std::max(cx, cx2); ++x) {
      if (cy >= 0 && cy < height) tiles[cy][x] = TileType::Floor;
      if (cy + 1 < height) tiles[cy + 1][x] = TileType::Floor;
    }
    for (int y = std::min(cy, cy2); y <= std::max(cy, cy2); ++y) {
      if (cx2 >= 0 && cx2 < width) tiles[y][cx2] = TileType::Floor;
      if (cx2 + 1 < width) tiles[y][cx2 + 1] = TileType::Floor;
    }
  }

  // гарантия пола внутри комнат
  for (const auto& room : rooms) {
    for (int y = room.y1; y <= room.y2; ++y)
      for (int x = room.x1; x <= room.x2; ++x) tiles[y][x] = TileType::Floor;
  }

  // случайные колонны-препятствия
  for (int i = 0; i < 40; ++i) {
    int x = 3 + rng() % (width - 6);
    int y = 3 + rng() % (height - 6);
    if (tiles[y][x] == TileType::Floor && std::abs(x - width / 2) > 5 &&
        std::abs(y - height / 2) > 5)
      tiles[y][x] = TileType::Wall;
  }

  // убедимся, что стартовая позиция (центр) — пол
  int centerX = width / 2;
  int centerY = height / 2;
  tiles[centerY][centerX] = TileType::Floor;
  for (int dy = -1; dy <= 1; ++dy)
    for (int dx = -1; dx <= 1; ++dx)
      if (centerY + dy >= 0 && centerY + dy < height && centerX + dx >= 0 &&
          centerX + dx < width)
        tiles[centerY + dy][centerX + dx] = TileType::Floor;

  // случайный выбор варианта пола (0,1,2)
  std::uniform_int_distribution<int> distFloor(0, 2);
  for (int y = 0; y < height; ++y)
    for (int x = 0; x < width; ++x)
      floorVariant[y][x] =
          (tiles[y][x] == TileType::Floor) ? distFloor(rng) : 0;
}

bool Map::isWalkable(int x, int y) const {
  if (x < 0 || x >= width || y < 0 || y >= height) return false;
  return tiles[y][x] == TileType::Floor;
}

bool Map::isWall(int x, int y) const {
  if (x < 0 || x >= width || y < 0 || y >= height) return true;
  return tiles[y][x] == TileType::Wall;
}

void Map::setTile(int x, int y, TileType type) {
  if (x >= 0 && x < width && y >= 0 && y < height) tiles[y][x] = type;
}

void Map::draw(sf::RenderWindow& window, const sf::Texture& wallTex,
               const sf::Texture& floor1Tex, const sf::Texture& floor2Tex,
               const sf::Texture& floor3Tex) {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (!explored[y][x]) continue;
      if (tiles[y][x] == TileType::Wall) {
        sf::Sprite sprite(wallTex);
        sprite.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
        window.draw(sprite);
      } else {
        const sf::Texture& floorTex = (floorVariant[y][x] == 0)   ? floor1Tex
                                      : (floorVariant[y][x] == 1) ? floor2Tex
                                                                  : floor3Tex;
        sf::Sprite sprite(floorTex);
        sprite.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
        window.draw(sprite);
      }
    }
  }
}

bool Map::isExplored(int x, int y) const {
  if (x < 0 || x >= width || y < 0 || y >= height) return false;
  return explored[y][x];
}

void Map::setExplored(int x, int y, bool exploredVal) {
  if (x >= 0 && x < width && y >= 0 && y < height) explored[y][x] = exploredVal;
}

void Map::updateExploredAround(sf::Vector2i center, int radius) {
  for (int dy = -radius; dy <= radius; ++dy) {
    for (int dx = -radius; dx <= radius; ++dx) {
      if (std::abs(dx) + std::abs(dy) <= radius) {
        int x = center.x + dx;
        int y = center.y + dy;
        if (x >= 0 && x < width && y >= 0 && y < height) explored[y][x] = true;
      }
    }
  }
}
