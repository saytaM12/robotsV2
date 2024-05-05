/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 */
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

/**
 * @brief The Robot class represents a robot in the scene.
 *
 * It inherits from MyItem and QGraphicsEllipseItem.
 */
class Robot : public MyItem, public QGraphicsEllipseItem {

    Q_OBJECT

  private:
    QString texture;                 /**< The name of the texture image file of the robot. */
    QGraphicsLineItem *rotationLine; /**< The rotation line of the robot. */

    int speed;          /**< The speed of the robot. */
    int player;         /**< The player number of the robot. */
    bool rotating;      /**< Whether the robot is currentely rotating. */
    bool clockwise;     /**< Whether the robot turns clockwise on detection. */
    int detectionRange; /**< The range of detection of the robot. */
    int detectionAngle; /**< The angle the robot turns on detection. */

    char playerMoving; /**< The direction in which the player is moving. */

    QPointer<RobotContextMenu> contextMenu; /**< Pointer to the context menu for the robot. */

  public:
    /**
     * @brief Constructor for the Robot class.
     *
     * @param x The x-coordinate of the robot.
     * @param y The y-coordinate of the robot.
     * @param speed The speed of the robot.
     * @param angle The angle that the robot is facing.
     * @param player Whether the robot is a player or not.
     * @param clockwise Whether the robot turns clockwise on detection or not.
     * @param detectionAngle The angle the robot turn on detection.
     * @param detectionRange The range of detection of the robot.
     * @param parent The parent item.
     */
    Robot(qreal x, qreal y, int speed, qreal angle, int player, bool clockwise, int detectionAngle,
          int detectionRange, QGraphicsItem *parent = nullptr);

    /**
     * @brief Constructor for a default robot with default values.
     *
     * @param x The x-coordinate of the robot.
     * @param y The y-coordinate of the robot.
     * @param parent The parent item.
     */
    Robot(qreal x, qreal y, QGraphicsItem *parent = nullptr)
        : Robot(x, y, 1, 0, false, false, 1, 100, parent) {}

    /**
     * @brief Constructor for the Robot class based on another robot.
     *
     * @param robot The robot that this robot is based on.
     * @param parent The parent item.
     */
    Robot(Robot *robot, QGraphicsItem *parent = nullptr)
        : Robot(robot->MyItem::x(), robot->MyItem::y(), robot->getSpeed(), robot->getAngle(),
                robot->getPlayer(), robot->isClockwise(), robot->getDetectionAngle(),
                robot->getDetectionRange(), parent) {}

    /**
     * @brief Method that returns whether this item is a wall or not.
     *
     * Since this is a robot it always returns false.
     *
     * @return bool false
     */
    inline bool isWall() const override { return false; }

    /**
     * @brief This method returns the speed of the robot.
     *
     * @return int The speed of the robot.
     */
    inline int getSpeed() const { return speed; }

    /**
     * @brief This method returns the angle that the robot is facing.
     *
     * @return int The angle that the robot is facing.
     */
    inline qreal getAngle() const {
        return MyItem::rotation() < 0 ? abs(MyItem::rotation()) : (360 - MyItem::rotation());
    }

    /**
     * @brief This method returns the player number of the robot.
     *
     * @return int The player number
     */
    inline int getPlayer() const { return player; }

    /**
     * @brief This method returns if the robot is rotating clockwise on derection.
     *
     * @return bool If robot rotates clockwise on detection
     */
    inline bool isClockwise() const { return clockwise; }

    /**
     * @brief This method returns the detection range of the robot.
     *
     * @return int The detection range of the robot.
     */
    inline int getDetectionRange() const { return detectionRange; }

    /**
     * @brief This method returns the angle in degrees the robot turns on detection.
     *
     * @return int The detection angle of the robot.
     */
    inline int getDetectionAngle() const { return detectionAngle; }

    /**
     * @brief This method sets the angle that the robot is facing.
     * Zero is up and the angle increases clockwise.
     *
     * @param newAngle The new angle of the robot.
     */
    inline void setAngle(qreal newAngle) { MyItem::setRotation(newAngle); }

    /**
     * @brief This method sets the player number of the robot.
     *
     * @param newPlayer Player number of the robot.
     */
    inline void setPlayer(int newPlayer) { player = newPlayer; }

    /**
     * @brief This method handles player movement.
     *
     * @param direction The direction of movement.
     * @param set Whether to set or unset the direction.
     */
    void playerSetMove(Direction direction, bool set);

    /**
     * @brief This method is called when a context menu is requested.
     *
     * It brings up the context menu to change the robot's parameters.
     *
     * @param event The context menu event.
     */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override {
        contextMenu->exec(event->screenPos());
    }

    /**
     * @brief This method handles mouse drag events.
     *
     * @param event The mouse event.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief This method handles mouse press event.
     *
     * @param event The mouse event.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Method to return the bounding rectangle of the robot.
     *
     * @return QRectF The bounding rectangle of the robot.
     */
    QRectF boundingRect() const override { return QRectF(rect().toAlignedRect()); }

    /**
     * @brief This method is used to paint the robot.
     *
     * @param painter The painter object.
     * @param option The options for the painting.
     * @param widget The widget that the painting is occuring in. Omit for global painting.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

  signals:
    bool detectObjects();

    /**
     * @brief Signal emitted when the player number is changed.
     *
     * @param player The new player status.
     */
    void playerChanged(int player);

  public slots:
    /**
     * @brief Slot called on game tick.
     */
    void gameTick();

    /**
     * @brief Slot to change the player.
     */
    void changePlayer();

    /**
     * @brief Slot to change the robot icon.
     */
    void changeIcon();

    /**
     * @brief Slot to set the speed of the robot.
     */
    void setSpeed();

    /**
     * @brief Slot to set the detection range of the robot.
     */
    void setDetectionRange();

    /**
     * @brief Slot to set the detection angle of the robot.
     */
    void setDetectionAngle();

    /**
     * @brief Slot to set the turning direction of the robot.
     */
    void setTurningDirection();
};
