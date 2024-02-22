#include "myButton.h"

MyButton::MyButton(QString string, QGraphicsRectItem *parent) : QGraphicsRectItem(parent) {

    this->setCursor(Qt::PointingHandCursor);

    this->clicked = false;
    this->string = string;
}

void MyButton::mousePressEvent(QGraphicsSceneMouseEvent *) {
    this->clicked = true;
}

void MyButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
    if (this->clicked) {
        this->clicked = false;
        emit pressed();
    }
}

void MyButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawRoundedRect(option->rect, option->rect.height() / 4.5, option->rect.height() / 4.5);

    painter->setFont(QFont(QString("Arial"), option->rect.height() * (1.0/3.0)));
    painter->drawText(option->rect, this->string, QTextOption(Qt::AlignCenter));
}
