#include "menuIcon.h"

MenuIcon::MenuIcon(QGraphicsScene *parent) : QGraphicsRectItem() {
    parent->addItem(this);
    setAcceptHoverEvents(true);
    setCursor(Qt::PointingHandCursor);
    setRect(40, 40, 50, 50);
    setOpacity(0.5);
    setZValue(2);
}

void MenuIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawRoundedRect(this->rect(), this->rect().width() / 5, this->rect().width() / 5);

    // math magic to make lineWidth even, whole and width / 10
    int lineWidth = std::ceil(this->rect().width() / 20.0) * 2;
    painter->setPen(QPen(Qt::gray, lineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::NoBrush);

    painter->drawLine(option->rect.left() + lineWidth * 1.5, option->rect.top() + this->rect().width() / 4,
                      option->rect.right() - lineWidth * 1.5, option->rect.top() + this->rect().width() / 4);

    painter->drawLine(option->rect.left() + lineWidth * 1.5, option->rect.top() + this->rect().width() / 2,
                      option->rect.right() - lineWidth * 1.5, option->rect.top() + this->rect().width() / 2);

    painter->drawLine(option->rect.left() + lineWidth * 1.5, option->rect.bottom() - this->rect().width() / 4,
                      option->rect.right() - lineWidth * 1.5, option->rect.bottom() - this->rect().width() / 4);
}
