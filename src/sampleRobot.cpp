#include "sampleRobot.h"

SampleRobot::SampleRobot(QRectF r, int a, bool p, QGraphicsEllipseItem *parent) : Robot(r, a, p, parent) {
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

SampleRobot::SampleRobot(SampleRobot *robot, QGraphicsEllipseItem *parent) : SampleRobot(QRectF(robot->x(), robot->y(), robot->rect().width(), robot->rect().height()), robot->getAngle(), robot->isPlayer(), parent) { }

/*
void SampleRobot::mousePressEvent(QGraphicsSceneMouseEvent *) {
    SampleRobot *robot = new SampleRobot(this);
    robot->setParentItem(this->parentItem());
    robot->setZValue(this->zValue());
}

void SampleRobot::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
    emit robotAdded(new Robot(this, nullptr));
    delete this;
}
*/
