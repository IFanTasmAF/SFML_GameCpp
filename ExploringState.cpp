#include "ExploringState.h"

#include <algorithm>
#include <cmath>
#include <queue>
#include <random>
#include <set>

#include "Centipede.h"
#include "Chest.h"
#include "CombatState.h"
#include "Constants.h"
#include "Exit.h"
#include "Game.h"
#include "GameOverState.h"
#include "Larva.h"
#include "ResourceManager.h"

std::mt19937 rng(std::random_device{}());

// ------------------- вспомогательные функции -------------------
sf::Vector2i getRandomEmptyFloorPosition(
    const Map& map, const std::vector<std::unique_ptr<Entity>>& entities,
    const sf::Vector2i& avoidPos, int minDistance) {
  std::vector<sf::Vector2i> candidates;
  for (int y = 0; y < MAP_HEIGHT; ++y)
    for (int x = 0; x < MAP_WIDTH; ++x) {
      if (!map.isWalkable(x, y)) continue;
      bool occupied = false;
      for (auto& e : entities)
        if (e->getPosition() == sf::Vector2i(x, y)) {
          occupied = true;
          break;
        }
      if (occupied) continue;
      int dist = std::abs(x - avoidPos.x) + std::abs(y - avoidPos.y);
      if (dist >= minDistance) candidates.push_back(sf::Vector2i(x, y));
    }
  if (candidates.empty()) {
    for (int y = 0; y < MAP_HEIGHT; ++y)
      for (int x = 0; x < MAP_WIDTH; ++x)
        if (map.isWalkable(x, y)) return sf::Vector2i(x, y);
    return sf::Vector2i(1, 1);
  }
  std::uniform_int_distribution<int> dist(
      0, static_cast<int>(candidates.size()) - 1);
  return candidates[dist(rng)];
}

struct CentipedePlacement {
  sf::Vector2i head;
  sf::Vector2i direction;
};

CentipedePlacement getRandomPositionForCentipede(
    const Map& map, const std::vector<std::unique_ptr<Entity>>& entities,
    const sf::Vector2i& avoidPos, int minDistance, int requiredLength) {
  std::vector<CentipedePlacement> candidates;
  const sf::Vector2i dirs[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  for (int y = 0; y < MAP_HEIGHT; ++y) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
      if (!map.isWalkable(x, y)) continue;
      bool occupied = false;
      for (auto& e : entities)
        if (e->getPosition() == sf::Vector2i(x, y)) {
          occupied = true;
          break;
        }
      if (occupied) continue;
      int dist = std::abs(x - avoidPos.x) + std::abs(y - avoidPos.y);
      if (dist < minDistance) continue;
      for (const auto& dir : dirs) {
        bool ok = true;
        for (int i = 1; i < requiredLength; ++i) {
          int nx = x + dir.x * i;
          int ny = y + dir.y * i;
          if (nx < 0 || nx >= MAP_WIDTH || ny < 0 || ny >= MAP_HEIGHT) {
            ok = false;
            break;
          }
          if (!map.isWalkable(nx, ny)) {
            ok = false;
            break;
          }
        }
        if (ok) {
          candidates.push_back({sf::Vector2i(x, y), dir});
          break;
        }
      }
    }
  }
  // fallback: если нет идеального места, ищем любую свободную клетку для головы
  if (candidates.empty()) {
    sf::Vector2i fallback =
        getRandomEmptyFloorPosition(map, entities, avoidPos, minDistance);
    // используем направление вниз (0,1) – если нет места, будет только голова
    return {fallback, {0, 1}};
  }
  std::uniform_int_distribution<int> dist(
      0, static_cast<int>(candidates.size()) - 1);
  return candidates[dist(rng)];
}

sf::Vector2i findFarthestReachable(const Map& map, sf::Vector2i start) {
  std::queue<sf::Vector2i> q;
  std::vector<std::vector<bool>> visited(MAP_HEIGHT,
                                         std::vector<bool>(MAP_WIDTH, false));
  q.push(start);
  visited[start.y][start.x] = true;
  sf::Vector2i farthest = start;
  int maxDist = 0;
  while (!q.empty()) {
    sf::Vector2i cur = q.front();
    q.pop();
    int dist = std::abs(cur.x - start.x) + std::abs(cur.y - start.y);
    if (dist > maxDist) {
      maxDist = dist;
      farthest = cur;
    }
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {1, 0, -1, 0};
    for (int i = 0; i < 4; ++i) {
      sf::Vector2i nxt(cur.x + dx[i], cur.y + dy[i]);
      if (nxt.x >= 0 && nxt.x < MAP_WIDTH && nxt.y >= 0 && nxt.y < MAP_HEIGHT &&
          !visited[nxt.y][nxt.x] && map.isWalkable(nxt.x, nxt.y)) {
        visited[nxt.y][nxt.x] = true;
        q.push(nxt);
      }
    }
  }
  return farthest;
}

