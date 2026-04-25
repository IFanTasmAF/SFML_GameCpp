#include "Exit.h"

#include "Game.h"
#include "Hero.h"

Exit::Exit(sf::Vector2i pos, const sf::Texture& texture)
    : Entity(pos, texture) {}

void Exit::interact(Hero& hero) {
  // ничего не делает, победа наступает при касании
}
