#include "wall.h"

WallResize::WallResize(Wall *wall, Position pos) : QGraphicsRectItem() {
  switch (pos) {
  case TOP:
    this->setRect(0, 0, wall->rect().width(), WALL_RESIZE_SIZE);
    this->setCursor(Qt::SizeVerCursor);
    break;
  case BOTTOM:
    this->setRect(0, wall->rect().height() - WALL_RESIZE_SIZE,
                  wall->rect().width(), WALL_RESIZE_SIZE);
    this->setCursor(Qt::SizeVerCursor);
    break;
  case LEFT:
    this->setRect(0, 0, WALL_RESIZE_SIZE, wall->rect().height());
    this->setCursor(Qt::SizeHorCursor);
    break;
  case RIGHT:
    this->setRect(wall->rect().width() - WALL_RESIZE_SIZE, 0, WALL_RESIZE_SIZE,
                  wall->rect().height());
    this->setCursor(Qt::SizeHorCursor);
    break;
  }
  this->setFlag(QGraphicsItem::ItemIsMovable);
  this->setZValue(10);

  MyItem *item = wall;
  this->setParentItem(item);
}

Wall::Wall(int x, int y, int width, int height, QGraphicsItem *parent)
    : MyItem(x, y, parent), QGraphicsRectItem(0, 0, width, height),
      topResize(new WallResize(this, TOP)),
      bottomResize(new WallResize(this, BOTTOM)),
      leftResize(new WallResize(this, LEFT)),
      rightResize(new WallResize(this, RIGHT)) {
  setRect(0, 0, width, height);
}

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
