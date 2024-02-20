#include "wall.h"

Wall::Wall(QGraphicsRectItem *parent) : QGraphicsRectItem(parent) {
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
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

void Wall::selectionChanged() {
    if (this->isSelected()) {
        this->color = Qt::gray;
    } else {
        this->color = Qt::white;
    }
    this->update();
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(this->color);
    painter->setPen(Qt::NoPen);

    painter->drawRect(option->rect);
}
