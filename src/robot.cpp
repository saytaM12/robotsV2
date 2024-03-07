#include "robot.h"

Robot::Robot(int x, int y, int angle, bool player, QGraphicsItem *parent)
    : MyItem(x, y, parent), angle(angle), player(player), moving(false) {
  setRect(0, 0, ROBOTSIZE, ROBOTSIZE);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *) {

  Qt::GlobalColor style = this->player ? Qt::green : Qt::blue;

  // this will make the color darker if the robot is selected
  if (this->MyItem::isSelected()) {
    style = (Qt::GlobalColor)((int)style + 6); // i know, it's bad
  }

  painter->setBrush(style);
  painter->setPen(Qt::NoPen);
  painter->drawEllipse(option->rect);

  /* painter->setPen(QPen(Qt::yellow, ROBOTSIZE / 10, Qt::SolidLine, */
  /*                      Qt::RoundCap, Qt::RoundJoin)); */
  /* painter->setBrush(Qt::NoBrush); */
  /* QLineF line(option->rect.center(), QPointF(0, 0)); */
  /* line.setLength(ROBOTSIZE * (4.0 / 10.0)); */
  /* line.setAngle((double)this->angle); */
  /* painter->drawLine(line); */
}
