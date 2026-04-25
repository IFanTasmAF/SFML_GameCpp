#pragma once
#include "Constants.h"
#include "Monster.h"

class Larva : public Monster {
 public:
  Larva(sf::Vector2i pos, const sf::Texture& texture);
  void onDeath(Map& map,
               std::vector<std::unique_ptr<Entity>>& entities) override;
  int getHearingRadius() const override { return 0; }  // не слышит
  void update(float deltaTime, const Map& map,
              const std::vector<std::unique_ptr<Entity>>& entities) override;
};
