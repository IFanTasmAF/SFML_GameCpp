#include "Entity.h"

#include "Constants.h"

Entity::Entity(sf::Vector2i pos, const sf::Texture& texture)
    : position(pos), sprite(texture) {
  setPixelPosition(sf::Vector2f(pos.x * CELL_SIZE, pos.y * CELL_SIZE));
}

void Entity::draw(sf::RenderWindow& window) { window.draw(sprite); }

void Entity::setPosition(sf::Vector2i pos) {
  position = pos;
  setPixelPosition(sf::Vector2f(pos.x * CELL_SIZE, pos.y * CELL_SIZE));
}

void Entity::setPixelPosition(const sf::Vector2f& pixelPos) {
  sprite.setPosition(pixelPos);
}
