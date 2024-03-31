#include "robotUtils.h"

RobotRotateLine::RobotRotateLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent)
    : QGraphicsLineItem(x1, y1, x2, y2, parent) {

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setPen(QPen(Qt::yellow, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setCursor(Qt::CrossCursor);
}

void RobotRotateLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qreal angle =
        atan2(-(event->pos().y() - ROBOTSIZE / 2.0), event->pos().x() - ROBOTSIZE / 2.0) * 180 / M_PI;

    QLineF newLine(line());
    newLine.setAngle(angle);

    this->setLine(newLine);

    update();

    emit rotated();
    QGraphicsLineItem::mouseMoveEvent(event);
}

void RobotRotateLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit mouseRelease();
    QGraphicsLineItem::mouseReleaseEvent(event);
}

RobotContextMenu::RobotContextMenu(QString name, QWidget *parent) : QMenu(name, parent) {
    QAction *changePlayer = new QAction(QIcon("imgs/icons/player.svg"), "Set robot type", this);
    QObject::connect(changePlayer, &QAction::triggered, this, &RobotContextMenu::changePlayer);
    addAction(changePlayer);
    addSeparator();

    QAction *rotate = new QAction(QIcon("imgs/icons/rotate.svg"), "Rotate", this);
    QObject::connect(rotate, &QAction::triggered, this, &RobotContextMenu::rotate);
    addAction(rotate);
    addSeparator();

    QAction *speed = new QAction(QIcon("imgs/icons/speed.svg"), "Set movement speed", this);
    QObject::connect(speed, &QAction::triggered, this, &RobotContextMenu::setSpeed);
    addAction(speed);
    addSeparator();

    QAction *detectionRange = new QAction(QIcon("imgs/icons/detectionRange.svg"), "Set detection range", this);
    QObject::connect(detectionRange, &QAction::triggered, this, &RobotContextMenu::setDetectionRange);
    addAction(detectionRange);
    addSeparator();

    QAction *detectionAngle = new QAction(QIcon("imgs/icons/detectionAngle.svg"), "Set detection angle", this);
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
