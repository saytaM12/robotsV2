/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 */
#include "myScene.h"

MyScene::MyScene(QSize size, QGraphicsScene *parent)
    : QGraphicsScene(parent), simulating(false), menu(new Menu(size.width() / 5.0, size.height(), this)),
      menuIcon(new MenuIcon(this)), gameTickTimer(new QTimer(this)) {

    setSceneRect(0, 0, size.width() - 4, size.height() - 4);
    setBackgroundBrush(QBrush(QImage("imgs/textures/background.png")));
    QObject::connect(menuIcon, &MenuIcon::menuToggled, menu, &Menu::toggle);

    QObject::connect(menu, &Menu::simulationPressed, this, &MyScene::simulationPressed);

    QObject::connect(gameTickTimer, &QTimer::timeout, this, &MyScene::gameTick);
}

QList<MyItem *> MyScene::items() const {
    QList<MyItem *> returnItems;
    for (MyItem *item : itemList) {
        returnItems.push_back(item);
    }
    return returnItems;
}

void MyScene::addItem(MyItem *item) {
    itemList.push_back(item);
    QGraphicsScene::addItem(item);
    QObject::connect(item, &MyItem::mouseReleased, this, &MyScene::itemDropped);
}

void MyScene::clear() {
    for (MyItem *item : itemList) {
        removeItem(item);
        delete item;
    }
    itemList.clear();
}

void MyScene::itemDropped() {
    MyItem *item = static_cast<MyItem *>(sender());

    getMenu()->getSampleRobot()->MyItem::setVisible(true);
    getMenu()->getSampleWall()->MyItem::setVisible(true);

    if (menu->QGraphicsRectItem::isUnderMouse() && menu->QGraphicsRectItem::isVisible()) {
        itemList.removeOne(item);
        removeItem(item);
        delete item;
    }
}

void MyScene::simulationPressed() {

    simulating = !simulating;

    if (simulating) {
        gameTickTimer->start(1000 / 60);
        menu->toggle();
    } else {
        gameTickTimer->stop();
    }
}

void MyScene::ensureOnePlayer(int player) {
    Robot *robot = static_cast<Robot *>(sender());

    if (player == 1) {
        if (player1 == NULL) {
            player1 = robot;
        }
        if (robot == player1) {
            return;
        }

        player1->setPlayer(0);
        player1 = robot;
    }

    if (player == 2) {
        if (player2 == NULL) {
            player2 = robot;
        }
        if (robot == player2) {
            return;
        }

        player2->setPlayer(0);
        player2 = robot;
    }
}

bool MyScene::detectObjects() {
    Robot *robot = static_cast<Robot *>(sender());

    QGraphicsPathItem *pathItem = new QGraphicsPathItem;
    QPainterPath path;

    path.addRoundedRect(-ROBOTSIZE / 2.0, -robot->getDetectionRange(), ROBOTSIZE, robot->getDetectionRange(),
                        ROBOTSIZE / 2.0, ROBOTSIZE / 2.0);

    QTransform t;
    t.translate(robot->MyItem::x() + ROBOTSIZE / 2.0, robot->MyItem::y() + ROBOTSIZE / 2.0);
    t.rotate(-robot->getAngle());
    path = t.map(path);

    pathItem->setPath(path);

    if (!sceneRect().contains(pathItem->boundingRect())) {
        return true;
    }

    QGraphicsScene::addItem(pathItem);
    QList<QGraphicsItem *> colItems = pathItem->collidingItems();
    removeItem(pathItem);
    delete pathItem;

    colItems.removeAll(static_cast<MyItem *>(robot));

    for (QGraphicsItem *colItem : colItems) {
        if (items().contains(static_cast<MyItem *>(colItem))) {
            return true;
        }
    }

    return false;
}

MyView::MyView(MyScene *scene) : QGraphicsView(scene), scene(scene) {
    setDragMode(QGraphicsView::RubberBandDrag);
    setMinimumSize(scene->getWidth(), scene->getHeight());
    setMaximumSize(scene->getWidth(), scene->getHeight());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MyView::mousePressEvent(QMouseEvent *e) {

    if (e->button() != Qt::LeftButton) {
        if (e->buttons().testFlag(Qt::LeftButton)) {
            QGraphicsView::mousePressEvent(e);
        }
        return;
    }

    SampleRobot *sampleRobot = scene->getMenu()->getSampleRobot();
    if (sampleRobot->MyItem::isUnderMouse() && sampleRobot->MyItem::isVisible()) {
        sampleRobot->MyItem::setVisible(false);
        QPointer<Robot> robot = new Robot(sampleRobot);
        QObject::connect(scene, &MyScene::gameTick, robot, &Robot::gameTick);
        QObject::connect(robot, &Robot::playerChanged, scene, &MyScene::ensureOnePlayer);
        QObject::connect(robot, &Robot::detectObjects, scene, &MyScene::detectObjects);
        robot->MyItem::setZValue(0);
        scene->addItem(robot);
    }

    SampleWall *sampleWall = scene->getMenu()->getSampleWall();
    if (sampleWall->MyItem::isUnderMouse() && sampleWall->MyItem::isVisible()) {
        sampleWall->MyItem::setVisible(false);
        QPointer<Wall> wall = new Wall(sampleWall);
        wall->MyItem::setZValue(0);
        scene->addItem(wall);
    }

    QGraphicsView::mousePressEvent(e);
}

void setPlayerMovement(MyScene *scene, QKeyEvent *e, bool set) {
    switch (e->key()) {
    case Qt::Key_Left:
        if (scene->getPlayer1()) {
            scene->getPlayer1()->playerSetMove(turnLeft, set);
        }
        break;
    case Qt::Key_Down:
        if (scene->getPlayer1()) {
            scene->getPlayer1()->playerSetMove(moveBack, set);
        }
        break;
    case Qt::Key_Up:
        if (scene->getPlayer1()) {
            scene->getPlayer1()->playerSetMove(moveForward, set);
        }
        break;
    case Qt::Key_Right:
        if (scene->getPlayer1()) {
            scene->getPlayer1()->playerSetMove(turnRight, set);
        }
        break;
    case Qt::Key_A:
        if (scene->getPlayer2()) {
            scene->getPlayer2()->playerSetMove(turnLeft, set);
        }
        break;
    case Qt::Key_S:
        if (scene->getPlayer2()) {
            scene->getPlayer2()->playerSetMove(moveBack, set);
        }
        break;
    case Qt::Key_W:
        if (scene->getPlayer2()) {
            scene->getPlayer2()->playerSetMove(moveForward, set);
        }
        break;
    case Qt::Key_D:
        if (scene->getPlayer2()) {
            scene->getPlayer2()->playerSetMove(turnRight, set);
        }
        break;
    default:
        break;
    }
}

void MyView::keyPressEvent(QKeyEvent *e) { setPlayerMovement(scene, e, true); }

void MyView::keyReleaseEvent(QKeyEvent *e) { setPlayerMovement(scene, e, false); }
