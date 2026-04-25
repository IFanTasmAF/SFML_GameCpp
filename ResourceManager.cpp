#include "ResourceManager.h"

#include <iostream>

#include "Constants.h"

ResourceManager::ResourceManager() {
  // вспомогательна€ л€мбда: создаЄт текстуру-заглушку из цвета
  auto makeFallback = [](const sf::Color& color) -> sf::Texture {
    sf::Image image({static_cast<unsigned int>(CELL_SIZE),
                     static_cast<unsigned int>(CELL_SIZE)},
                    color);
    sf::Texture texture;
    texture.loadFromImage(image);
    return texture;
  };

  // попытка загрузить текстуру из файла; если не удаЄтс€ Ц создаЄм цветную
  auto loadOrFallback = [&](const std::string& key, const std::string& path,
                            const sf::Color& fallbackColor) {
    sf::Texture tex;
    if (tex.loadFromFile(path)) {
      textures[key] = tex;
      std::cout << "loaded texture: " << path << std::endl;
    } else {
      textures[key] = makeFallback(fallbackColor);
      std::cerr << "warning: could not load " << path
                << ", using fallback color." << std::endl;
    }
  };

  // загрузка всех необходимых текстур
  loadOrFallback("hero", "textures/hero.png", sf::Color::Cyan);
  loadOrFallback("head", "textures/head_centipide.png", sf::Color::Red);
  loadOrFallback("body", "textures/body_centipide.png", sf::Color::Magenta);
  loadOrFallback("tail", "textures/tail_centipide.png", sf::Color::Yellow);
  loadOrFallback("larva", "textures/larva.png", sf::Color::Green);
  loadOrFallback("wall", "textures/wall.png", sf::Color(80, 80, 80));
  loadOrFallback("floor1", "textures/floor_1.png", sf::Color(120, 120, 120));
  loadOrFallback("floor2", "textures/floor_2.png", sf::Color(140, 140, 140));
  loadOrFallback("floor3", "textures/floor_3.png", sf::Color(160, 160, 160));
  loadOrFallback("chest", "textures/chest.png", sf::Color(255, 215, 0));
  loadOrFallback("exit", "textures/exit.png", sf::Color(0, 255, 0));

  // загрузка шрифта (сначала из системной папки, затем локально)
  if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
    if (!font.openFromFile("arial.ttf")) {
      std::cerr << "warning: cannot load arial.ttf, text will not be displayed."
                << std::endl;
    } else {
      std::cout << "loaded arial.ttf from local folder." << std::endl;
    }
  } else {
    std::cout << "loaded arial.ttf from system fonts." << std::endl;
  }
}

ResourceManager& ResourceManager::getInstance() {
  static ResourceManager instance;
  return instance;
}

sf::Texture& ResourceManager::getTexture(const std::string& key) {
  return textures[key];
}

sf::Font& ResourceManager::getFont() { return font; }
