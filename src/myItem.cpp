#include "myItem.h"

MyItem::MyItem(qreal x, qreal y, QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent), selectedFromHover(false) {
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsMovable);
  setCursor(Qt::OpenHandCursor);
  setAcceptHoverEvents(true);
  setX(x);
  setY(y);
}

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
