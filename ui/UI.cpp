#include "UI.h"

void UI::draw(Player& player, sf::RenderWindow& window) {
  float max_hp = 100.0f;
  float hp = static_cast<float>(player.getHp());

  float percent = hp / max_hp;

  sf::RectangleShape bg({200.f, 20.f});
  bg.setPosition({10.f, 10.f});
  bg.setFillColor(sf::Color(100, 100, 100));

  sf::RectangleShape bar({200.f * percent, 20.f});
  bar.setPosition({10.f, 10.f});

  sf::Color color;
  if (percent > 0.6f)
    color = sf::Color::Green;
  else if (percent > 0.3f)
    color = sf::Color::Yellow;
  else
    color = sf::Color::Red;

  bar.setFillColor(color);

  window.draw(bg);
  window.draw(bar);
}
