#include "CombatState.h"

#include "Centipede.h"
#include "CombatSystem.h"
#include "Constants.h"
#include "ExploringState.h"
#include "Game.h"
#include "GameOverState.h"
#include "Monster.h"
#include "ResourceManager.h"

CombatState::CombatState(Game& game, ExploringState& exploring,
                         Monster& monster, bool heroAttacksFirst)
    : hero_(exploring.getHero()),
      monster_(monster),
      exploring_(exploring),
      heroWon_(false),
      finished_(false),
      timer_(0.0f) {
  if (heroAttacksFirst) {
    heroWon_ = CombatSystem::fight(hero_, monster_, &exploring_.getMap(),
                                   &exploring_.getEntities());
  } else {
    hero_.takeDamage(monster_.getDamage());
    if (hero_.isAlive())
      heroWon_ = CombatSystem::fight(hero_, monster_, &exploring_.getMap(),
                                     &exploring_.getEntities());
    else
      heroWon_ = false;
  }

  if (heroWon_) {
    if (dynamic_cast<CentipedeSegment*>(&monster)) {
      exploring_.addMessage("You defeated the centipede!");
      auto& entities = exploring_.getEntities();
      for (auto it = entities.begin(); it != entities.end();) {
        if (dynamic_cast<CentipedeSegment*>((*it).get()))
          it = entities.erase(it);
        else
          ++it;
      }
    } else {
      exploring_.removeEntity(&monster);
      exploring_.addMessage("You crushed a larva.");
    }
  } else {
    exploring_.addMessage("You died...");
  }
  finished_ = true;
}

void CombatState::handleInput(const sf::Event& event, Game& game) {
  if (finished_ && event.is<sf::Event::KeyPressed>()) {
    if (!heroWon_) {
      game.changeState(std::make_unique<GameOverState>(false));
    } else {
      game.popState();
    }
  }
}

void CombatState::update(float deltaTime) {}

void CombatState::draw(sf::RenderWindow& window) {
  sf::Font& font = ResourceManager::getInstance().getFont();
  std::string message = finished_ ? (heroWon_ ? "Victory! Press any key"
                                              : "Game Over! Press any key")
                                  : "Fighting...";
  sf::Text text(font, message, 30);
  text.setFillColor(sf::Color::White);
  text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2));
  window.draw(text);
}
