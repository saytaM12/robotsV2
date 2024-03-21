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
    if (!isSelected()) {
        setSelected(true);
        selectedFromHover = true;
    }
}

void MyItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    if (selectedFromHover) {
        setSelected(false);
        selectedFromHover = false;
    }
}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        QGraphicsItem::mousePressEvent(event);
        return;
    }

    setCursor(Qt::ClosedHandCursor);
    setZValue(3);

    QGraphicsItem::mousePressEvent(event);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        QGraphicsItem::mousePressEvent(event);
        return;
    }

    setCursor(Qt::OpenHandCursor);
    setZValue(0);

    QGraphicsItem::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton) {
        emit mouseReleased(this);
    }
}

QVariant MyItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();

        if (!rect.contains(QRectF(newPos, QSizeF(boundingRect().width(), boundingRect().height())))) {
            newPos.setX(qBound((qreal)0, newPos.x(), rect.right() - boundingRect().width()));

            newPos.setY(qBound((qreal)0, newPos.y(), rect.bottom() - boundingRect().height()));

            return newPos;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
