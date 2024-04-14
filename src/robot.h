#pragma once

#include <QDialog>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPainter>
#include <QPointer>
#include <QPushButton>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QtMath>

#include "darkenImage.h"
#include "myItem.h"
#include "robotUtils.h"

class Robot : public MyItem, public QGraphicsEllipseItem {

    Q_OBJECT

  private:
    QString texture;
    QGraphicsLineItem *rotationLine;

    int speed;
    bool player;
    bool rotating;
    bool clockwise;
    bool simulating;
    int detectionRange;
    int detectionAngle;

    QPointer<RobotContextMenu> contextMenu;

  public:
    /* The constructor used to create a new Robot.
     * @param QRectF rect The rectangle that the robot is in.
     * @param int speed The speed of the robot.
     * @param int angle The angle that the robot is facing.
     * @param bool player Whether the robot is a player or not.
     * @param clockwise Whether the robot turns clockwise on detection or not.
     * @param int detectionAngle The angle the robot turn on detection.
     * @param detectionRange The range of detection of the robot.
     * @param MyItem *parent The parent of the robot.
     */
    Robot(int x, int y, int speed, int angle, bool player, bool clockwise, int detectionAngle,
          int detectionRange, QGraphicsItem *parent = nullptr);

    Robot(int x, int y, QGraphicsItem *parent = nullptr) : Robot(x, y, 1, 0, false, false, 1, 100, parent) {}

    /* The constructor used to create a new Robot based off of another robot.
     * @param Robot *robot The robot that this robot is based off of.
     * @param MyItem *parent The parent of the robot.
     */
    Robot(Robot *robot, QGraphicsItem *parent = nullptr)
        : Robot(robot->MyItem::x(), robot->MyItem::y(), robot->getSpeed(), robot->getAngle(),
                robot->isPlayer(), robot->isClockwise(), robot->getDetectionAngle(),
                robot->getDetectionRange(), parent) {}

    /* Method that returns whether this item is a wall or not. Always returns
     * false.
     * @return: bool false
     */
    inline bool isWall() const override { return false; }

    /* This method returns the speed of the robot.
     * @return: int
     */
    inline int getSpeed() { return speed; }

    /* This method returns the angle that the robot is facing.
     * @return: int
     */
    inline int getAngle() { return MyItem::rotation(); }

    /* This method returns whether the robot is moving or not.
     * @return: bool
     */
    inline bool isMoving() { return simulating; }

    /* This method returns whether the robot is a player or not.
     * @return: bool
     */
    inline bool isPlayer() { return player; }

    /* This method returns the turning direction of the robot.
     * @return: bool
     */
    inline bool isClockwise() { return clockwise; }

    /* This method returns the detection range of the robot.
     * @return: int
     */
    inline int getDetectionRange() { return detectionRange; }

    /* This method returns the detection angle of the robot.
     * @return: int
     */
    inline int getDetectionAngle() { return detectionAngle; }

    /* This method sets the angle that the robot is facing.
     * @param int angle: The angle that the robot is facing.
     * @return: void
     */
    inline void setAngle(int newAngle) { MyItem::setRotation(newAngle); }

    /* This method sets the player status of the robot.
     * @param bool player: Whether the robot is a player or not.
     */
    inline void setPlayer(bool newPlayer) { player = newPlayer; }

    /* This method sets the moving status of the robot.
     * @param bool moving: Whether the robot is moving or not.
     * @return: void
     */
    inline void setMoving(bool newMoving) { simulating = newMoving; }

    /* This method is called when the mouse is realased after clicking the robot
     * It brings up the context menu to change the robot's parameters
     * @param QGraphicsSceneMouseEvent *event: The event that occured.
     * @return: void
     */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /* Method to return the bounding rectangle of the robot.
     * This method must be implemented, otherwise the program breaks. This is due
     * to inheritance sheananigans.
     * @return: QRectF
     */
    QRectF boundingRect() const override { return QRectF(rect().toAlignedRect()); }

    /* This method returns the visual bounding rectangle of the robot.
     * @return: QRectF
     */
    QRectF visualBoundingRect() const override { return rect(); }

    /* This method is used to paint the robot.
     * @param QPainter *painter: The painter object.
     * @param QStyleOptionGraphicsItem *option: The options for the painting.
     * @param QWidget *widget: The widget that the painting is occuring in.
     * Omit for global painting.
     * @return: void
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

  public slots:
    void gameTick();

    void changePlayer();
    void changeIcon();
    void setSpeed();
    void setDetectionRange();
    void setDetectionAngle();
    void setTurningDirection();
};
