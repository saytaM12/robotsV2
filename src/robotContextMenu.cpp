#include "robotContextMenu.h"

RobotContextMenu::RobotContextMenu(QString name, QWidget *parent) : QMenu(name, parent) {
    QAction *rotate = new QAction(QIcon("imgs/icons/rotate.svg"), "Rotate", this);
    QObject::connect(rotate, &QAction::triggered, this, &RobotContextMenu::rotate);
    addAction(rotate);
    addSeparator();

    QAction *speed = new QAction(QIcon("imgs/icons/speed.svg"), "Set movement speed", this);
    QObject::connect(speed, &QAction::triggered, this, &RobotContextMenu::setSpeed);
    addAction(speed);
    addSeparator();

    QAction *detectionRange =
        new QAction(QIcon("imgs/icons/detectionRange.svg"), "Change detection range", this);
    QObject::connect(detectionRange, &QAction::triggered, this, &RobotContextMenu::setDetectionRange);
    addAction(detectionRange);
    addSeparator();

    QAction *detectionAngle =
        new QAction(QIcon("imgs/icons/detectionAngle.svg"), "Change detection angle", this);
    QObject::connect(detectionAngle, &QAction::triggered, this, &RobotContextMenu::setDetectionAngle);
    addAction(detectionAngle);
    addSeparator();

    QAction *turningDirection =
        new QAction(QIcon("imgs/icons/turningDirection.svg"), "Set turning direction", this);
    QObject::connect(turningDirection, &QAction::triggered, this, &RobotContextMenu::setTurningDirection);
    addAction(turningDirection);
    addSeparator();

    QAction *changeIcon = new QAction(QIcon("imgs/icons/changeIcon.svg"), "Change Icon", this);
    QObject::connect(changeIcon, &QAction::triggered, this, &RobotContextMenu::changeIcon);
    addAction(changeIcon);
}
