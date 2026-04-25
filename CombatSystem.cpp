#include "CombatSystem.h"

#include "Hero.h"
#include "Map.h"
#include "Monster.h"

bool CombatSystem::fight(Hero& hero, Monster& monster, Map* map,
                         std::vector<std::unique_ptr<Entity>>* entities) {
  while (hero.isAlive() && monster.isAlive()) {
    int heroDamage = hero.getDamage();
    monster.takeDamage(heroDamage);
    if (!monster.isAlive()) {
      monster.onDeath(*map, *entities);
      return true;
    }
    hero.takeDamage(monster.getDamage());
  }
  return hero.isAlive();
}
