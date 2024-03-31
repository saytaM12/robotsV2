#include "robot.h"

Robot::Robot(int x, int y, int angle, bool player, QGraphicsItem *parent)
    : MyItem(x, y, parent), texture("imgs/textures/robot15.png"), angle(angle), speed(1), moving(false),
      player(player), clockwise(false), detectionRange(100), detectionAngle(1),
      rotatingLine(new RobotRotateLine(ROBOTSIZE / 2.0, ROBOTSIZE / 2.0, ROBOTSIZE / 2.0, 0,
                                       static_cast<MyItem *>(this))),
      contextMenu(new RobotContextMenu(QString("hello"))) {

    setRect(0, 0, ROBOTSIZE, ROBOTSIZE);

    rotatingLine->setVisible(false);
    QObject::connect(rotatingLine, &RobotRotateLine::rotated, this, &Robot::rotate);
    QObject::connect(rotatingLine, &RobotRotateLine::mouseRelease, this, &Robot::rotateEnd);

    QObject::connect(contextMenu, &RobotContextMenu::changePlayer, this, &Robot::changePlayer);
    QObject::connect(contextMenu, &RobotContextMenu::rotate, this, &Robot::rotateStart);
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
    return;

    MyItem::contextMenuEvent(event);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    QImage image(texture);

    if (MyItem::isSelected()) {
        darkenImage(image);
    }

    painter->translate(ROBOTSIZE / 2.0, ROBOTSIZE / 2.0);
    painter->rotate(-angle);
    painter->translate(-ROBOTSIZE / 2.0, -ROBOTSIZE / 2.0);

    painter->drawImage(option->rect, image);

    MyItem::update();
}

void Robot::rotateStart() { rotatingLine->setVisible(true); }

void Robot::rotate() {
    angle = rotatingLine->line().angle() - 90;
    angle = angle < 0 ? 360 + angle : angle;
}

void Robot::rotateEnd() { rotatingLine->setVisible(false); }

void Robot::changePlayer() {
    QDialog dialog;
    QGridLayout layout(&dialog);

    QLabel label(
        QString("Currenttely this robot is set to be %1").arg(player ? "player controlled" : "autonomous"));
    layout.addWidget(&label, 0, 0, 1, 2);

    QPointer<QPushButton> buttonPlayer = new QPushButton();
    buttonPlayer->setText("Set the Robot to be Player Controlled");
    layout.addWidget(buttonPlayer, 1, 0);
    QObject::connect(buttonPlayer, &QPushButton::clicked, [&dialog, this]() {
        dialog.accept();
        player = true;
    });

    QPointer<QPushButton> buttonNonPlayer = new QPushButton();
    buttonNonPlayer->setText("Set the Robot to be Autonomous");
    layout.addWidget(buttonNonPlayer, 1, 1);
    QObject::connect(buttonNonPlayer, &QPushButton::clicked, [&dialog, this]() {
        dialog.accept();
        player = false;
    });

    dialog.exec();
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

void Robot::setSpeed() {
    setParametersWithDialog(("Set the speed of the robot: "),
                            ("Speed indicates how many pixels the robot will move per frame.\n\n"
                             ""
                             "Minimum is 0 (no movement).\n"
                             "Maximum is effectively infinite"),
                            0, 0, speed);
}

void Robot::setDetectionRange() {
    setParametersWithDialog(
        ("Set the detection range of the robot: "),
        ("Detection range indicates how many pixels forward can the robot detect an obstacle\n\n"
         ""
         "When an autonomous robot detects an obstacle it turns in the direction of\n"
         "'turning direction' by 'detection angle' degrees\n\n"
         ""
         "When a player controlled robot detects an obstacle it stops accepting forward movement\n\n"
         ""
         "Minimum is 0 (no detection).\n"
         "Maximum is effectively infinite"),
        0, 0, detectionRange);
}
void Robot::setDetectionAngle() {
    setParametersWithDialog(
        ("Set the detection angle of the robot: "),
        ("Detection angle indivates by how many degrees the robot turns\nwhen it detects an "
         "obstacle in 'detection Range'\n\n"
         ""
         "Minimum is 0 (no turning).\n"
         "Maximum is 360 (back to no turning)"),
        0, 360, detectionAngle);
}
void Robot::setTurningDirection() {
    setParametersWithDialog(("Set the turning direction of the robot: "),
                            ("Turning Direction indicates wheter the robot turns clockwise\n"
                             "or counter clockwise when detecting an obstacle\n"
                             "1 means clockwise, 0 means counter clockwise\n"),
                            0, 1, clockwise);
}
