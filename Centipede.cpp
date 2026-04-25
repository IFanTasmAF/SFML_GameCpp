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
      isHead_(isHead),
      type_(type),
      nextSegment_(nullptr),
      prevSegment_(nullptr),
      targetPos_(pos),
      previousPos_(pos) {}

void CentipedeSegment::onDeath(Map&, std::vector<std::unique_ptr<Entity>>&) {
  if (!isHead_) {
    if (prevSegment_) prevSegment_->setNextSegment(nextSegment_);
    if (nextSegment_) nextSegment_->setPrevSegment(prevSegment_);
  }
}

void CentipedeSegment::update(
    float deltaTime, const Map& map,
    const std::vector<std::unique_ptr<Entity>>& entities) {
  if (isHead_) {
    Monster::update(deltaTime, map, entities);
    if (nextSegment_) {
      nextSegment_->setTargetPos(position_);
    }
  } else {
    if (prevSegment_) {
      setPosition(prevSegment_->getPosition());
    }
  }
}

void CentipedeSegment::drawAlert(sf::RenderWindow& window) {
  if (isHead_ && alertTimer_ > 0.f) {
    sf::Text exclamation(ResourceManager::getInstance().getFont(), "!", 24);
    exclamation.setFillColor(sf::Color::Red);
    exclamation.setStyle(sf::Text::Bold);
    exclamation.setPosition(
        sf::Vector2f(sprite_.getPosition().x + CELL_SIZE / 2 - 8,
                     sprite_.getPosition().y - 20));
    window.draw(exclamation);
  }
}
