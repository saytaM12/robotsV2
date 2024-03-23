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

