#pragma once
#include <memory>
#include <vector>

#include "Entity.h"
#include "SoundEvent.h"

class Map;

enum class MonsterMode { Wandering, Hunting };

class Monster : public Entity {
 public:
  Monster(sf::Vector2i pos, const sf::Texture& texture, int hp, int damage);
  virtual ~Monster() = default;
  virtual void onDeath(Map& map,
                       std::vector<std::unique_ptr<Entity>>& entities) = 0;
  virtual int getHearingRadius() const = 0;
  virtual void hearSound(const SoundEvent& sound);
  void takeDamage(int damage);
  virtual void update(float deltaTime, const Map& map,
                      const std::vector<std::unique_ptr<Entity>>& entities);
  void interact(Hero& hero, bool heroAttacksFirst);
  void interact(Hero& hero) override {}
  void setMode(MonsterMode mode) { this->mode = mode; }
  virtual void drawAlert(sf::RenderWindow& window);
  int getHp() const { return hp; }
  int getDamage() const { return damage; }
  bool isAlive() const { return hp > 0; }

 protected:
  bool isOccupied(sf::Vector2i pos,
                  const std::vector<std::unique_ptr<Entity>>& entities) const;
  int hp, maxHp, damage;
  MonsterMode mode;
  sf::Vector2i targetSoundPos;
  float alertTimer;
};
