#include "sampleWall.h"

SampleWall::SampleWall(int x, int y, int size, Wall *parent)
    : Wall(x, y, size, parent) {
  MyItem::setFlag(QGraphicsItem::ItemIsMovable, false);
}

SampleWall::SampleWall(SampleWall *wall, Wall *parent)
    : SampleWall(wall->MyItem::x(), wall->MyItem::y(), wall->getSize(),
                 parent) {}
