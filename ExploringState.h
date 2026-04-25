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
  Hero& getHero() { return hero; }
  Map& getMap() { return map; }
  std::vector<std::unique_ptr<Entity>>& getEntities() { return entities; }

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

  Game& game;
  Map map;
  Hero hero;
  std::vector<std::unique_ptr<Entity>> entities;
  UIManager ui;
  std::string currentMessage;
  float messageTimer;
  sf::Vector2i lastMoveDirection;
  float currentDt;

  sf::View camera;
  struct RadarBlip {
    sf::Vector2i direction;
    sf::Color color;
  };
  std::vector<RadarBlip> radarBlips;
};
