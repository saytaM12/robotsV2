#include "myScene.h"

MyScene::MyScene(QSize size, QGraphicsScene *parent)
    : QGraphicsScene(parent),
      menu(new Menu(size.width() / 5.0, size.height(), this)),
      menuIcon(new MenuIcon(this)) {

  setSceneRect(0, 0, size.width() - 4, size.height() - 4);
  QObject::connect(menuIcon, &MenuIcon::menuToggled, menu, &Menu::toggle);
}

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
  SampleRobot *sampleRobot = this->scene->getMenu()->getSampleRobot();
  if (sampleRobot->MyItem::isUnderMouse() && sampleRobot->MyItem::isVisible()) {
    QPointer<Robot> robot = new Robot(sampleRobot);
    robot->MyItem::setZValue(3);
    this->scene->addItem(robot);
  }

  SampleWall *sampleWall = this->scene->getMenu()->getSampleWall();
  if (sampleWall->MyItem::isUnderMouse() && sampleWall->MyItem::isVisible()) {
    QPointer<Wall> wall = new Wall(sampleWall);
    wall->MyItem::setZValue(3);
    this->scene->addItem(wall);
  }

  QGraphicsView::mousePressEvent(e);
}
