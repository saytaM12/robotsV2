#include "menu.h"

MyButton::MyButton(QRectF rect, QString string, Menu *menu)
    : QGraphicsRectItem(menu), string(string) {

  setCursor(Qt::PointingHandCursor);
  setX(rect.x());
  setY(rect.y());
  setRect(0, 0, rect.width(), rect.height());
}

void MyButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *) {
  painter->setPen(Qt::black);
  painter->setBrush(Qt::white);
  painter->drawRoundedRect(option->rect, option->rect.height() / 4.5,
                           option->rect.height() / 4.5);

  painter->setFont(QFont(QString("Arial"), option->rect.height() / 3.0));
  painter->drawText(option->rect, this->string, QTextOption(Qt::AlignCenter));
}

Menu::Menu(int menuWidth, int menuHeight, QGraphicsScene *parent)
    : QGraphicsRectItem(),
      saveButton(
          new MyButton(LEFT_BUTTON_RECT(menuWidth, menuHeight), "Save", this)),
      loadButton(
          new MyButton(RIGHT_BUTTON_RECT(menuWidth, menuHeight), "Load", this)),
      sampleWall(new SampleWall(SAMPLE_WALL_RECT(menuWidth, menuHeight), this)),
      sampleRobot(new SampleRobot(SAMPLE_ROBOT_TOPLEFT(menuWidth, menuHeight),
                                  0, false, this)) {

  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsSelectable);

  QObject::connect(saveButton, &MyButton::pressed, this, &Menu::savePressed);
  QObject::connect(loadButton, &MyButton::pressed, this, &Menu::loadPressed);

  setX(0);
  setY(0);
  setRect(0, 0, menuWidth, menuHeight);
  setZValue(1);

  parent->addItem(this);
  QGraphicsRectItem::setVisible(false);
}

void Menu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *) {
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::gray);
  painter->drawRect(option->rect);

  painter->setBrush(Qt::darkGray);
  painter->drawRect(
      TOP_SAMPLE_BACKGROUND_RECT(option->rect.width(), option->rect.height()));
  painter->drawRect(
      BOT_SAMPLE_BACKGROUND_RECT(option->rect.width(), option->rect.height()));
}