// ------------------- конструктор -------------------
ExploringState::ExploringState(Game& game)
    : game_(game),
      map_(MAP_WIDTH, MAP_HEIGHT),
      hero_(sf::Vector2i(MAP_WIDTH / 2, MAP_HEIGHT / 2),
            ResourceManager::getInstance().getTexture("hero")),
      ui_(ResourceManager::getInstance().getFont()),
      messageTimer_(0.f),
      lastMoveDirection_(0, 0),
      currentDt_(0.f) {
  map_.loadFromPrefab();
  map_.updateExploredAround(hero_.getPosition(), VIEW_RADIUS);

  auto& tex = ResourceManager::getInstance();
  entities_.clear();

  // личинки
  for (int i = 0; i < 4; ++i) {
    sf::Vector2i pos =
        getRandomEmptyFloorPosition(map_, entities_, hero_.getPosition(), 4);
    entities_.push_back(std::make_unique<Larva>(pos, tex.getTexture("larva")));
  }

  // многоножка
  CentipedePlacement placement = getRandomPositionForCentipede(
      map_, entities_, hero_.getPosition(), 7, CENTIPEDE_LENGTH);
  addCentipede(placement.head, placement.direction);

  // сундуки
  std::vector<LootType> loots = {LootType::HealthPotion, LootType::InstantHeal,
                                 LootType::Trap};
  for (int i = 0; i < 3; ++i) {
    sf::Vector2i pos =
        getRandomEmptyFloorPosition(map_, entities_, hero_.getPosition(), 3);
    entities_.push_back(std::make_unique<Chest>(pos, tex.getTexture("chest"),
                                                loots[i % loots.size()]));
  }

  // выход
  sf::Vector2i exitPos = findFarthestReachable(map_, hero_.getPosition());
  entities_.push_back(std::make_unique<Exit>(exitPos, tex.getTexture("exit")));

  // камера: приближаем (уменьшаем размер вида)
  float zoomFactor = 0.8f;  // приближение
  camera_.setSize(sf::Vector2f(static_cast<float>(WINDOW_WIDTH) * zoomFactor,
                               static_cast<float>(WINDOW_HEIGHT) * zoomFactor));
  updateCamera();
}

void ExploringState::addCentipede(const sf::Vector2i& headPos,
                                  const sf::Vector2i& direction) {
  std::vector<sf::Vector2i> positions;
  positions.push_back(headPos);
  for (int i = 1; i < CENTIPEDE_LENGTH; ++i)
    positions.push_back(headPos + direction * i);

  std::vector<CentipedeSegment*> segments;
  for (size_t i = 0; i < positions.size(); ++i) {
    CentipedeSegment::SegmentType type;
    if (i == 0)
      type = CentipedeSegment::SegmentType::Head;
    else if (i == positions.size() - 1)
      type = CentipedeSegment::SegmentType::Tail;
    else
      type = CentipedeSegment::SegmentType::Body;
    auto seg = std::make_unique<CentipedeSegment>(positions[i], type, i == 0);
    segments.push_back(seg.get());
    entities_.push_back(std::move(seg));
  }
  for (size_t i = 0; i < segments.size(); ++i) {
    if (i > 0) segments[i]->setPrevSegment(segments[i - 1]);
    if (i < segments.size() - 1) segments[i]->setNextSegment(segments[i + 1]);
  }
}

CentipedeSegment* ExploringState::getCentipedeHead() {
  for (auto& e : entities_) {
    if (auto* seg = dynamic_cast<CentipedeSegment*>(e.get())) {
      if (seg->isHead()) return seg;
    }
  }
  return nullptr;
}

void ExploringState::handleInput(const sf::Event& event, Game& game) {
  if (!hero_.isAlive()) return;
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    switch (keyPressed->code) {
      case sf::Keyboard::Key::Up:
        moveHero(0, -1, game);
        break;
      case sf::Keyboard::Key::Down:
        moveHero(0, 1, game);
        break;
      case sf::Keyboard::Key::Left:
        moveHero(-1, 0, game);
        break;
      case sf::Keyboard::Key::Right:
        moveHero(1, 0, game);
        break;
      case sf::Keyboard::Key::W:
        moveHero(0, -1, game);
        break;
      case sf::Keyboard::Key::S:
        moveHero(0, 1, game);
        break;
      case sf::Keyboard::Key::A:
        moveHero(-1, 0, game);
        break;
      case sf::Keyboard::Key::D:
        moveHero(1, 0, game);
        break;
      case sf::Keyboard::Key::Q:
        hero_.useHealthPotion();
        addMessage("used potion");
        break;
      default:
        break;
    }
  }
}

