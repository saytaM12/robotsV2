#include "robot.h"

Robot::Robot(int x, int y, int speed, int angle, bool player, bool clockwise, int detectionAngle,
             int detectionRange, QGraphicsItem *parent)
    : MyItem(x, y, parent), texture("imgs/textures/robot15.png"), speed(speed), player(player),
      clockwise(clockwise), simulating(false), detectionRange(detectionRange), detectionAngle(detectionAngle),
      contextMenu(new RobotContextMenu(QString("hello"))) {

    setRect(0, 0, ROBOTSIZE, ROBOTSIZE);

    MyItem::setTransformOriginPoint(rect().center());
    MyItem::setRotation(angle);
    rotationLine = new QGraphicsLineItem(rect().center().x(), rect().center().y(), rect().center().x(),
                                         rect().center().y() - 100, static_cast<MyItem *>(this));
    rotationLine->setPen(Qt::NoPen);

    QObject::connect(contextMenu, &RobotContextMenu::rotate, this, [this]() {
        rotating = true;
        MyItem::grabMouse();
    });
    QObject::connect(contextMenu, &RobotContextMenu::changePlayer, this, &Robot::changePlayer);
    QObject::connect(contextMenu, &RobotContextMenu::setSpeed, this, &Robot::setSpeed);
    QObject::connect(contextMenu, &RobotContextMenu::setDetectionRange, this, &Robot::setDetectionRange);
    QObject::connect(contextMenu, &RobotContextMenu::setDetectionAngle, this, &Robot::setDetectionAngle);
    QObject::connect(contextMenu, &RobotContextMenu::setTurningDirection, this, &Robot::setTurningDirection);
    QObject::connect(contextMenu, &RobotContextMenu::changeIcon, this, &Robot::changeIcon);
}

void Robot::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    // chose whther to do the menu async or not
    /* contextMenu->exec(event->screenPos()); */
    contextMenu->popup(event->screenPos());
    return;

    MyItem::contextMenuEvent(event);
}

void Robot::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (rotating) {
        QLineF line(rotationLine->line().p1(), event->pos());
        MyItem::setRotation(-rotationLine->line().angleTo(line) + 90);
        line.setAngle(MyItem::rotation());
        line.setLength(100);
        rotationLine->setLine(line);
    }
    MyItem::mouseMoveEvent(event);
}

void Robot::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (rotating) {
        rotating = false;
        MyItem::ungrabMouse();
    }
    MyItem::mousePressEvent(event);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {

    Q_UNUSED(option);

    QImage image(texture);

    if (MyItem::isSelected()) {
        darkenImage(image);
    }

    painter->drawImage(rect(), image);
}

void Robot::gameTick() {
    if (player) {
        return;
    }

    if (simulating) {
        qreal r = MyItem::rotation();
        r = r < 0 ? 360 + r : r;
        r = 360 - r;
        qreal dx = speed * sin(r * M_PI / 180.0);
        qreal dy = speed * cos(r * M_PI / 180.0);
        MyItem::setX(MyItem::x() - dx);
        MyItem::setY(MyItem::y() - dy);
    }
}

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
