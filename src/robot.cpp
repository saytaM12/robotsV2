#include "robot.h"

Robot::Robot(int x, int y, int angle, bool player, QGraphicsItem *parent)
    : MyItem(x, y, parent), texture("imgs/textures/robot15.png"), rotating(false), angle(angle), player(player),
      moving(false), contextMenu(new RobotContextMenu(QString("hello"))) {
    setRect(0, 0, ROBOTSIZE, ROBOTSIZE);

    QObject::connect(contextMenu, &RobotContextMenu::rotate, this, &Robot::rotate);
    QObject::connect(contextMenu, &RobotContextMenu::changeIcon, this, &Robot::changeIcon);
    QObject::connect(contextMenu, &RobotContextMenu::setSpeed, this, &Robot::setSpeed);
    QObject::connect(contextMenu, &RobotContextMenu::setDetectionRange, this, &Robot::setDetectionRange);
    QObject::connect(contextMenu, &RobotContextMenu::setDetectionAngle, this, &Robot::setDetectionAngle);
    QObject::connect(contextMenu, &RobotContextMenu::setTurningDirection, this, &Robot::setTurningDirection);
}

void Robot::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

    // chose whther to do the menu async or not
    /* contextMenu->exec(event->screenPos()); */
    contextMenu->popup(event->screenPos());

    player = !player;
    MyItem::update();
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {

    QImage image(texture);

    if (MyItem::isSelected()) {
        darkenImage(image);
    }

    painter->drawImage(option->rect, image);
}

void Robot::rotate() { rotating = true; }
void Robot::changeIcon() {
    /* Create a dialog with options to select a new icon */
    QDialog dialog;
    dialog.setWindowFlags(Qt::Popup);
    QGridLayout layout(&dialog);

    /* Populate the dialog with icons */
    for (int i = 0; i < 24; i++) {
        QString iconPath = QString("imgs/textures/robot%1.png").arg(i + 1);
        QIcon icon(iconPath);

        QPointer<QPushButton> button = new QPushButton();
        button->setIcon(icon);
        button->setIconSize(QSize(80, 80));

        layout.addWidget(button, i / 6, i % 6);

        /* Link a button click to setting the texture */
        QObject::connect(button, &QPushButton::clicked, [iconPath, &dialog, this]() {
            texture = iconPath;
            dialog.accept();
            MyItem::setSelected(false);
            MyItem::update();
        });
    }

    /* Show the dialog */
    dialog.exec();
}

void Robot::setSpeed() {
    setParametersWithDialog(("Set the speed of the robot: "),
                            ("Speed indicates how many pixels the robot will move per frame.\n"
                             "Minimum is 0 (no movement).\n"
                             "There is no maximum, use common sense."),
                            speed);
}

void Robot::setDetectionRange() {
    setParametersWithDialog(
        ("Set the detection range of the robot: "),
        ("Detection range indicates how many pixels forward can the robot detect an obstacle\nWhen an "
         "autonomous robot detects an obstacle it turns in the direction of 'turning direction' by 'detection "
         "angle'\nWhen a player controlled robot detects an obstacle it stops accepting forward "
         "movement\nMinimum is 0 (no detection).\nThere is no maximum number, but effectively its' anything "
         "larger than the screen size"),
        detectionRange);
}
void Robot::setDetectionAngle() {
    setParametersWithDialog(("Set the detection angle of the robot: "), ("TODO"), detectionAngle);
}
void Robot::setTurningDirection() {
    setParametersWithDialog(("Set the turning direction of the robot: "), ("TODO"), clockwise);
}
