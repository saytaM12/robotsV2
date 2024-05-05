/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 *
 * This module contains the implementation of the MenuIcon class.
 */
#include "menuIcon.h"

MenuIcon::MenuIcon(QGraphicsScene *parent) : QGraphicsRectItem(), menuUp(false) {
    parent->addItem(this);
    setAcceptHoverEvents(true);
    setCursor(Qt::PointingHandCursor);
    setRect(40, 40, 50, 50);
    setOpacity(0.5);
    setZValue(2);
}

void MenuIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(menuUp ? Qt::lightGray : Qt::black);
    painter->drawRoundedRect(rect(), rect().width() / 5, rect().width() / 5);

    // math magic to make lineWidth even, whole and width / 10
    int lineWidth = ceil(rect().width() / 20.0) * 2;
    painter->setPen(
        QPen(menuUp ? Qt::black : Qt::white, lineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::NoBrush);

    painter->drawLine(option->rect.left() + lineWidth * 1.5, option->rect.top() + rect().width() / 4,
                      option->rect.right() - lineWidth * 1.5, option->rect.top() + rect().width() / 4);

    painter->drawLine(option->rect.left() + lineWidth * 1.5, option->rect.top() + rect().width() / 2,
                      option->rect.right() - lineWidth * 1.5, option->rect.top() + rect().width() / 2);

    painter->drawLine(option->rect.left() + lineWidth * 1.5, option->rect.bottom() - rect().width() / 4,
                      option->rect.right() - lineWidth * 1.5, option->rect.bottom() - rect().width() / 4);
}
