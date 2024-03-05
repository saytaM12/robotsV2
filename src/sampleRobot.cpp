#include "sampleRobot.h"

SampleRobot::SampleRobot(int x, int y, int angle, bool player, Robot *parent)
    : Robot(x, y, angle, player, parent) {
  MyItem::setFlag(QGraphicsItem::ItemIsMovable, false);
}

SampleRobot::SampleRobot(SampleRobot *robot, Robot *parent)
    : SampleRobot(robot->MyItem::x(), robot->MyItem::y(), robot->getAngle(),
                  robot->isPlayer(), parent) {}
