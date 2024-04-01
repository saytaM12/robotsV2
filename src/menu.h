#pragma once

#include <QEvent>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPointer>
#include <QPushButton>
#include <QStyleOptionGraphicsItem>

#include "guiMacros.h"
#include "robot.h"
#include "wall.h"

class SampleRobot;
class SampleWall;

class Menu : public QWidget, public QGraphicsRectItem {

    Q_OBJECT

  private:
    QPointer<QPushButton> saveButton;
    QPointer<QPushButton> loadButton;
    QPointer<SampleWall> sampleWall;
    QPointer<SampleRobot> sampleRobot;

  public:
    /* This constructor creates a new menu
     * @param QGraphicsRectItem *parent: The parent of this object.
     */
    Menu(int menuWidth, int menuHeight, QGraphicsScene *parent = nullptr);

    /* This method returns the sample robot
     * @return: SampleRobot*
     */
    inline SampleRobot *getSampleRobot() { return sampleRobot; }

    /* This method returns the sample wall
     * @return: SampleWall*
     */
    inline SampleWall *getSampleWall() { return sampleWall; }

    /* This method is called to paint the menu
     * @param QPainter *painter: The painter to be used
     * @param const QStyleOptionGraphicsItem *option: The option to be used
     * @param QWidget *widget: The widget that is painted on. Omit for global
     * painting.
     * @return: void
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

  public slots:
    /* When this slot is called the menu is toggled
     * It toggles the visibility of the menu.
     * @return: void
     */
    void toggle();

  signals:
    void savePressed();
    void loadPressed();
};

class SampleRobot : public Robot {

  public:
    /* Constructor for SampleRobot. creates a new SampleRobot.
     * @param QrectF rect: Rectangle in which the robot is placed.
     * @param int angle: The angle the robot is facing.
     * @param bool player: Whether the robot is a player or not.
     * @param Robot *parent: The parent of this object.
     */
    SampleRobot(QPointF topLeft, Menu *parent) : Robot(topLeft.x(), topLeft.y(), parent) {
        MyItem::setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override {}
};

class SampleWall : public Wall {

  public:
    /* Constructor for SampleWall. creates a new SampleWall.
     * @param QrectF rect: Rectangle in which the wall is placed.
     * @param int size: The size of the wall.
     * @param Wall *parent: The parent of this object.
     */
    SampleWall(QRectF rect, Menu *parent) : Wall(rect.x(), rect.y(), rect.width(), rect.height(), parent) {
        MyItem::setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override { MyItem::mouseMoveEvent(event); }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override { MyItem::hoverEnterEvent(event); }

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override { MyItem::hoverMoveEvent(event); }
};
