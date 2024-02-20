#include "wall.h"

Wall::Wall(QGraphicsRectItem *parent) : QGraphicsRectItem(parent) {
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

Qt::GlobalColor Wall::getColor() {
    return this->color;
}

int Wall::getSize() {
    return this->size;
}

void Wall::setColor(Qt::GlobalColor color) {
    this->color = color;
}

void Wall::setSize(int size) {
    this->size = size;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(this->color);
    painter->setPen(Qt::NoPen);

    painter->drawRect(option->rect);
}

void Wall::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    this->color = Qt::gray;
    this->update();
}

void Wall::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    this->color = Qt::white;
    this->update();
}
