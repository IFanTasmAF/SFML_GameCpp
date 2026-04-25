#include "Monster.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <random>

#include "Constants.h"
#include "Hero.h"
#include "Map.h"
#include "ResourceManager.h"

Monster::Monster(sf::Vector2i pos, const sf::Texture& texture, int hp,
                 int damage)
    : Entity(pos, texture),
      hp_(hp),
      maxHp_(hp),
      damage_(damage),
      mode_(MonsterMode::Wandering),
      targetSoundPos_(pos),
      alertTimer_(0.f) {}

void Monster::hearSound(const SoundEvent& sound) {
  int dist = std::abs(sound.position.x - position_.x) +
             std::abs(sound.position.y - position_.y);
  if (dist <= sound.radius && sound.intensity >= 1) {
    if (mode_ != MonsterMode::Hunting) {
      mode_ = MonsterMode::Hunting;
      alertTimer_ = 0.8f;
    }
    targetSoundPos_ = sound.position;
  }
}

void Monster::takeDamage(int damage) { hp_ = std::max(0, hp_ - damage); }

void Monster::update(float deltaTime, const Map& map,
                     const std::vector<std::unique_ptr<Entity>>& entities) {
  if (alertTimer_ > 0.f) alertTimer_ -= deltaTime;

  if (mode_ == MonsterMode::Hunting) {
    int dx = targetSoundPos_.x - position_.x;
    int dy = targetSoundPos_.y - position_.y;
    if (dx == 0 && dy == 0) {
      mode_ = MonsterMode::Wandering;
      return;
    }
    int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;
    if (stepX != 0 && stepY != 0) {
      if (rand() % 2 == 0)
        stepY = 0;
      else
        stepX = 0;
    }
    sf::Vector2i newPos(position_.x + stepX, position_.y + stepY);
    if (map.isWalkable(newPos.x, newPos.y) && !isOccupied(newPos, entities)) {
      setPosition(newPos);
    } else {
      mode_ = MonsterMode::Wandering;
      alertTimer_ = 0.f;
    }
  } else {
    std::vector<sf::Vector2i> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {0, 0}};
    std::shuffle(dirs.begin(), dirs.end(),
                 std::mt19937{std::random_device{}()});
    for (auto& dir : dirs) {
      sf::Vector2i newPos(position_.x + dir.x, position_.y + dir.y);
      if (map.isWalkable(newPos.x, newPos.y) && !isOccupied(newPos, entities)) {
        setPosition(newPos);
        break;
      }
    }
  }
}

void Monster::interact(Hero& hero, bool heroAttacksFirst) {
  if (!heroAttacksFirst) hero.takeDamage(damage_);
}

bool Monster::isOccupied(
    sf::Vector2i pos,
    const std::vector<std::unique_ptr<Entity>>& entities) const {
  for (auto& e : entities)
    if (e.get() != this && e->getPosition() == pos) return true;
  return false;
}

void Monster::drawAlert(sf::RenderWindow& window) {
  // Ѕазовый класс не рисует ничего, переопредел€етс€ в CentipedeSegment
}
