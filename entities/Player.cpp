#include "Player.h"

#include <cmath>

Player::Player(float x, float y) : Entity(x, y) {
  shape.setSize(sf::Vector2f(50.f, 50.f));
  shape.setFillColor(sf::Color::Green);
}

void Player::update(float dt) {
  sf::Vector2f input(0.f, 0.f);

  // ввод
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) input.y -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) input.y += 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) input.x -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) input.x += 1.f;

  // нормализация (чтобы диагональ не была быстрее)
  if (input.x != 0.f || input.y != 0.f) {
    float length = std::sqrt(input.x * input.x + input.y * input.y);
    input /= length;

    velocity += input * acceleration * dt;
  } else {
    // трение (замедление)
    if (velocity.x > 0.f)
      velocity.x = std::max(0.f, velocity.x - friction * dt);
    else if (velocity.x < 0.f)
      velocity.x = std::min(0.f, velocity.x + friction * dt);

    if (velocity.y > 0.f)
      velocity.y = std::max(0.f, velocity.y - friction * dt);
    else if (velocity.y < 0.f)
      velocity.y = std::min(0.f, velocity.y + friction * dt);
  }

  // ограничение скорости
  float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
  if (speed > maxSpeed) {
    velocity = (velocity / speed) * maxSpeed;
  }

  // движение
  shape.move(velocity * dt);
}

void Player::draw(sf::RenderWindow& window) { window.draw(shape); }
