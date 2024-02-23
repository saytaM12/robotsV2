#include "myScene.h"

MyScene::MyScene(QGraphicsScene *parent) : QGraphicsScene(parent) {
    size = QSize(1280, 920);
    setSceneRect(0, 0, size.width() - 4, size.height() - 4);

    menu = new Menu;
    addItem(menu);

    menuIcon = new MenuIcon;
    addItem(menuIcon);

    QObject::connect(menuIcon, &MenuIcon::menuToggled, menu, &Menu::toggle);
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

void MyScene::newItem(Robot *robot) {
    this->addItem(robot);
    if (robot->isPlayer()) {
        this->players.append(robot);
    } else {
        this->robots.append(robot);
    }
}

void MyScene::newItem(Wall *wall) {
    this->addItem(wall);
    this->walls.append(wall);
}

void MyScene::clear() {
    qsizetype playersLen = this->players.size();
    for (qsizetype i = 0; i < playersLen; i++) {
        this->removeItem(this->players.at(i));
    }
    this->players.clear();

    qsizetype robotsLen = this->robots.size();
    for (qsizetype i = 0; i < robotsLen; i++) {
        this->removeItem(this->robots.at(i));
    }
    this->robots.clear();

    qsizetype wallsLen = this->walls.size();
    for (qsizetype i = 0; i < wallsLen; i++) {
        this->removeItem(this->walls.at(i));
    }
    this->walls.clear();
}
