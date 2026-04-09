#include "Player.h"

Player::Player(float x, float y) : Entity(x, y) {
  shape.setSize(sf::Vector2f(50.f, 50.f));
  shape.setFillColor(sf::Color::Green);
}

void Player::update(float dt) {
  float speed = 200.f;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) shape.move(0, -speed * dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) shape.move(0, speed * dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) shape.move(-speed * dt, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) shape.move(speed * dt, 0);
}

void Player::draw(sf::RenderWindow& window) { window.draw(shape); }
