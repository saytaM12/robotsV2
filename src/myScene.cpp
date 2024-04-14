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

QList<MyItem *> MyScene::items() {
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

    for (MyItem *item : itemList) {
        if (!item->isWall()) {
            static_cast<Robot *>(item)->setMoving(simulating);
        }
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
