#include "wall.h"

WallResize::WallResize(Wall *wall, Position pos) : QGraphicsRectItem() {
  switch (pos) {
  case TOP:
    this->setRect(wall->rect().left(), wall->rect().top(), wall->rect().width(),
                  WALL_RESIZE_SIZE);
    this->setCursor(Qt::SizeVerCursor);
    break;
  case BOTTOM:
    this->setRect(wall->rect().left(), wall->rect().bottom() - WALL_RESIZE_SIZE,
                  wall->rect().width(), WALL_RESIZE_SIZE);
    this->setCursor(Qt::SizeVerCursor);
    break;
  case LEFT:
    this->setRect(wall->rect().left(), wall->rect().top(), WALL_RESIZE_SIZE,
                  wall->rect().height());
    this->setCursor(Qt::SizeHorCursor);
    break;
  case RIGHT:
    this->setRect(wall->rect().right() - WALL_RESIZE_SIZE, wall->rect().top(),
                  WALL_RESIZE_SIZE, wall->rect().height());
    this->setCursor(Qt::SizeHorCursor);
    break;
  }
  this->setFlag(QGraphicsItem::ItemIsMovable);
  this->setZValue(4);

  MyItem *item = wall;
  this->setParentItem(item);
}

Wall::Wall(int x, int y, int width, int height, QGraphicsItem *parent)
    : MyItem(parent), QGraphicsRectItem(x, y, width, height),
      topResize(new WallResize(this, TOP)),
      bottomResize(new WallResize(this, BOTTOM)),
      leftResize(new WallResize(this, LEFT)),
      rightResize(new WallResize(this, RIGHT)) {}

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
