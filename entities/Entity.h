#pragma once
#include <SFML/Graphics.hpp>

class Entity {
 protected:
  sf::RectangleShape shape;

 public:
  Entity(float x, float y) { shape.setPosition({x, y}); }

  virtual ~Entity() = default;

  virtual void update(float dt) = 0;

  virtual void draw(sf::RenderWindow& window) { window.draw(shape); }

  sf::Vector2f getPosition() const { return shape.getPosition(); }
};
