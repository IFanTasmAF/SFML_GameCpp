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
      hp(hp),
      maxHp(hp),
      damage(damage),
      mode(MonsterMode::Wandering),
      targetSoundPos(pos),
      alertTimer(0.f) {}

void Monster::hearSound(const SoundEvent& sound) {
  int dist = std::abs(sound.position.x - position.x) +
             std::abs(sound.position.y - position.y);
  if (dist <= sound.radius && sound.intensity >= 1) {
    if (mode != MonsterMode::Hunting) {
      mode = MonsterMode::Hunting;
      alertTimer = 0.8f;
    }
    targetSoundPos = sound.position;
  }
}

void Monster::takeDamage(int damage) { hp = std::max(0, hp - damage); }

void Monster::update(float deltaTime, const Map& map,
                     const std::vector<std::unique_ptr<Entity>>& entities) {
  if (alertTimer > 0.f) alertTimer -= deltaTime;

  if (mode == MonsterMode::Hunting) {
    int dx = targetSoundPos.x - position.x;
    int dy = targetSoundPos.y - position.y;
    if (dx == 0 && dy == 0) {
      mode = MonsterMode::Wandering;
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
    sf::Vector2i newPos(position.x + stepX, position.y + stepY);
    if (map.isWalkable(newPos.x, newPos.y) && !isOccupied(newPos, entities)) {
      setPosition(newPos);
    } else {
      mode = MonsterMode::Wandering;
      alertTimer = 0.f;
    }
  } else {
    std::vector<sf::Vector2i> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {0, 0}};
    std::shuffle(dirs.begin(), dirs.end(),
                 std::mt19937{std::random_device{}()});
    for (auto& dir : dirs) {
      sf::Vector2i newPos(position.x + dir.x, position.y + dir.y);
      if (map.isWalkable(newPos.x, newPos.y) && !isOccupied(newPos, entities)) {
        setPosition(newPos);
        break;
      }
    }
  }
}

void Monster::interact(Hero& hero, bool heroAttacksFirst) {
  if (!heroAttacksFirst) hero.takeDamage(damage);
}

bool Monster::isOccupied(
    sf::Vector2i pos,
    const std::vector<std::unique_ptr<Entity>>& entities) const {
  for (auto& e : entities)
    if (e.get() != this && e->getPosition() == pos) return true;
  return false;
}

void Monster::drawAlert(sf::RenderWindow& window) {
  // переопределяется в CentipedeSegment
}