void ExploringState::moveHero(int dx, int dy, Game& game) {
  if (dx != 0 || dy != 0) lastMoveDirection_ = sf::Vector2i(dx, dy);
  sf::Vector2i newPos = hero_.getPosition() + sf::Vector2i(dx, dy);
  if (!map_.isWalkable(newPos.x, newPos.y)) return;
  Entity* target = nullptr;
  for (auto& e : entities_)
    if (e->getPosition() == newPos) {
      target = e.get();
      break;
    }
  if (target) {
    if (auto* monster = dynamic_cast<Monster*>(target)) {
      generateNoise(NOISE_WALK);
      if (auto* segment = dynamic_cast<CentipedeSegment*>(target)) {
        CentipedeSegment* head = getCentipedeHead();
        if (head) {
          startCombat(game, *head, true);
          return;
        }
      }
      startCombat(game, *monster, true);
      return;
    } else if (auto* chest = dynamic_cast<Chest*>(target)) {
      chest->interact(hero_);
      generateNoise(NOISE_CHEST);
      addMessage("opened chest!");
      removeEntity(chest);
    }
  }
  hero_.setPosition(newPos);
  map_.updateExploredAround(hero_.getPosition(), VIEW_RADIUS);
  generateNoise(NOISE_WALK);
  updateMonsters(game);
  checkExit(game);
}

void ExploringState::updateMonsters(Game& game) {
  // обычные монстры (личинки)
  for (auto& entity : entities_) {
    if (auto* monster = dynamic_cast<Monster*>(entity.get())) {
      if (dynamic_cast<CentipedeSegment*>(monster)) continue;
      monster->update(currentDt_, map_, entities_);
      if (monster->getPosition() == hero_.getPosition()) {
        startCombat(game, *monster, false);
        return;
      }
    }
  }

  CentipedeSegment* head = getCentipedeHead();
  if (!head) return;

  sf::Vector2i oldHeadPos = head->getPosition();
  head->update(currentDt_, map_, entities_);
  if (head->getPosition() == hero_.getPosition()) {
    startCombat(game, *head, false);
    return;
  }

  CentipedeSegment* current = head->getNextSegment();
  sf::Vector2i previousPos = oldHeadPos;
  while (current) {
    sf::Vector2i oldPos = current->getPosition();
    current->setPosition(previousPos);
    if (current->getPosition() == hero_.getPosition()) {
      startCombat(game, *current, false);
      return;
    }
    previousPos = oldPos;
    current = current->getNextSegment();
  }
}

void ExploringState::generateNoise(int intensity) {
  SoundEvent sound(hero_.getPosition(), intensity, 10.0f);
  for (auto& entity : entities_) {
    if (auto* monster = dynamic_cast<Monster*>(entity.get())) {
      int dist = std::abs(sound.position.x - monster->getPosition().x) +
                 std::abs(sound.position.y - monster->getPosition().y);
      if (dist <= monster->getHearingRadius()) monster->hearSound(sound);
    }
  }
}

void ExploringState::removeEntity(Entity* entity) {
  auto it = std::find_if(entities_.begin(), entities_.end(),
                         [entity](const std::unique_ptr<Entity>& ptr) {
                           return ptr.get() == entity;
                         });
  if (it != entities_.end()) entities_.erase(it);
}

void ExploringState::addMessage(const std::string& msg) {
  currentMessage_ = msg;
  messageTimer_ = 2.0f;
}

void ExploringState::update(float deltaTime) {
  currentDt_ = deltaTime;
  if (!hero_.isAlive()) {
    game_.changeState(std::make_unique<GameOverState>(false));
    return;
  }
  updateCamera();
  if (messageTimer_ > 0) {
    messageTimer_ -= deltaTime;
    if (messageTimer_ <= 0) currentMessage_.clear();
  }
}

