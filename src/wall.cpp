#include "wall.h"

Wall::Wall(QGraphicsRectItem *parent) : QGraphicsRectItem(parent) {
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setCursor(Qt::OpenHandCursor);
    selectedFromHover = false;
}

Wall::Wall(QRectF r, int size, QGraphicsRectItem *parent) : Wall(parent) {
    setRect(0, 0, r.width(), r.height());
    setX(r.x());
    setY(r.y());
    setSize(size);
}

Wall::Wall(Wall *wall, QGraphicsRectItem *parent) : Wall(QRectF(wall->x(), wall->y(), wall->rect().width(), wall->rect().height()), wall->getSize(), parent) { }

int Wall::getSize() {
    return this->size;
}

void Wall::setSize(int size) {
    this->size = size;
}

void Wall::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    if (!this->isSelected()) {
        this->setSelected(true);
        this->selectedFromHover = true;
    }
}

void Wall::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    if (this->selectedFromHover) {
        this->setSelected(false);
        this->selectedFromHover = false;
    }
}

void Wall::selectionChanged() {
    this->update();
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    if (!this->isSelected()) {
        painter->setBrush(Qt::white);
        painter->setPen(Qt::NoPen);
        painter->drawRect(option->rect);

    } else {
        painter->setBrush(Qt::gray);
        painter->setPen(Qt::NoPen);
        painter->drawRect(option->rect);

        painter->setBrush(Qt::red);
        painter->setPen(Qt::red);

        int x = option->rect.x();
        int y = option->rect.y();
        int s = this->size;

        QPolygonF poly;                                         // top left corner
        poly << QPointF(x, y)
             << QPointF(x, y + s * CL)
             << QPointF(x + s * CW, y + s * CL)
             << QPointF(x + s * CW, y + s * CW)
             << QPointF(x + s * CL, y + s * CW)
             << QPointF(x + s * CL, y);
        painter->drawPolygon(poly);
        poly.remove(0, 6);

        poly << QPoint(x + s, y + s)                            // bottom right corner
             << QPoint(x + s, y + s * (1 - CL))
             << QPoint(x + s * (1 - CW), y + s * (1 - CL))
             << QPoint(x + s * (1 - CW), y + s * (1 - CW))
             << QPoint(x + s * (1 - CL), y + s * (1 - CW))
             << QPoint(x + s * (1 - CL), y + s);
        painter->drawPolygon(poly);
        poly.remove(0, 6);

        poly << QPoint(x + s, y)                                // top right corner
             << QPoint(x + s * (1 - CL), y)
             << QPoint(x + s * (1 - CL), y + s * CW)
             << QPoint(x + s * (1 - CW), y + s * CW)
             << QPoint(x + s * (1 - CW), y + s * CL)
             << QPoint(x + s, y + s * CL);
        painter->drawPolygon(poly);
        poly.remove(0, 6);

        poly << QPoint(x, y + s)                                // bottom left corner
             << QPoint(x, y + s * (1 - CL))
             << QPoint(x + s * CW, y + s * (1 - CL))
             << QPoint(x + s * CW, y + s * (1 - CW))
             << QPoint(x + s * CL, y + s * (1 - CW))
             << QPoint(x + s * CL, y + s);
        painter->drawPolygon(poly);
        poly.remove(0, 6);
    }
}
