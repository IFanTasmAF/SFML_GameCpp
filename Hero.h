#pragma once
#include "Entity.h"

class Hero : public Entity {
 public:
  Hero(sf::Vector2i startPos, const sf::Texture& texture);
  void interact(Hero&) override {}
  void takeDamage(int damage);
  void heal(int amount);
  void useHealthPotion();
  void addPotion(int count = 1);
  int getHp() const { return hp; }
  int getMaxHp() const { return maxHp; }
  int getDamage() const { return damage; }
  int getPotionCount() const { return potionCount; }
  bool isAlive() const { return hp > 0; }

 private:
  int hp, maxHp;
  int damage;
  int potionCount;
};
