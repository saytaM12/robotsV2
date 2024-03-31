#pragma once

#include <QDialog>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPainter>
#include <QPointer>
#include <QPushButton>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include "darkenImage.h"
#include "myItem.h"
#include "robotContextMenu.h"

#define setParametersWithDialog(inputLabelText, descriptionText, limitMin, limitMax, parameter)               \
    QDialog dialog;                                                                                           \
    QGridLayout layout(&dialog);                                                                              \
                                                                                                              \
    QLabel inputLabel((inputLabelText));                                                                      \
                                                                                                              \
    QLineEdit lineEdit;                                                                                       \
    if (limitMax == 0) {                                                                                      \
        lineEdit.setValidator(new QIntValidator(limitMin));                                                   \
    } else {                                                                                                  \
        lineEdit.setValidator(new QIntValidator(limitMin, limitMax));                                         \
    }                                                                                                         \
    lineEdit.setPlaceholderText(QString("current value: %2").arg((parameter)));                               \
                                                                                                              \
    QLabel description((descriptionText));                                                                    \
                                                                                                              \
    QPushButton okButton("OK");                                                                               \
    QPushButton cancelButton("Cancel");                                                                       \
                                                                                                              \
    layout.addWidget(&inputLabel, 0, 0);                                                                      \
    layout.addWidget(&lineEdit, 0, 1);                                                                        \
    layout.addWidget(&description, 1, 0, 1, 2);                                                               \
    layout.addWidget(&okButton, 2, 0);                                                                        \
    layout.addWidget(&cancelButton, 2, 1);                                                                    \
                                                                                                              \
    QObject::connect(&okButton, &QPushButton::clicked, [&dialog, &lineEdit, this]() {                         \
        dialog.accept();                                                                                      \
        (parameter) = atoi(qPrintable(lineEdit.text()));                                                      \
    });                                                                                                       \
    QObject::connect(&cancelButton, &QPushButton::clicked, [&dialog]() { dialog.reject(); });                 \
                                                                                                              \
    dialog.exec();

#define ROBOTSIZE 80

class Robot : public MyItem, public QGraphicsEllipseItem {

    Q_OBJECT

  private:
    QString texture;

    bool rotating;

    int angle;
    bool player;
    bool moving;
    int speed;
    int detectionRange;
    int detectionAngle;
    bool clockwise;

    QPointer<RobotContextMenu> contextMenu;

  public:
    /* The constructor used to create a new Robot.
     * @param QRectF rect The rectangle that the robot is in.
     * @param int angle The angle that the robot is facing.
     * @param bool player Whether the robot is a player or not.
     * @param MyItem *parent The parent of the robot.
     */
    Robot(int x, int y, int angle = 0, bool player = false, QGraphicsItem *parent = nullptr);

    /* The constructor used to create a new Robot based off of another robot.
     * @param Robot *robot The robot that this robot is based off of.
     * @param MyItem *parent The parent of the robot.
     */
    Robot(Robot *robot, QGraphicsItem *parent = nullptr)
        : Robot(robot->MyItem::x(), robot->MyItem::y(), robot->getAngle(), robot->isPlayer(), parent) {}

    /* Method that returns whether this item is a wall or not. Always returns
     * false.
     * @return: bool false
     */
    inline bool isWall() const override { return false; }

    /* This method returns the angle that the robot is facing.
     * @return: int
     */
    inline int getAngle() { return angle; }

    /* This method returns whether the robot is a player or not.
     * @return: bool
     */
    inline bool isPlayer() { return player; }

    /* This method returns whether the robot is moving or not.
     * @return: bool
     */
    inline bool getMoving() { return moving; }

    /* This method sets the angle that the robot is facing.
     * @param int angle: The angle that the robot is facing.
     * @return: void
     */
    inline void setAngle(int newAngle) { angle = newAngle; }

    /* This method sets the player status of the robot.
     * @param bool player: Whether the robot is a player or not.
     */
    inline void setPlayer(bool newPlayer) { player = newPlayer; }

    /* This method sets the moving status of the robot.
     * @param bool moving: Whether the robot is moving or not.
     * @return: void
     */
    inline void setMoving(bool newMoving) { moving = newMoving; }

    /* This method is called when the mouse is realased after clicking the robot
     * It brings up the context menu to change the robot's parameters
     * @param QGraphicsSceneMouseEvent *event: The event that occured.
     * @return: void
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    /* Method to return the bounding rectangle of the robot.
     * This method must be implemented, otherwise the program breaks. This is due
     * to inheritance sheananigans.
     * @return: QRectF
     */
    QRectF boundingRect() const override { return rect(); }

    /* This method is used to paint the robot.
     * @param QPainter *painter: The painter object.
     * @param QStyleOptionGraphicsItem *option: The options for the painting.
     * @param QWidget *widget: The widget that the painting is occuring in.
     * Omit for global painting.
     * @return: void
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

  public slots:
    void changePlayer();
    void rotate();
    void changeIcon();
    void setSpeed();
    void setDetectionRange();
    void setDetectionAngle();
    void setTurningDirection();
};
