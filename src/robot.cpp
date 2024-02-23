#include "robot.h"

Robot::Robot(QGraphicsEllipseItem *parent) : QGraphicsEllipseItem(parent) {
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setCursor(Qt::OpenHandCursor);
    selectedFromHover = false;
}

Robot::Robot(QRectF r, int angle, bool player, QGraphicsEllipseItem *parent) : Robot(parent) {
    setRect(0, 0, r.width(), r.height());
    setX(r.x());
    setY(r.y());
    setAngle(angle);
    setPlayer(player);
}

int Robot::getAngle() {
    return this->angle;
}

bool Robot::isPlayer() {
    return this->player;
}

bool Robot::getMoving() {
    return this->moving;
}

void Robot::setAngle(int angle) {
    this->angle = angle;
}

void Robot::setPlayer(bool player) {
    this->player = player;
}

void Robot::setMoving(bool moving) {
    this->moving = moving;
}

void Robot::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    if (!this->isSelected()) {
        this->setSelected(true);
        this->selectedFromHover = true;
    }
}

void Robot::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    if (this->selectedFromHover) {
        this->setSelected(false);
        this->selectedFromHover = false;
    }
}

/*
void Robot::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(Qt::ClosedHandCursor);
}

void Robot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(Qt::OpenHandCursor);
}
*/

void Robot::contextMenuEvent(QGraphicsSceneContextMenuEvent *) {
    this->player = !this->player;
    this->update();
}

void Robot::selectionChanged() {
    this->update();
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    if (!this->isSelected()) {                  // not selected
        if (this->player) {
            painter->setBrush(Qt::green);           // player
            painter->setPen(Qt::NoPen);
            painter->drawEllipse(option->rect);

        } else {
            painter->setBrush(Qt::blue);            // nonplayer
            painter->setPen(Qt::NoPen);
            painter->drawEllipse(option->rect);
        }

    } else {                                    // seleceted
        if (this->player) {
            painter->setBrush(Qt::darkGreen);       // player
            painter->setPen(Qt::NoPen);
            painter->drawEllipse(option->rect);

        } else {
            painter->setBrush(Qt::darkBlue);        // nonplayer
            painter->setPen(Qt::NoPen);
            painter->drawEllipse(option->rect);
        }

    painter->setPen(QPen(Qt::yellow, ROBOTSIZE / 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::NoBrush);
    QLineF line(option->rect.center(), QPointF(0, 0));
    line.setLength(ROBOTSIZE * (4.0/10.0));
    line.setAngle((double)this->angle);
    painter->drawLine(line);

    }
}
