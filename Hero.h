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
  int getHp() const { return hp_; }
  int getMaxHp() const { return maxHp_; }
  int getDamage() const { return damage_; }
  int getPotionCount() const { return potionCount_; }
  bool isAlive() const { return hp_ > 0; }

 private:
  int hp_, maxHp_;
  int damage_;
  int potionCount_;
};
