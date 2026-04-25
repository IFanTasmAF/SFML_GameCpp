#include "Larva.h"

#include "Hero.h"
#include "Map.h"

Larva::Larva(sf::Vector2i pos, const sf::Texture& texture)
    : Monster(pos, texture, 15, 5) {}

void Larva::onDeath(Map&, std::vector<std::unique_ptr<Entity>>&) {}

void Larva::update(float deltaTime, const Map& map,
                   const std::vector<std::unique_ptr<Entity>>& entities) {
  mode = MonsterMode::Wandering;
  Monster::update(deltaTime, map, entities);
}
