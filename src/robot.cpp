#include "robot.h"

Robot::Robot(QGraphicsEllipseItem *parent) : QGraphicsEllipseItem(parent) {
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

Qt::GlobalColor Robot::getColor() {
    return this->color;
}

int Robot::getAngle() {
    return this->angle;
}

bool Robot::getMoving() {
    return this->moving;
}

void Robot::setColor(Qt::GlobalColor color) {
    this->color = color;
}

void Robot::setAngle(int angle) {
    this->angle = angle;
}

void Robot::setMoving(bool moving) {
    this->moving = moving;
}

void Robot::selectionChanged() {
    if (this->isSelected()) {
        if (this->color == Qt::blue) {
            this->color = Qt::darkBlue;
        }
        if (this->color == Qt::green) {
            this->color = Qt::darkGreen;
        }
    } else {
        if (this->color == Qt::darkBlue) {
            this->color = Qt::blue;
        }
        if (this->color == Qt::darkGreen) {
            this->color = Qt::green;
        }
    }
    this->update();
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(this->color);
    painter->setPen(Qt::NoPen);

    painter->drawEllipse(option->rect);
}
