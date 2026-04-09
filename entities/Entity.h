#pragma once
#include <SFML/Graphics.hpp>

class Map;
class Player;

class Entity {
 protected:
  int x;
  int y;
  int hp;
  int damage;
  sf::RectangleShape shape;

 public:
  Entity(int x, int y, int hp, int damage)
      : x(x), y(y), hp(hp), damage(damage) {}

  virtual ~Entity() = default;

  virtual void draw(sf::RenderWindow& window) = 0;

  virtual void update(float dt) = 0;

  void takeDamage(int dmg) { hp -= dmg; }

  void attack(Entity& target) { target.takeDamage(damage); }

  bool isAlive() const { return hp > 0; }

  int getX() const { return x; }
  int getY() const { return y; }
};
