#include "Hero.h"

#include <algorithm>

#include "Constants.h"

Hero::Hero(sf::Vector2i startPos, const sf::Texture& texture)
    : Entity(startPos, texture),
      hp_(HERO_MAX_HP),
      maxHp_(HERO_MAX_HP),
      damage_(HERO_BASE_DAMAGE),
      potionCount_(HERO_START_POTIONS) {}

void Hero::takeDamage(int damage) { hp_ = std::max(0, hp_ - damage); }

void Hero::heal(int amount) { hp_ = std::min(maxHp_, hp_ + amount); }

void Hero::useHealthPotion() {
  if (potionCount_ > 0 && hp_ < maxHp_) {
    potionCount_--;
    heal(POTION_HEAL_AMOUNT);
  }
}

void Hero::addPotion(int count) { potionCount_ += count; }
