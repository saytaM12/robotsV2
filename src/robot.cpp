#include "robot.h"

Robot::Robot(int x, int y, int angle, bool player, MyItem *parent)
    : MyItem(x, y, parent) {
  setRect(0, 0, ROBOTSIZE, ROBOTSIZE);
  this->angle = angle;
  this->player = player;
  this->moving = false;
}

Robot::Robot(Robot *robot, MyItem *parent)
    : Robot(robot->MyItem::x(), robot->MyItem::y(), robot->getAngle(),
            robot->isPlayer(), parent) {}

bool Robot::isWall() const { return false; }

int Robot::getAngle() { return this->angle; }

bool Robot::isPlayer() { return this->player; }

bool Robot::getMoving() { return this->moving; }

void Robot::setAngle(int angle) { this->angle = angle; }

void Robot::setPlayer(bool player) { this->player = player; }

void Robot::setMoving(bool moving) { this->moving = moving; }

void Robot::contextMenuEvent(QGraphicsSceneContextMenuEvent *) {
  this->player = !this->player;
  this->MyItem::update();
}

QRectF Robot::boundingRect() const { return this->rect(); }

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *) {
  if (!this->MyItem::isSelected()) { // not selected
    if (this->player) {
      painter->setBrush(Qt::green); // player
      painter->setPen(Qt::NoPen);
      painter->drawEllipse(option->rect);

    } else {
      painter->setBrush(Qt::blue); // nonplayer
      painter->setPen(Qt::NoPen);
      painter->drawEllipse(option->rect);
    }

  } else { // seleceted
    if (this->player) {
      painter->setBrush(Qt::darkGreen); // player
      painter->setPen(Qt::NoPen);
      painter->drawEllipse(option->rect);

    } else {
      painter->setBrush(Qt::darkBlue); // nonplayer
      painter->setPen(Qt::NoPen);
      painter->drawEllipse(option->rect);
    }

    painter->setPen(QPen(Qt::yellow, ROBOTSIZE / 10, Qt::SolidLine,
                         Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::NoBrush);
    QLineF line(option->rect.center(), QPointF(0, 0));
    line.setLength(ROBOTSIZE * (4.0 / 10.0));
    line.setAngle((double)this->angle);
    painter->drawLine(line);
  }
}
