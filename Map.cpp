#include "Map.h"

#include <queue>
#include <random>

static std::mt19937 rng(
    std::random_device{}());

Map::Map(int width, int height) : width_(width), height_(height) {
  tiles_.resize(height, std::vector<TileType>(width, TileType::Wall));
  explored_.resize(height, std::vector<bool>(width, false));
  floorVariant_.resize(height, std::vector<int>(width, 0));
}

struct Room {
  int x1, y1, x2, y2;
};

void Map::loadFromPrefab() {
  // Генерация комнат и коридоров
  for (int y = 0; y < height_; ++y)
    for (int x = 0; x < width_; ++x) tiles_[y][x] = TileType::Wall;

  int roomCount = 20 + rng() % 15;
  std::vector<Room> rooms;
  for (int i = 0; i < roomCount; ++i) {
    int w = 4 + rng() % 6;
    int h = 4 + rng() % 6;
    int x = 2 + rng() % (width_ - w - 2);
    int y = 2 + rng() % (height_ - h - 2);
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
        for (int rx = x; rx <= x + w - 1; ++rx)
          tiles_[ry][rx] = TileType::Floor;
    }
  }
  if (rooms.empty()) rooms.push_back({5, 5, 10, 10});

  // Соединение комнат коридорами (ширина 2)
  for (size_t i = 0; i < rooms.size() - 1; ++i) {
    const auto& a = rooms[i];
    const auto& b = rooms[i + 1];
    int cx = (a.x1 + a.x2) / 2;
    int cy = (a.y1 + a.y2) / 2;
    int cx2 = (b.x1 + b.x2) / 2;
    int cy2 = (b.y1 + b.y2) / 2;
    for (int x = std::min(cx, cx2); x <= std::max(cx, cx2); ++x) {
      if (cy >= 0 && cy < height_) tiles_[cy][x] = TileType::Floor;
      if (cy + 1 < height_) tiles_[cy + 1][x] = TileType::Floor;
    }
    for (int y = std::min(cy, cy2); y <= std::max(cy, cy2); ++y) {
      if (cx2 >= 0 && cx2 < width_) tiles_[y][cx2] = TileType::Floor;
      if (cx2 + 1 < width_) tiles_[y][cx2 + 1] = TileType::Floor;
    }
  }

  // Заполняем все клетки комнат полом
  for (const auto& room : rooms) {
    for (int y = room.y1; y <= room.y2; ++y)
      for (int x = room.x1; x <= room.x2; ++x) tiles_[y][x] = TileType::Floor;
  }

  // Случайные стены-колонны
  for (int i = 0; i < 40; ++i) {
    int x = 3 + rng() % (width_ - 6);
    int y = 3 + rng() % (height_ - 6);
    if (tiles_[y][x] == TileType::Floor && std::abs(x - width_ / 2) > 5 &&
        std::abs(y - height_ / 2) > 5)
      tiles_[y][x] = TileType::Wall;
  }

  // Гарантия пола в центре (стартовая позиция героя)
  int centerX = width_ / 2;
  int centerY = height_ / 2;
  tiles_[centerY][centerX] = TileType::Floor;
  for (int dy = -1; dy <= 1; ++dy)
    for (int dx = -1; dx <= 1; ++dx)
      if (centerY + dy >= 0 && centerY + dy < height_ && centerX + dx >= 0 &&
          centerX + dx < width_)
        tiles_[centerY + dy][centerX + dx] = TileType::Floor;

  // Случайный выбор варианта пола для каждой клетки (3 текстуры)
  std::uniform_int_distribution<int> distFloor(0, 2);
  for (int y = 0; y < height_; ++y)
    for (int x = 0; x < width_; ++x)
      floorVariant_[y][x] =
          (tiles_[y][x] == TileType::Floor) ? distFloor(rng) : 0;
}

// Методы работы с картой
bool Map::isWalkable(int x, int y) const {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) return false;
  return tiles_[y][x] == TileType::Floor;
}

bool Map::isWall(int x, int y) const {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) return true;
  return tiles_[y][x] == TileType::Wall;
}

void Map::setTile(int x, int y, TileType type) {
  if (x >= 0 && x < width_ && y >= 0 && y < height_) tiles_[y][x] = type;
}

void Map::draw(sf::RenderWindow& window, const sf::Texture& wallTex,
               const sf::Texture& floor1Tex, const sf::Texture& floor2Tex,
               const sf::Texture& floor3Tex) {
  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      if (!explored_[y][x]) continue;  // туман войны
      if (tiles_[y][x] == TileType::Wall) {
        sf::Sprite sprite(wallTex);
        sprite.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
        window.draw(sprite);
      } else {
        const sf::Texture& floorTex = (floorVariant_[y][x] == 0)   ? floor1Tex
                                      : (floorVariant_[y][x] == 1) ? floor2Tex
                                                                   : floor3Tex;
        sf::Sprite sprite(floorTex);
        sprite.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
        window.draw(sprite);
      }
    }
  }
}

// Туман войны
bool Map::isExplored(int x, int y) const {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) return false;
  return explored_[y][x];
}

void Map::setExplored(int x, int y, bool explored) {
  if (x >= 0 && x < width_ && y >= 0 && y < height_) explored_[y][x] = explored;
}

void Map::updateExploredAround(sf::Vector2i center, int radius) {
  for (int dy = -radius; dy <= radius; ++dy) {
    for (int dx = -radius; dx <= radius; ++dx) {
      if (std::abs(dx) + std::abs(dy) <= radius) {
        int x = center.x + dx;
        int y = center.y + dy;
        if (x >= 0 && x < width_ && y >= 0 && y < height_)
          explored_[y][x] = true;
      }
    }
  }
}
