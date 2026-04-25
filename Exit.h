#pragma once
#include "Entity.h"

class Exit : public Entity {
 public:
  Exit(sf::Vector2i pos, const sf::Texture& texture);
  void interact(Hero& hero) override;
};
