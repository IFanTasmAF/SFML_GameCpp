#include "StickyMonster.h"

#include "Hero.h"
#include "Map.h"

StickyMonster::StickyMonster(sf::Vector2i pos, const sf::Texture& texture)
    : Monster(pos, texture, STICKY_HP, STICKY_DAMAGE) {}

void StickyMonster::onDeath(Map&, std::vector<std::unique_ptr<Entity>>&) {}

void StickyMonster::hearSound(const SoundEvent& sound) {
  if (sound.intensity >= 3) Monster::hearSound(sound);
}
