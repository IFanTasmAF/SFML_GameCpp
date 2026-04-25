#pragma once
#include "Entity.h"

enum class LootType { HealthPotion, InstantHeal, Trap };

class Chest : public Entity {
 public:
  Chest(sf::Vector2i pos, const sf::Texture& texture, LootType loot);
  void interact(Hero& hero) override;

 private:
  LootType loot_;
};
