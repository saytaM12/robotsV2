#include "wall.h"

#include <QDebug>

Wall::Wall(int x, int y, int width, int height, QGraphicsItem *parent)
    : MyItem(x, y, parent), QGraphicsRectItem(0, 0, width, height), binaryResizeSelector(0) {
    setRect(0, 0, width, height);
}

void Wall::resizeEvent(QGraphicsSceneHoverEvent *event) {
    binaryResizeSelector = 0;
    if (event->pos().x() < WALL_RESIZE_SIZE) { // left side
        binaryResizeSelector |= 0b1000;
        MyItem::setCursor(Qt::SizeHorCursor);
    }
    if (event->pos().y() > rect().height() - WALL_RESIZE_SIZE) { // bottom side
        binaryResizeSelector |= 0b0100;
        MyItem::setCursor(Qt::SizeVerCursor);
    }
    if (event->pos().y() < WALL_RESIZE_SIZE) { // top side
        binaryResizeSelector |= 0b0010;
        MyItem::setCursor(Qt::SizeVerCursor);
    }
    if (event->pos().x() > rect().width() - WALL_RESIZE_SIZE) { // right side
        binaryResizeSelector |= 0b0001;
        MyItem::setCursor(Qt::SizeHorCursor);
    }
    if (!binaryResizeSelector) {
        MyItem::setCursor(Qt::OpenHandCursor);
        return;
    }

    switch (binaryResizeSelector) {
    case 0b1010:
    case 0b0101:
        MyItem::setCursor(Qt::SizeFDiagCursor);
        break;
    case 0b1100:
    case 0b0011:
        MyItem::setCursor(Qt::SizeBDiagCursor);
        break;
    }
}

void Wall::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    resizeEvent(event);
    MyItem::hoverEnterEvent(event);
}

void Wall::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    resizeEvent(event);
    MyItem::hoverMoveEvent(event);
}

void Wall::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    if (justCreated || binaryResizeSelector == 0) {
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    QRectF oldRect(MyItem::x(), MyItem::y(), rect().width(), rect().height());

    if (binaryResizeSelector & 0b1000) {
        MyItem::setX(qMin(MyItem::x() + event->pos().x(), MyItem::x() + rect().width() - MIN_WALL_SIZE));
        setRect(0, 0, qMax(rect().width() - event->pos().x(), MIN_WALL_SIZE), rect().height());
    }

    if (binaryResizeSelector & 0b0100) {
        setRect(0, 0, rect().width(), qMax(event->pos().y(), MIN_WALL_SIZE));
    }

    if (binaryResizeSelector & 0b0010) {
        MyItem::setY(qMin(MyItem::y() + event->pos().y(), MyItem::y() + rect().height() - MIN_WALL_SIZE));
        setRect(0, 0, rect().width(), qMax(rect().height() - event->pos().y(), MIN_WALL_SIZE));
    }

    if (binaryResizeSelector & 0b0001) {
        setRect(0, 0, qMax(event->pos().x(), MIN_WALL_SIZE), rect().height());
    }

    MyItem::scene()->update(oldRect);
    MyItem::update();

    MyItem::mouseMoveEvent(event);
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
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
