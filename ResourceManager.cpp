#include "ResourceManager.h"

#include <iostream>

#include "Constants.h"

ResourceManager::ResourceManager() {
  // ¬спомогательна€ функци€ Ц создаЄт текстуру из одного цвета
  auto makeTexture = [](const sf::Color& color) -> sf::Texture {
    sf::Image image({static_cast<unsigned int>(CELL_SIZE),
                     static_cast<unsigned int>(CELL_SIZE)},
                    color);
    sf::Texture texture;
    texture.loadFromImage(image);  // игнорируем возможную ошибку Ц цветна€
                                   // текстура всегда создаЄтс€
    return texture;
  };

  // ”ниверсальна€ загрузка текстуры из файла или создание цветной заглушки
  auto loadTex = [&](const std::string& key, const std::string& path) {
    sf::Texture tex;
    if (tex.loadFromFile(path)) {
      textures_[key] = tex;
      std::cout << "Loaded: " << path << std::endl;
    } else {
      // ÷вета дл€ заглушек
      sf::Color color = sf::Color::Magenta;
      if (key == "hero")
        color = COLOR_HERO;
      else if (key == "head")
        color = COLOR_HORROR;
      else if (key == "body")
        color = sf::Color(200, 100, 200);
      else if (key == "tail")
        color = sf::Color(180, 80, 180);
      else if (key == "larva")
        color = COLOR_STICKY;
      else if (key == "wall")
        color = COLOR_WALL;
      else if (key.find("floor") == 0)
        color = sf::Color(100, 100, 100);
      else if (key == "chest")
        color = COLOR_CHEST;
      else if (key == "exit")
        color = sf::Color(0, 255, 0);
      textures_[key] = makeTexture(color);
      std::cerr << "Warning: Could not load " << path << ", using fallback."
                << std::endl;
    }
  };

  // «агрузка всех необходимых текстур
  loadTex("hero", "textures/hero.png");
  loadTex("head", "textures/head_centipide.png");
  loadTex("body", "textures/body_centipide.png");
  loadTex("tail", "textures/tail_centipide.png");
  loadTex("larva", "textures/larva.png");
  loadTex("wall", "textures/wall.png");
  loadTex("floor1", "textures/floor_1.png");
  loadTex("floor2", "textures/floor_2.png");
  loadTex("floor3", "textures/floor_3.png");
  loadTex("chest", "textures/chest.png");
  loadTex("exit", "textures/exit.png");

  // Ўрифт (сначала системный, потом local)
  if (!font_.openFromFile("C:/Windows/Fonts/arial.ttf")) {
    if (!font_.openFromFile("arial.ttf")) {
      std::cerr << "Warning: Cannot load arial.ttf. Text will not be displayed."
                << std::endl;
    }
  }
}

ResourceManager& ResourceManager::getInstance() {
  static ResourceManager instance;  // единственный static Ц нужен дл€ синглтона
  return instance;
}

sf::Texture& ResourceManager::getTexture(const std::string& key) {
  return textures_[key];
}
sf::Font& ResourceManager::getFont() { return font_; }
