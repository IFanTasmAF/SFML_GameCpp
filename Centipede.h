#pragma once
#include <vector>

#include "Monster.h"

class CentipedeSegment : public Monster {
 public:
  enum class SegmentType { Head, Body, Tail };
  CentipedeSegment(sf::Vector2i pos, SegmentType type, bool isHead);
  void onDeath(Map& map,
               std::vector<std::unique_ptr<Entity>>& entities) override;
  int getHearingRadius() const override { return 8; }
  void update(float deltaTime, const Map& map,
              const std::vector<std::unique_ptr<Entity>>& entities) override;
  void drawAlert(sf::RenderWindow& window) override;
  void setNextSegment(CentipedeSegment* next) { nextSegment = next; }
  void setPrevSegment(CentipedeSegment* prev) { prevSegment = prev; }
  void setTargetPos(const sf::Vector2i& pos) { targetPos = pos; }
  bool isHead() const { return isHeadSegment; }
  CentipedeSegment* getNextSegment() const { return nextSegment; }

 private:
  bool isHeadSegment;
  SegmentType type;
  CentipedeSegment* nextSegment;
  CentipedeSegment* prevSegment;
  sf::Vector2i targetPos;
  sf::Vector2i previousPos;
};
