#pragma once
#include <SFML/Graphics.hpp>

class Entity {
 protected:
  sf::RectangleShape shape;

 public:
  Entity(float x, float y) {
    shape.setSize({20.f, 20.f});
    shape.setPosition({x, y});
  }

  virtual ~Entity() = default;

  virtual void update(float dt) {}

  void draw(sf::RenderWindow& window) { window.draw(shape); }

  void move(const sf::Vector2f& offset) { shape.move(offset); }

  void setPosition(const sf::Vector2f& pos) { shape.setPosition(pos); }

  sf::Vector2f getPosition() const { return shape.getPosition(); }

  sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
};
