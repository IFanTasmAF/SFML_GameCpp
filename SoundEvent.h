#pragma once
#include <SFML/System/Vector2.hpp>

struct SoundEvent {
  sf::Vector2i position;
  int intensity;
  float radius;
  SoundEvent(sf::Vector2i pos, int inten, float rad)
      : position(pos), intensity(inten), radius(rad) {}
};
