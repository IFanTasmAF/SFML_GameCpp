#include "UIManager.h"

#include <sstream>

#include "Constants.h"
#include "Hero.h"

UIManager::UIManager(sf::Font& font)
    : font_(font),
      healthText_(font, "", 20),
      potionText_(font, "", 20),
      messageText_(font, "", 16) {
  healthText_.setFillColor(COLOR_TEXT);
  potionText_.setFillColor(COLOR_TEXT);
  messageText_.setFillColor(sf::Color::Yellow);

  // Позиция – на правом краю окна (отступ 20)
  float rightX = static_cast<float>(WINDOW_WIDTH - 20);
  healthText_.setPosition(sf::Vector2f(rightX - 150, 10));
  potionText_.setPosition(sf::Vector2f(rightX - 150, 50));
  messageText_.setPosition(sf::Vector2f(rightX - 150, 90));
}

void UIManager::draw(sf::RenderWindow& window, const Hero& hero,
                     const std::string& message) {
  std::stringstream ss;
  ss << "HP: " << hero.getHp() << "/" << hero.getMaxHp();
  healthText_.setString(ss.str());
  window.draw(healthText_);

  ss.str("");
  ss << "Potions: " << hero.getPotionCount();
  potionText_.setString(ss.str());
  window.draw(potionText_);

  messageText_.setString(message);
  window.draw(messageText_);
}
