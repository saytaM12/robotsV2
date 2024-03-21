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
#include <QStyleOptionGraphicsItem>

#include "robot.h"
#include "wall.h"

/* GUI BUTTONS
 * BWS = button width (inverse) scaler
 * BHS = button height (inverse) scaler
 * mW  = menu width
 * mH  = menu height
 * BW  = button width
 * BH  = button height
 * LBX = left button x
 * RBX = right button x
 * BY  = both button y
 */
#define BWS (1.0 / 3.0) // must be between 0 and 1
#define BHS (1.0 / 5.0) // must be between 0 and 1
#define BW(mW) ((mW) * BWS)
#define BH(mW) ((mW) * BHS)
/* (mw - (mw * 2 * bws)) / 3  //(mw*2bws) = both_width, mw - (...) = white space
 * 1/3(1 - 2bws) * mw
 * mw * (1 - 2 * bws) / 3
 */
#define LBX(mW) ((mW) * (1 - 2 * BWS) / 3.0)
/* LBX / 2 + mw / 2   // the same padding but from center of menu
 * simplifies to -> mw * 5/9
 */
#define RBX(mW) ((mW) * 5.0 / 9.0)
/* mw * bhs                 // button height
 * mw * (1 - 2 * bws) / 3   // button padding
 *
 * mh - (mw * bhs + (mw * (1 - 2 * bws) / 3))
 * mh - mw * (bhs + (1 - 2 * bws) / 3)
 */
#define BY(mW, mH) ((mH) - (mW) * (BHS + (1 - 2 * BWS) / 3))
#define LEFT_BUTTON_RECT(mW, mH) QRectF(LBX(mW), BY(mW, mH), BW(mW), BH(mW))
#define RIGHT_BUTTON_RECT(mW, mH) QRectF(RBX(mW), BY(mW, mH), BW(mW), BH(mW))

/* GUI SAMLPLE ITEMS
 * SWS = sample wall size
 * SB  = sample background scaler
 * SBS = sample background size
 * RX  = robot x
 * RY  = robot y
 * WX  = wall x
 * WY  = wall y
 * SBX = sample background x
 * TSBY = top sample background y
 * BSBY = bottom sample background y
 */
#define SWS 100
#define SB (9.0 / 10.0) // must be between 0 and 1
#define SBS(mW) ((mW) * SB)
/* half of robot to the left of center of menu */
#define RX(mW) ((mW) / 2.0 - ROBOTSIZE / 2.0)
/* mw * bhs +                   // button height
 * mw * (1 - 2 * bws) / 1.5 +   // two button paddings (top and bot)
 * mw * 1.5 * sb +              // one and a half sample backgrounds
 * mw * (1 - sb) / 2 +          // one sample background padding
 * ROBOTSIZE / 2                // from center to top of robot
 *
 * mw * bhs + mw * (1 - 2 * bws) / 1.5 + mw * 1.5 * sb + mw * (1 - sb) / 2 +
 *   ROBOTSIZE / 2
 * mw * (bhs + (1 - 2 * bws) / 1.5 + 1.5 * sb + (1 - sb) / 2) + ROBOTSIZE / 2
 * mw * (bhs + (1 - 2 * bws) / 1.5 + (2 * sb + 1) / 2) + ROBOTSIZE / 2
 */
#define RY(mW, mH) ((mH) - ((mW) * (BHS + (1 - 2 * BWS) / 1.5 + (2 * SB + 1) / 2.0) + ROBOTSIZE / 2.0))
/* half of wall to the left of center of menu */
#define WX(mW) ((mW) / 2.0 - SWS / 2.0)
/* mw * bhs +                   // button height
 * mw * (1 - 2 * bws) / 1.5 +   // two button paddings (top and bot)
 * mw * 0.5 * sb +              // half a sample background
 * SWS / 2                      // from center to top of wall
 *
 * mw * bhs + mw * (1 - 2 * bws) / 1.5 + mw * 0.5 * sb + SWS / 2
 * mw * (bhs + (1 - 2 * bws) / 1.5 + 0.5 * sb) + SWS / 2
 */
#define WY(mW, mH) ((mH) - ((mW) * (BHS + (1 - 2 * BWS) / 1.5 + 0.5 * SB) + SWS / 2.0))
#define SAMPLE_ROBOT_TOPLEFT(mW, mH) QPointF(RX(mW), RY(mW, mH))
#define SAMPLE_WALL_RECT(mW, mH) QRectF(WX(mW), WY(mW, mH), SWS, SWS)

