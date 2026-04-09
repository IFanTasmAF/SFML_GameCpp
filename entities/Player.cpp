#include "Player.h"

Player::Player(float x, float y) : Entity(x, y) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setFillColor(sf::Color::Green);
}

void Player::update(float dt) {
    // пока пусто
}

void Player::move(float dx, float dy, Map& map) { shape.move({dx, dy}); }

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

int Player::getHp() const { return hp; }
