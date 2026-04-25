#include "Chest.h"

#include "Constants.h"
#include "Hero.h"

Chest::Chest(sf::Vector2i pos, const sf::Texture& texture, LootType loot)
    : Entity(pos, texture), loot_(loot) {}

void Chest::interact(Hero& hero) {
  switch (loot_) {
    case LootType::HealthPotion:
      hero.addPotion(1);
      break;
    case LootType::InstantHeal:
      hero.heal(15);
      break;
    case LootType::Trap:
      hero.takeDamage(10);
      break;
  }
}
