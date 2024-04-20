#include "myScene.h"
#include "qnamespace.h"

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

void MyScene::itemDropped(MyItem *item) {
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

void MyScene::ensureOnePlayer(Robot *robot, int player) {
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
            scene->getPlayer1()->playerMove(turnLeft, set);
        }
        break;
    case Qt::Key_Down:
        if (scene->getPlayer1()) {
            scene->getPlayer1()->playerMove(moveBack, set);
        }
        break;
    case Qt::Key_Up:
        if (scene->getPlayer1()) {
            scene->getPlayer1()->playerMove(moveForward, set);
        }
        break;
    case Qt::Key_Right:
        if (scene->getPlayer1()) {
            scene->getPlayer1()->playerMove(turnRight, set);
        }
        break;
    case Qt::Key_A:
        if (scene->getPlayer2()) {
            scene->getPlayer2()->playerMove(turnLeft, set);
        }
        break;
    case Qt::Key_S:
        if (scene->getPlayer2()) {
            scene->getPlayer2()->playerMove(moveBack, set);
        }
        break;
    case Qt::Key_W:
        if (scene->getPlayer2()) {
            scene->getPlayer2()->playerMove(moveForward, set);
        }
        break;
    case Qt::Key_D:
        if (scene->getPlayer2()) {
            scene->getPlayer2()->playerMove(turnRight, set);
        }
        break;
    default:
        break;
    }
}

void MyView::keyPressEvent(QKeyEvent *e) { setPlayerMovement(scene, e, true); }

void MyView::keyReleaseEvent(QKeyEvent *e) { setPlayerMovement(scene, e, false); }
