#include "editPanel.h"

MenuIcon::MenuIcon(QGraphicsRectItem *parent) : QGraphicsRectItem(parent) {
    setAcceptHoverEvents(true);
    setCursor(Qt::PointingHandCursor);
    pos = 20;
    size = 50;
    setRect(pos, pos, size, size);
}

void MenuIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::Dense4Pattern);
    painter->drawRoundedRect(this->rect(), size / 5, size / 5);

    int lineWidth = std::ceil(this->size / 20.0) * 2; // math magic to make width even, whole and size / 10
    painter->setPen(QPen(Qt::gray, lineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::NoBrush);

    painter->drawLine(option->rect.left() + lineWidth / 5, option->rect.top() + this->size / 4,
                      option->rect.right() - lineWidth / 5, option->rect.top() + this->size / 4);

    painter->drawLine(option->rect.left() + lineWidth / 5, option->rect.top() + this->size / 2,
                      option->rect.right() - lineWidth / 5, option->rect.top() + this->size / 2);

    painter->drawLine(option->rect.left() + lineWidth / 5, option->rect.bottom() - this->size / 4,
                      option->rect.right() - lineWidth / 5, option->rect.bottom() - this->size / 4);
}
