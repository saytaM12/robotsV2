#include "sampleWall.h"

SampleWall::SampleWall(QRectF r, int s, QGraphicsRectItem *parent) : Wall(r, s, parent) {
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

SampleWall::SampleWall(SampleWall *wall, QGraphicsRectItem *parent) : SampleWall(QRectF(wall->x(), wall->y(), wall->rect().width(), wall->rect().height()), wall->getSize(), parent) { }

/*
void SampleWall::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Wall *wall = new Wall(this, nullptr);
    wall->setZValue(this->zValue() + 1);
    QMouseEvent e(QEvent::MouseButtonPress, event->pos(), event->scenePos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
    emit wallAdded(wall, &e);
}

void SampleWall::mouseReleaseEvent(QGraphicsSceneMouseEvent *) { }

void SampleWall::mousePressEvent(QGraphicsSceneMouseEvent *) {
    SampleWall *wall = new SampleWall(this);
    wall->setParentItem(this->parentItem());
    wall->setZValue(this->zValue());
}

void SampleWall::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
    emit wallAdded(new Wall(this, nullptr));
    delete this;
}
*/
