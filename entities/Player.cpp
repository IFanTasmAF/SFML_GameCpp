#include "Player.h"

Player::Player(float x, float y) : Entity(x, y) {
  shape.setSize({50.f, 50.f});
  shape.setFillColor(sf::Color::Green);
}

void Player::update(float dt) {
  sf::Vector2f movement(0.f, 0.f);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += speed;

  shape.move(movement * dt);  // ПЛАВНОЕ движение
}
