#pragma once
#include <SFML/Graphics/Color.hpp>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int MAP_WIDTH = 60;
const int MAP_HEIGHT = 40;
const int CELL_SIZE = 32;

const int VIEW_RADIUS = 12;
const int RADAR_SIZE = 100;
const int RADAR_POS_X = 10;
const int RADAR_POS_Y = WINDOW_HEIGHT - RADAR_SIZE - 10;

const sf::Color COLOR_WALL = sf::Color(80, 80, 80);
const sf::Color COLOR_FLOOR = sf::Color(40, 40, 40);
const sf::Color COLOR_HERO = sf::Color(0, 200, 255);
const sf::Color COLOR_CHEST = sf::Color(255, 215, 0);
const sf::Color COLOR_TEXT = sf::Color::White;
const sf::Color COLOR_HORROR = sf::Color(150, 0, 150);
const sf::Color COLOR_STICKY = sf::Color(0, 150, 0);

const int HERO_MAX_HP = 30;
const int HERO_BASE_DAMAGE = 10;
const int HERO_START_POTIONS = 1;

const int CENTIPEDE_SEGMENT_HP = 20;
const int CENTIPEDE_DAMAGE = 15;
const int CENTIPEDE_LENGTH = 5;

const int NOISE_WALK = 2;
const int NOISE_CHEST = 5;
const int POTION_HEAL_AMOUNT = 20;
