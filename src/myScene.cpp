#include "myScene.h"

MyScene::MyScene(QSize size, QGraphicsScene *parent)
    : QGraphicsScene(parent), menu(new Menu(size.width() / 5.0, size.height(), this)),
      menuIcon(new MenuIcon(this)) {

    setSceneRect(0, 0, size.width() - 4, size.height() - 4);
    setBackgroundBrush(QBrush(QColor(35, 35, 35)));
    QObject::connect(menuIcon, &MenuIcon::menuToggled, menu, &Menu::toggle);
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
    if (menu->isUnderMouse() && menu->QGraphicsRectItem::isVisible()) {
        itemList.removeOne(item);
        removeItem(item);
        delete item;
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
        QGraphicsView::mousePressEvent(e);
        return;
    }
    SampleRobot *sampleRobot = scene->getMenu()->getSampleRobot();
    if (sampleRobot->MyItem::isUnderMouse() && sampleRobot->MyItem::isVisible()) {
        QPointer<Robot> robot = new Robot(sampleRobot);
        robot->MyItem::setZValue(3);
        scene->addItem(robot);
    }

    SampleWall *sampleWall = scene->getMenu()->getSampleWall();
    if (sampleWall->MyItem::isUnderMouse() && sampleWall->MyItem::isVisible()) {
        QPointer<Wall> wall = new Wall(sampleWall);
        wall->MyItem::setZValue(3);
        scene->addItem(wall);
    }

    QGraphicsView::mousePressEvent(e);
}
