#pragma once
#include "../entities/Entity.h"

class CombatSystem {
 public:
  static void fight(Entity& a, Entity& b) {
    while (a.isAlive() && b.isAlive()) {
      b.takeDamage(10);
      if (b.isAlive()) {
        a.takeDamage(5);
      }
    }
  }
};
