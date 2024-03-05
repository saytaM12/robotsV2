#include "menuIcon.h"

MenuIcon::MenuIcon(QGraphicsRectItem *parent) : QGraphicsRectItem(parent) {
  setAcceptHoverEvents(true);
  setCursor(Qt::PointingHandCursor);
  int iconSize = 50;
  int iconX = 40;
  int iconY = 40;
  setRect(iconX, iconY, iconSize, iconSize);
  setOpacity(0.5);
  setZValue(2);
}

void MenuIcon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    this->clicked = true;
  }
}

void MenuIcon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    if (this->clicked) {
      this->clicked = false;
      emit menuToggled();
    }
  }
}

void MenuIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *) {
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::black);
  painter->drawRoundedRect(this->rect(), this->rect().width() / 5,
                           this->rect().width() / 5);

  // math magic to make lineWidth even, whole and width / 10
  int lineWidth = std::ceil(this->rect().width() / 20.0) * 2;
  painter->setPen(
      QPen(Qt::gray, lineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->setBrush(Qt::NoBrush);

  painter->drawLine(option->rect.left() + lineWidth * 1.5,
                    option->rect.top() + this->rect().width() / 4,
                    option->rect.right() - lineWidth * 1.5,
                    option->rect.top() + this->rect().width() / 4);

  painter->drawLine(option->rect.left() + lineWidth * 1.5,
                    option->rect.top() + this->rect().width() / 2,
                    option->rect.right() - lineWidth * 1.5,
                    option->rect.top() + this->rect().width() / 2);

  painter->drawLine(option->rect.left() + lineWidth * 1.5,
                    option->rect.bottom() - this->rect().width() / 4,
                    option->rect.right() - lineWidth * 1.5,
                    option->rect.bottom() - this->rect().width() / 4);
}
