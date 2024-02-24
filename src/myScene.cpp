#include "myScene.h"

#include <iostream>

MyView::MyView(MyScene *scene) : QGraphicsView(scene) {
    this->scene = scene;
    this->alreadyClicked = false;
}

void MyView::mousePressEvent(QMouseEvent *e) {
    SampleWall *sampleWall = this->scene->getMenu()->getSampleWall();
    if (sampleWall->isUnderMouse() && sampleWall->isVisible()) {
        Wall *wall = new Wall(sampleWall);
        wall->setZValue(3);
        this->scene->addWall(wall);
    }

    SampleRobot *sampleRobot = this->scene->getMenu()->getSampleRobot();
    if (sampleRobot->isUnderMouse() && sampleRobot->isVisible()) {
        Robot *robot = new Robot(sampleRobot);
        robot->setZValue(3);
        this->scene->addRobot(robot);
    }

    QGraphicsView::mousePressEvent(e);
}

MyScene::MyScene(QGraphicsScene *parent) : QGraphicsScene(parent) {
    size = QSize(1280, 920);
    setSceneRect(0, 0, size.width() - 4, size.height() - 4);

    menu = new Menu;
    addItem(menu);

    menuIcon = new MenuIcon;
    addItem(menuIcon);

    QObject::connect(menuIcon, &MenuIcon::menuToggled, menu, &Menu::toggle);
}

QSize MyScene::getSize() {
    return this->size;
}

Menu *MyScene::getMenu() {
    return this->menu;
}

MenuIcon *MyScene::getMenuIcon() {
    return this->menuIcon;
}

QList<Robot *> MyScene::getPlayers() {
    return this->players;
}

QList<Robot *> MyScene::getRobots() {
    return this->robots;
}

QList<Wall *> MyScene::getWalls() {
    return this->walls;
}

void MyScene::addRobot(Robot *robot) {
    this->addItem(robot);
    if (robot->isPlayer()) {
        this->players.append(robot);
    } else {
        this->robots.append(robot);
    }
}

void MyScene::addWall(Wall *wall) {
    this->addItem(wall);
    this->walls.append(wall);
}

template<typename T, typename Func>
void QListForEach(QList<T> &list, Func fun) {
    for (auto item : list) {
        fun(item);
    }
}

void MyScene::clear() {
    std::function<void(QGraphicsItem *item)> lambda = [=](QGraphicsItem *item){this->removeItem(item);};
    QListForEach(this->players, lambda);
    this->players.clear();
    QListForEach(this->robots, lambda);
    this->robots.clear();
    QListForEach(this->walls, lambda);
    this->walls.clear();
}