#define SBX(mW) ((mW) * (1 - SB) / 2.0)
/* mw * bhs +                   // button width
 * mw * (1 - 2 * bws) / 1.5 +   // two button paddings (top and bot)
 * mw * 2 * sb +                // two sample backgrounds
 * mw * (1 - sb) / 2 +          // one sample background padding
 *
 * mw * bhs + mw * (1 - 2 * bws) / 1.5 + mw * 2 * sb + mw * (1 - sb) / 2
 * mw * (bhs + (1 - 2 * bws) / 1.5 + 2 * sb + (1 - sb) / 2)
 * mw * (bhs + (1 - 2 * bws) / 1.5 + (3 * sb + 1) / 2)
 */
#define TSBY(mW, mH) ((mH) - (mW) * (BHS + (1 - 2 * BWS) / 1.5 + (3 * SB + 1) / 2))
/* mw * bhs +                   // button width
 * mw * (1 - 2 * bws) / 1.5 +   // two button paddings (top and bot)
 * mw * sb +                    // one sample background
 *
 * mw * bhs + mw * (1 - 2 * bws) / 1.5 + mw * sb
 * mw * (bhs + (1 - 2 * bws) / 1.5 + sb)
 */
#define BSBY(mW, mH) ((mH) - (mW) * (BHS + (1 - 2 * BWS) / 1.5 + SB))
#define TOP_SAMPLE_BACKGROUND_RECT(mW, mH) QRectF(SBX(mW), TSBY(mW, mH), SBS(mW), SBS(mW))
#define BOT_SAMPLE_BACKGROUND_RECT(mW, mH) QRectF(SBX(mW), BSBY(mW, mH), SBS(mW), SBS(mW))

class MyButton;
class SampleRobot;
class SampleWall;

class Menu : public QWidget, public QGraphicsRectItem {

    Q_OBJECT

  private:
    QPointer<MyButton> saveButton;
    QPointer<MyButton> loadButton;
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
    void toggle() {
        QGraphicsRectItem::setVisible(!QGraphicsRectItem::isVisible());
        QGraphicsRectItem::update();
    }

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
    SampleRobot(QPointF topLeft, int angle, bool player, Menu *parent)
        : Robot(topLeft.x(), topLeft.y(), angle, player, parent) {
        MyItem::setFlag(QGraphicsItem::ItemIsMovable, false);
    }
};

class SampleWall : public Wall {

  protected:
    void resizeEvent(QGraphicsSceneHoverEvent *) {}

  public:
    /* Constructor for SampleWall. creates a new SampleWall.
     * @param QrectF rect: Rectangle in which the wall is placed.
     * @param int size: The size of the wall.
     * @param Wall *parent: The parent of this object.
     */
    SampleWall(QRectF rect, Menu *parent) : Wall(rect.x(), rect.y(), rect.width(), rect.height(), parent) {
        MyItem::setFlag(QGraphicsItem::ItemIsMovable, false);
    }
};

class MyButton : public QObject, public QGraphicsRectItem {

    Q_OBJECT

  private:
    QString string;

  public:
    /* This constructor is used to create a new MyButton object.
     * @param QString string: The string to be displayed on the button.
     * @param QGraphicsRectItem *parent: The parent of this object.
     */
    MyButton(QRectF rect, QString string, Menu *menu);

    /* This method is called when the mouse is pressed on the button.
     * It doens nothing, but if this method isn't implemented `mouseReleaseEvent`
     * won't be called.
     * @param QGraphicsSceneMouseEvent *event: The event that was triggered.
     * @return: void
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *) {}

    /* This method is called when the mouse, which was pressed on the button, is
     * released.
     * If the mouse was pressed on the button it emits a signal (pressed) to
     * trigger the evnt.
     * @param QGraphicsSceneMouseEvent *event: The event that was triggered.
     * @return: void
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) { emit pressed(); }

    /* This method is called to paint the button.
     * @param QPainter *painter: The painter to be used.
     * @param const QStyleOptionGraphicsItem *option: The option to be used.
     * @param QWidget *widget: The widget on which the painting will be done.
     * Omit for global painting.
     * @return: void
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

  signals:
    void pressed();
};
