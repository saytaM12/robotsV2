/*
 * Autors Milan Vrbas (xvrbas01), Matyáš Oujezdský (xoujz04)
 * ICP 2024
 */
#include "robot.h"

Robot::Robot(qreal x, qreal y, int speed, qreal angle, int player, bool clockwise, int detectionAngle,
             int detectionRange, QGraphicsItem *parent)
    : MyItem(x, y, parent), texture("imgs/textures/robot15.png"), speed(speed), player(player),
      clockwise(clockwise), detectionRange(detectionRange), detectionAngle(detectionAngle), playerMoving(0),
      contextMenu(new RobotContextMenu(QString("hello"))) {

    setRect(0, 0, ROBOTSIZE, ROBOTSIZE);
    MyItem::setTransformOriginPoint(rect().center());
    MyItem::setRotation(-angle);

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

void Robot::playerSetMove(Direction direction, bool set) {
    switch (direction) {
    case turnLeft:
        if (set) {
            playerMoving |= 0b1000;
        } else {
            playerMoving &= 0b0111;
        }
        break;
    case moveBack:
        if (set) {
            playerMoving |= 0b0100;
        } else {
            playerMoving &= 0b1011;
        }
        break;
    case moveForward:
        if (set) {
            playerMoving |= 0b0010;
        } else {
            playerMoving &= 0b1101;
        }
        break;
    case turnRight:
        if (set) {
            playerMoving |= 0b0001;
        } else {
            playerMoving &= 0b1110;
        }
    default:
        break;
    }
}

void Robot::gameTick() {
    qreal r = 360 - MyItem::rotation();
    qreal dx = speed * sin(r * M_PI / 180.0);
    qreal dy = speed * cos(r * M_PI / 180.0);

    if (player) {
        if (playerMoving & 0b1000) {
            MyItem::setRotation(MyItem::rotation() - detectionAngle * (clockwise ? -1 : 1));
        }
        if (playerMoving & 0b0100) {
            MyItem::setX(MyItem::x() + dx);
            MyItem::setY(MyItem::y() + dy);
        }
        if (playerMoving & 0b0010) {
            MyItem::setX(MyItem::x() - dx);
            MyItem::setY(MyItem::y() - dy);
        }
        if (playerMoving & 0b0001) {
            MyItem::setRotation(MyItem::rotation() + detectionAngle * (clockwise ? 1 : -1));
        }

        return;
    }

    if (emit detectObjects()) {
        MyItem::setRotation(MyItem::rotation() + detectionAngle * (clockwise ? -1 : 1));
        return;
    }

    MyItem::setX(MyItem::x() - dx);
    MyItem::setY(MyItem::y() - dy);
}

void Robot::changePlayer() {
    QDialog dialog;
    QGridLayout layout(&dialog);

    QLabel label(player ? QString("Currenttely this robot is set to be player %1").arg(player)
                        : (QString("Currenttely this robot is set to be autonomous")));
    layout.addWidget(&label, 0, 0, 1, 2);

    QPointer<QPushButton> buttonPlayer = new QPushButton();
    buttonPlayer->setText("Set the Robot to be Player Controlled");
    layout.addWidget(buttonPlayer, 1, 0);

    QPointer<QPushButton> buttonNonPlayer = new QPushButton();
    buttonNonPlayer->setText("Set the Robot to be Autonomous");
    layout.addWidget(buttonNonPlayer, 1, 1);

    QObject::connect(buttonPlayer, &QPushButton::clicked, [&dialog, this]() {
        dialog.accept();

        QDialog dialog2;
        QGridLayout layout2(&dialog2);

        QLabel label2("Which player should this robot be controlled by?");
        layout2.addWidget(&label2, 0, 0, 1, 2);

        QPointer<QPushButton> buttonPlayer1 = new QPushButton();
        buttonPlayer1->setText("This is player 1");
        layout2.addWidget(buttonPlayer1, 1, 0);

        QPointer<QPushButton> buttonPlayer2 = new QPushButton();
        buttonPlayer2->setText("This is player 2");
        layout2.addWidget(buttonPlayer2, 1, 1);

        QObject::connect(buttonPlayer1, &QPushButton::clicked, [&dialog2, this]() {
            dialog2.accept();
            player = 1;
            emit playerChanged(1);
        });

        QObject::connect(buttonPlayer2, &QPushButton::clicked, [&dialog2, this]() {
            dialog2.accept();
            player = 2;
            emit playerChanged(2);
        });

        dialog2.exec();
    });

    QObject::connect(buttonNonPlayer, &QPushButton::clicked, [&dialog, this]() {
        dialog.accept();
        player = 0;
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
