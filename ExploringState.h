#pragma once
#include <SFML/Graphics/View.hpp>
#include <memory>
#include <vector>

#include "GameState.h"
#include "Hero.h"
#include "Map.h"
#include "Monster.h"
#include "UIManager.h"

class CentipedeSegment;

class ExploringState : public GameState {
 public:
  ExploringState(Game& game);
  void handleInput(const sf::Event& event, Game& game) override;
  void update(float deltaTime) override;
  void draw(sf::RenderWindow& window) override;
  void startCombat(Game& game, Monster& monster, bool heroAttacksFirst);
  void removeEntity(Entity* entity);
  void addMessage(const std::string& msg);
  Hero& getHero() { return hero_; }
  Map& getMap() { return map_; }
  std::vector<std::unique_ptr<Entity>>& getEntities() { return entities_; }

 private:
  void moveHero(int dx, int dy, Game& game);
  void updateMonsters(Game& game);
  void generateNoise(int intensity);
  void updateCamera();
  void drawRadar(sf::RenderWindow& window);
  void addCentipede(const sf::Vector2i& headPos, const sf::Vector2i& direction);
  bool isOccupied(sf::Vector2i pos);
  void checkExit(Game& game);
  CentipedeSegment* getCentipedeHead();

  Game& game_;
  Map map_;
  Hero hero_;
  std::vector<std::unique_ptr<Entity>> entities_;
  UIManager ui_;
  std::string currentMessage_;
  float messageTimer_;
  sf::Vector2i lastMoveDirection_;
  float currentDt_;

  sf::View camera_;
  struct RadarBlip {
    sf::Vector2i direction;
    sf::Color color;
  };
  std::vector<RadarBlip> radarBlips_;
};
