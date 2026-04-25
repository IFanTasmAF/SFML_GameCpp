#include "Hero.h"

#include <algorithm>

#include "Constants.h"

Hero::Hero(sf::Vector2i startPos, const sf::Texture& texture)
    : Entity(startPos, texture),
      hp(HERO_MAX_HP),
      maxHp(HERO_MAX_HP),
      damage(HERO_BASE_DAMAGE),
      potionCount(HERO_START_POTIONS) {}

void Hero::takeDamage(int damage) { hp = std::max(0, hp - damage); }
void Hero::heal(int amount) { hp = std::min(maxHp, hp + amount); }
void Hero::useHealthPotion() {
  if (potionCount > 0 && hp < maxHp) {
    potionCount--;
    heal(POTION_HEAL_AMOUNT);
  }
}
void Hero::addPotion(int count) { potionCount += count; }
