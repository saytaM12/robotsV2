#include "myScene.h"

MyView::MyView(MyScene *scene) : QGraphicsView(scene) { this->scene = scene; }

void MyView::mousePressEvent(QMouseEvent *e) {
  SampleWall *sampleWall = this->scene->getMenu()->getSampleWall();
  if (sampleWall->MyItem::isUnderMouse() && sampleWall->MyItem::isVisible()) {
    QPointer<Wall> wall = new Wall(sampleWall);
    wall->MyItem::setZValue(3);
    this->scene->addItem(wall);
  }

  SampleRobot *sampleRobot = this->scene->getMenu()->getSampleRobot();
  if (sampleRobot->MyItem::isUnderMouse() && sampleRobot->MyItem::isVisible()) {
    QPointer<Robot> robot = new Robot(sampleRobot);
    robot->MyItem::setZValue(3);
    this->scene->addItem(robot);
  }

  QGraphicsView::mousePressEvent(e);
}

MyScene::MyScene(QGraphicsScene *parent) : QGraphicsScene(parent) {
  size = QSize(1280, 920);
  setSceneRect(0, 0, size.width() - 4, size.height() - 4);

  menu = new Menu;
  QGraphicsScene::addItem(menu);

  menuIcon = new MenuIcon;
  QGraphicsScene::addItem(menuIcon);

  QObject::connect(menuIcon, &MenuIcon::menuToggled, menu, &Menu::toggle);
}

QSize MyScene::getSize() { return this->size; }

Menu *MyScene::getMenu() { return this->menu; }

MenuIcon *MyScene::getMenuIcon() { return this->menuIcon; }

QList<QPointer<MyItem>> MyScene::getItems() { return this->items; }

void MyScene::addItem(MyItem *item) {
  this->items.push_back(item);
  this->QGraphicsScene::addItem(item);
  QObject::connect(item, &MyItem::mouseReleased, this, &MyScene::itemDropped);
}

void MyScene::clear() {
  for (MyItem *item : this->items) {
    this->removeItem(item);
  }
  this->items.clear();
}

void MyScene::itemDropped(MyItem *item) {
  if (this->menu->isUnderMouse() &&
      this->menu->QGraphicsRectItem::isVisible()) {
    this->items.removeOne(item);
    this->removeItem(item);
    // delete item;
  }
}
