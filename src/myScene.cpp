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

void MyScene::newItem(QGraphicsItem *item) {
    this->addItem(item);
    this->items.append(item);
}

void MyScene::clear() {
    qsizetype listSize = this->items.size();
    for (qsizetype i = 0; i < listSize; i++) {
        this->removeItem(this->items.at(i));
    }
    this->items.clear();
}
