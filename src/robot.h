#pragma once

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include "myItem.h"

#define ROBOTSIZE 60

class Robot : public MyItem, public QGraphicsEllipseItem {

  Q_OBJECT

private:
  int angle;
  bool player;
  bool moving;
  int detectionRange;
  int detectionAngle;
  bool clockwise;

public:
  /* The constructor used to create a new Robot.
   * @param QRectF rect The rectangle that the robot is in.
   * @param int angle The angle that the robot is facing.
   * @param bool player Whether the robot is a player or not.
   * @param MyItem *parent The parent of the robot.
   */
  Robot(int x, int y, int angle = 0, bool player = false,
        QGraphicsItem *parent = nullptr);

  /* The constructor used to create a new Robot based off of another robot.
   * @param Robot *robot The robot that this robot is based off of.
   * @param MyItem *parent The parent of the robot.
   */
  Robot(Robot *robot, QGraphicsItem *parent = nullptr)
      : Robot(robot->MyItem::x(), robot->MyItem::y(), robot->getAngle(),
              robot->isPlayer(), parent) {}

  /* Method that returns whether this item is a wall or not. Always returns
   * false.
   * @return: bool false
   */
  inline bool isWall() const { return false; }

  /* This method returns the angle that the robot is facing.
   * @return: int
   */
  inline int getAngle() { return this->angle; }

  /* This method returns whether the robot is a player or not.
   * @return: bool
   */
  inline bool isPlayer() { return this->player; }

  /* This method returns whether the robot is moving or not.
   * @return: bool
   */
  inline bool getMoving() { return this->moving; }

  /* This method sets the angle that the robot is facing.
   * @param int angle: The angle that the robot is facing.
   * @return: void
   */
  inline void setAngle(int angle) { this->angle = angle; }

  /* This method sets the player status of the robot.
   * @param bool player: Whether the robot is a player or not.
   */
  inline void setPlayer(bool player) { this->player = player; }

  /* This method sets the moving status of the robot.
   * @param bool moving: Whether the robot is moving or not.
   * @return: void
   */
  inline void setMoving(bool moving) { this->moving = moving; }

  /* This method is called when the robot is right clicked.
   * It simply toggles the player status of the robot.
   * @param QGraphicsSceneContextMenuEvent *event: The event that occured.
   * @return: void
   */
  inline void contextMenuEvent(QGraphicsSceneContextMenuEvent *) {
    this->player = !this->player;
    this->MyItem::update();
  }

  /* Method to return the bounding rectangle of the robot.
   * This method must be implemented, otherwise the program breaks. This is due
   * to inheritance sheananigans.
   * @return: QRectF
   */
  QRectF boundingRect() const { return this->rect(); }

  /* This method is used to paint the robot.
   * @param QPainter *painter: The painter object.
   * @param QStyleOptionGraphicsItem *option: The options for the painting.
   * @param QWidget *widget: The widget that the painting is occuring in.
   * Omit for global painting.
   * @return: void
   */
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr);
};
