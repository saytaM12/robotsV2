#include "wall.h"

Wall::Wall(int x, int y, int size, MyItem *parent) : MyItem(x, y, parent) {
  setRect(0, 0, size, size);
  this->size = size;

}

Wall::Wall(Wall *wall, MyItem *parent)
    : Wall(wall->MyItem::x(), wall->MyItem::y(), wall->getSize(), parent) {}

bool Wall::isWall() const { return true; }

int Wall::getSize() { return this->size; }

void Wall::setSize(int size) {
  this->size = size;
  this->setRect(0, 0, size, size);
  this->MyItem::update();
}

QRectF Wall::boundingRect() const { return this->rect(); }

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *) {
  if (!this->MyItem::isSelected()) {
    painter->setBrush(Qt::white);
    painter->setPen(Qt::NoPen);
    painter->drawRect(option->rect);

  } else {
    painter->setBrush(Qt::gray);
    painter->setPen(Qt::NoPen);
    painter->drawRect(option->rect);
  }
}
