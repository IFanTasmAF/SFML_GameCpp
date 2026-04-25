#include "Entity.h"

#include "Constants.h"

Entity::Entity(sf::Vector2i pos, const sf::Texture& texture)
    : position_(pos), sprite_(texture) {
  setPixelPosition(sf::Vector2f(pos.x * CELL_SIZE, pos.y * CELL_SIZE));
}

void Entity::draw(sf::RenderWindow& window) { window.draw(sprite_); }

void Entity::setPosition(sf::Vector2i pos) {
  position_ = pos;
  setPixelPosition(sf::Vector2f(pos.x * CELL_SIZE, pos.y * CELL_SIZE));
}

void Entity::setPixelPosition(const sf::Vector2f& pixelPos) {
  sprite_.setPosition(pixelPos);
}
