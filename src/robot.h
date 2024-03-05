#ifndef ROBOT
#define ROBOT

#include <QGraphicsEllipseItem>
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
  /*
   * The constructor used to create a new Robot.
   * @param QRectF rect The rectangle that the robot is in.
   * @param int angle The angle that the robot is facing.
   * @param bool player Whether the robot is a player or not.
   * @param MyItem *parent The parent of the robot.
   */
  Robot(int x, int y, int angle = 0, bool player = false,
        MyItem *parent = nullptr);

  /*
   * The constructor used to create a nwe Robot from an existing Robot.
   * @param Robot *robot The robot to be copied.
   * @param MyItem *parent The parent of the robot.
   */
  Robot(Robot *robot, MyItem *parent = nullptr);

  /*
   * Method that returns whether this item is a wall or not. Always returns
   * false.
   * @return: bool false
   */
  bool isWall() const;

  /*
   * This method returns the angle that the robot is facing.
   * @return: int
   */
  int getAngle();

  /*
   * This method returns whether the robot is a player or not.
   * @return: bool
   */
  bool isPlayer();

  /*
   * This method returns whether the robot is moving or not.
   * @return: bool
   */
  bool getMoving();

  /*
   * This method sets the angle that the robot is facing.
   * @param int angle: The angle that the robot is facing.
   * @return: void
   */
  void setAngle(int angle);

  /*
   * This method sets the player status of the robot.
   * @param bool player: Whether the robot is a player or not.
   */
  void setPlayer(bool player);

  /*
   * This method sets the moving status of the robot.
   * @param bool moving: Whether the robot is moving or not.
   * @return: void
   */
  void setMoving(bool moving);

  /*
   * This method is called when the robot is right clicked.
   * It simply toggles the player status of the robot.
   * @param QGraphicsSceneContextMenuEvent *event: The event that occured.
   * @return: void
   */
  void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

  /*
   * Method to return the bounding rectangle of the robot.
   * This method must be implemented, otherwise the program breaks. This is due
   * to inheritance sheananigans.
   * @return: QRectF
   */
  QRectF boundingRect() const;

  /*
   * This method is used to paint the robot.
   * @param QPainter *painter: The painter object.
   * @param QStyleOptionGraphicsItem *option: The options for the painting.
   * @param QWidget *widget: The widget that the painting is occuring in.
   * Omit for global painting.
   * @return: void
   */
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr);
};

#endif // ROBOT
