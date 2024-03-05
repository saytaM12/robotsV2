#include "myItem.h"

MyItem::MyItem(qreal x, qreal y, QAbstractGraphicsShapeItem *parent)
    : QAbstractGraphicsShapeItem(parent) {
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsMovable);
  this->selectedFromHover = false;
  setCursor(Qt::OpenHandCursor);
  setAcceptHoverEvents(true);
  setX(x);
  setY(y);
}

MyItem::MyItem(MyItem *item, QAbstractGraphicsShapeItem *parent)
    : MyItem(item->x(), item->y(), parent) {}

void MyItem::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
  if (!this->isSelected()) {
    this->setSelected(true);
    this->selectedFromHover = true;
  }
}

void MyItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
  if (this->selectedFromHover) {
    this->setSelected(false);
    this->selectedFromHover = false;
  }
}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  this->setCursor(Qt::ClosedHandCursor);
  this->setZValue(3);

  QGraphicsItem::mouseReleaseEvent(event);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  this->setCursor(Qt::OpenHandCursor);
  this->setZValue(0);

  QGraphicsItem::mouseReleaseEvent(event);

  emit mouseReleased(this);
}
