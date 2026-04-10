#include "Player.h"

#include <SFML/Window/Keyboard.hpp>
#include <cmath>

Player::Player() : Entity(100.f, 100.f), speed(200.f), hp(100) {}

sf::Vector2f Player::getVelocity() const {
  sf::Vector2f movement(0.f, 0.f);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;

  if (movement.x != 0 || movement.y != 0) {
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    movement /= length;
  }

  return movement * speed;
}

void Player::update(float dt) {
  // теперь пусто или можно оставить
}
