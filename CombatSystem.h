#pragma once
#include <memory>
#include <vector>

class Hero;
class Monster;
class Map;
class Entity;

class CombatSystem {
 public:
  static bool fight(Hero& hero, Monster& monster, Map* map,
                    std::vector<std::unique_ptr<Entity>>* entities);
};
