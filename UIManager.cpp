#include "UIManager.h"

#include <sstream>

#include "Constants.h"
#include "Hero.h"

UIManager::UIManager(sf::Font& font)
    : font(font),
      healthText(font, "", 20),
      potionText(font, "", 20),
      messageText(font, "", 16) {
  healthText.setFillColor(COLOR_TEXT);
  potionText.setFillColor(COLOR_TEXT);
  messageText.setFillColor(sf::Color::Yellow);

  float rightX = static_cast<float>(WINDOW_WIDTH - 20);
  healthText.setPosition(sf::Vector2f(rightX - 150, 10));
  potionText.setPosition(sf::Vector2f(rightX - 150, 50));
  messageText.setPosition(sf::Vector2f(rightX - 150, 90));
}

void UIManager::draw(sf::RenderWindow& window, const Hero& hero,
                     const std::string& message) {
  std::stringstream ss;
  ss << "hp: " << hero.getHp() << "/" << hero.getMaxHp();
  healthText.setString(ss.str());
  window.draw(healthText);

  ss.str("");
  ss << "potions: " << hero.getPotionCount();
  potionText.setString(ss.str());
  window.draw(potionText);

  messageText.setString(message);
  window.draw(messageText);
}