void ExploringState::draw(sf::RenderWindow& window) {
  window.setView(camera_);
  auto& res = ResourceManager::getInstance();
  map_.draw(window, res.getTexture("wall"), res.getTexture("floor1"),
            res.getTexture("floor2"), res.getTexture("floor3"));
  hero_.draw(window);
  for (auto& e : entities_) {
    sf::Vector2i pos = e->getPosition();
    if (map_.isExplored(pos.x, pos.y)) {
      e->draw(window);
      if (auto* monster = dynamic_cast<Monster*>(e.get()))
        monster->drawAlert(window);
    }
  }

  // ui view (экранные координаты)
  sf::View uiView(sf::FloatRect(
      sf::Vector2f(0.f, 0.f), sf::Vector2f(static_cast<float>(WINDOW_WIDTH),
                                           static_cast<float>(WINDOW_HEIGHT))));
  window.setView(uiView);
  ui_.draw(window, hero_, currentMessage_);
  drawRadar(window);
}

void ExploringState::updateCamera() {
  sf::Vector2f heroPos(
      static_cast<float>(hero_.getPosition().x * CELL_SIZE + CELL_SIZE / 2),
      static_cast<float>(hero_.getPosition().y * CELL_SIZE + CELL_SIZE / 2));
  camera_.setCenter(heroPos);

  // ограничение камеры границами карты
  float left = 0.f;
  float top = 0.f;
  float right = static_cast<float>(MAP_WIDTH * CELL_SIZE);
  float bottom = static_cast<float>(MAP_HEIGHT * CELL_SIZE);
  float halfW = camera_.getSize().x / 2.f;
  float halfH = camera_.getSize().y / 2.f;
  sf::Vector2f center = camera_.getCenter();
  if (center.x - halfW < left) center.x = left + halfW;
  if (center.y - halfH < top) center.y = top + halfH;
  if (center.x + halfW > right) center.x = right - halfW;
  if (center.y + halfH > bottom) center.y = bottom - halfH;
  camera_.setCenter(center);
}

void ExploringState::drawRadar(sf::RenderWindow& window) {
  radarBlips_.clear();
  sf::Vector2i heroPos = hero_.getPosition();
  for (auto& e : entities_) {
    Monster* monster = dynamic_cast<Monster*>(e.get());
    if (!monster) continue;
    sf::Vector2i delta = monster->getPosition() - heroPos;
    float len =
        std::sqrt(static_cast<float>(delta.x * delta.x + delta.y * delta.y));
    if (len < 0.01f) continue;
    sf::Vector2i dir(static_cast<int>(delta.x / len),
                     static_cast<int>(delta.y / len));
    sf::Color color = (dynamic_cast<CentipedeSegment*>(monster))
                          ? sf::Color::Yellow
                          : sf::Color::Green;
    radarBlips_.push_back({dir, color});
  }
  sf::RectangleShape radarBg(sf::Vector2f(static_cast<float>(RADAR_SIZE),
                                          static_cast<float>(RADAR_SIZE)));
  radarBg.setFillColor(sf::Color(0, 0, 0, 180));
  radarBg.setOutlineColor(sf::Color::White);
  radarBg.setOutlineThickness(2);
  radarBg.setPosition(sf::Vector2f(static_cast<float>(RADAR_POS_X),
                                   static_cast<float>(RADAR_POS_Y)));
  window.draw(radarBg);
  sf::CircleShape center(4);
  center.setFillColor(sf::Color::Cyan);
  center.setPosition(
      sf::Vector2f(static_cast<float>(RADAR_POS_X + RADAR_SIZE / 2 - 4),
                   static_cast<float>(RADAR_POS_Y + RADAR_SIZE / 2 - 4)));
  window.draw(center);
  for (auto& blip : radarBlips_) {
    sf::CircleShape dot(3);
    dot.setFillColor(blip.color);
    float x = static_cast<float>(RADAR_POS_X + RADAR_SIZE / 2 +
                                 blip.direction.x * (RADAR_SIZE / 2 - 10));
    float y = static_cast<float>(RADAR_POS_Y + RADAR_SIZE / 2 +
                                 blip.direction.y * (RADAR_SIZE / 2 - 10));
    dot.setPosition(sf::Vector2f(x - 3, y - 3));
    window.draw(dot);
  }
}

bool ExploringState::isOccupied(sf::Vector2i pos) {
  for (auto& e : entities_)
    if (e->getPosition() == pos) return true;
  return false;
}

void ExploringState::startCombat(Game& game, Monster& monster,
                                 bool heroAttacksFirst) {
  game.changeState(
      std::make_unique<CombatState>(game, *this, monster, heroAttacksFirst));
}

void ExploringState::checkExit(Game& game) {
  for (auto& e : entities_) {
    if (auto* exitEntity = dynamic_cast<Exit*>(e.get())) {
      if (hero_.getPosition() == exitEntity->getPosition()) {
        game.changeState(std::make_unique<GameOverState>(true));
        return;
      }
    }
  }
}
