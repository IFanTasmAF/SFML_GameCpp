#pragma once
#include <SFML/Graphics.hpp>

class Hero;

class Entity {
 public:
  Entity(sf::Vector2i pos, const sf::Texture& texture);
  virtual ~Entity() = default;
  virtual void draw(sf::RenderWindow& window);
  virtual void interact(Hero& hero) = 0;
  virtual void update(float deltaTime) {}
  sf::Vector2i getPosition() const { return position_; }
  void setPosition(sf::Vector2i pos);
  void setPixelPosition(const sf::Vector2f& pixelPos);

 protected:
  sf::Vector2i position_;
  sf::Sprite sprite_;
};
