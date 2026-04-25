#include "Centipede.h"

#include "Constants.h"
#include "Hero.h"
#include "Map.h"
#include "ResourceManager.h"

CentipedeSegment::CentipedeSegment(sf::Vector2i pos, SegmentType type,
                                   bool isHead)
    : Monster(pos,
              ResourceManager::getInstance().getTexture(
                  (type == SegmentType::Head)
                      ? "head"
                      : ((type == SegmentType::Tail) ? "tail" : "body")),
              CENTIPEDE_SEGMENT_HP, CENTIPEDE_DAMAGE),
      isHeadSegment(isHead),
      type(type),
      nextSegment(nullptr),
      prevSegment(nullptr),
      targetPos(pos),
      previousPos(pos) {}

void CentipedeSegment::onDeath(Map&, std::vector<std::unique_ptr<Entity>>&) {
  if (!isHeadSegment) {
    if (prevSegment) prevSegment->setNextSegment(nextSegment);
    if (nextSegment) nextSegment->setPrevSegment(prevSegment);
  }
}

void CentipedeSegment::update(
    float deltaTime, const Map& map,
    const std::vector<std::unique_ptr<Entity>>& entities) {
  if (isHeadSegment) {
    Monster::update(deltaTime, map, entities);
    if (nextSegment) {
      nextSegment->setTargetPos(position);
    }
  } else {
    if (prevSegment) {
      setPosition(prevSegment->getPosition());
    }
  }
}

void CentipedeSegment::drawAlert(sf::RenderWindow& window) {
  if (isHeadSegment && alertTimer > 0.f) {
    sf::Text exclamation(ResourceManager::getInstance().getFont(), "!", 24);
    exclamation.setFillColor(sf::Color::Red);
    exclamation.setStyle(sf::Text::Bold);
    exclamation.setPosition(
        sf::Vector2f(sprite.getPosition().x + CELL_SIZE / 2 - 8,
                     sprite.getPosition().y - 20));
    window.draw(exclamation);
  }
}
