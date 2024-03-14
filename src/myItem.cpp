#include "myItem.h"

#include <iostream>

MyItem::MyItem(qreal x, qreal y, QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent), selectedFromHover(false) {
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges);
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

  QGraphicsItem::mousePressEvent(event);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  this->setCursor(Qt::OpenHandCursor);
  this->setZValue(0);

  QGraphicsItem::mouseReleaseEvent(event);
  if (event->button() == Qt::LeftButton) {
    emit mouseReleased(this);
  }
}

QVariant MyItem::itemChange(QGraphicsItem::GraphicsItemChange change,
                            const QVariant &value) {
  if (change == ItemPositionChange && scene()) {
    QPointF newPos = value.toPointF();
    QRectF rect = scene()->sceneRect();

    if (!rect.contains(QRectF(
            newPos, QSizeF(boundingRect().width(), boundingRect().height())))) {
      newPos.setX(
          qBound((qreal)0, newPos.x(), rect.right() - boundingRect().width()));

      newPos.setY(qBound((qreal)0, newPos.y(),
                         rect.bottom() - boundingRect().height()));

      return newPos;
    }
  }
  return QGraphicsItem::itemChange(change, value);
}
