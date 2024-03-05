#include "menu.h"

Menu::Menu(QGraphicsRectItem *parent) : QGraphicsRectItem(parent) {

  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsSelectable);
  QGraphicsRectItem::setCursor(Qt::ArrowCursor);

  QSize windowSize(1280, 920);

  int menuWidth = windowSize.width() / 4.0;
  int menuHeight = windowSize.height();
  int buttonWidth = menuWidth / 3.0;
  int buttonHeight = menuWidth / 5.0;
  int sampleSize = menuWidth * SCALER;

  setRect(POS, 0, menuWidth, menuHeight);
  setZValue(1);

  saveButton = new MyButton("Save", this);
  int saveButtonX = POS + menuWidth / 9.0;
  int saveButtonY = menuHeight - buttonHeight - 30;
  saveButton->setRect(saveButtonX, saveButtonY, buttonWidth, buttonHeight);
  QObject::connect(saveButton, &MyButton::pressed, this, &Menu::savePressed);

  loadButton = new MyButton("Load", this);
  int loadButtonX = saveButtonX + buttonWidth + menuWidth / 9.0;
  int loadButtonY = saveButtonY;
  loadButton->setRect(loadButtonX, loadButtonY, buttonWidth, buttonHeight);
  QObject::connect(loadButton, &MyButton::pressed, this, &Menu::loadPressed);

  sampleRobot = new SampleRobot(POS + menuWidth / 2.0 - ROBOTSIZE / 2.0,
                                menuHeight - buttonHeight - 60 - sampleSize -
                                    (menuWidth - sampleSize) / 2.0 -
                                    sampleSize / 2.0 - ROBOTSIZE / 2.0,
                                0, false);
  sampleRobot->MyItem::setParentItem(this);

  sampleWall = new SampleWall(
      POS + menuWidth / 2.0 - 50,
      menuHeight - buttonHeight - 60 - sampleSize / 2.0 - 50, 100);
  sampleWall->MyItem::setParentItem(this);

  QGraphicsRectItem::setVisible(false);
}

void Menu::toggle() {
  QGraphicsRectItem::setVisible(!QGraphicsRectItem::isVisible());
  QGraphicsRectItem::update();
}

SampleRobot *Menu::getSampleRobot() { return this->sampleRobot; }

SampleWall *Menu::getSampleWall() { return this->sampleWall; }

void Menu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *) {
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::gray);
  painter->drawRect(option->rect);

  int buttonHeight = option->rect.width() / 5.0;
  int sampleSize = option->rect.width() * SCALER;
  int samplePadding = (option->rect.width() - sampleSize) / 2.0;
  painter->setBrush(Qt::darkGray);
  painter->drawRect(option->rect.x() + samplePadding,
                    option->rect.bottom() - buttonHeight - 60 - sampleSize * 2 -
                        samplePadding,
                    sampleSize, sampleSize);
  painter->drawRect(option->rect.x() + samplePadding,
                    option->rect.bottom() - buttonHeight - 60 - sampleSize,
                    sampleSize, sampleSize);
}
