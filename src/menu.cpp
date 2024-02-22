#include "menu.h"

#include <iostream>

Menu::Menu(QGraphicsRectItem *parent) : QGraphicsRectItem(parent) {

    int menuWidth = windowSize.width() / 4.0;
    int menuHeight = windowSize.height();
    int buttonWidth = menuWidth / 3.0;
    int buttonHeight = menuWidth / 5.0;
    int sampleSize = menuWidth * SCALER;

    setRect(POS, 0, menuWidth, menuHeight);

    saveButton = new QPushButton(QString("save"), this);
    int saveButtonX = POS + menuWidth / 9.0;
    int saveButtonY = menuHeight - buttonHeight - 30;
    saveButton->setGeometry(saveButtonX, saveButtonY, buttonWidth, buttonHeight);

    loadButton = new QPushButton(QString("load"), this);
    int loadButtonX = saveButtonX + buttonWidth + menuWidth / 9.0;
    int loadButtonY = saveButtonY;
    loadButton->setGeometry(loadButtonX, loadButtonY, buttonWidth, buttonHeight);

    sampleWall = new Wall;
    sampleWall->setParentItem(this);
    sampleWall->setRect(POS + menuWidth / 2.0 - 50,
                        menuHeight - buttonHeight - 60 - sampleSize - (menuWidth - sampleSize) / 2.0 - sampleSize / 2.0 - 50,
                        100,
                        100);
    sampleWall->setSize(100);

    sampleRobot = new Robot;
    sampleRobot->setParentItem(this);
    sampleRobot->setRect(POS + menuWidth / 2.0 - ROBOTSIZE / 2.0,
                         menuHeight - buttonHeight - 60 - sampleSize / 2.0 - ROBOTSIZE / 2.0,
                         ROBOTSIZE,
                         ROBOTSIZE);
    sampleRobot->setAngle(0);
    sampleRobot->setPlayer(false);
    QGraphicsRectItem::setVisible(false);
}

void Menu::toggle() {
    QGraphicsRectItem::setVisible(!QGraphicsRectItem::isVisible());
    QGraphicsRectItem::update();
}

void Menu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::gray);
    painter->drawRect(option->rect);

    int buttonHeight = option->rect.width() / 5.0;
    int sampleSize = option->rect.width() * SCALER;
    int samplePadding = (option->rect.width() - sampleSize) / 2.0;
    painter->setBrush(Qt::darkGray);
    painter->drawRect(option->rect.x() + samplePadding,
                      option->rect.bottom() - buttonHeight - 60 - sampleSize * 2 - samplePadding,
                      sampleSize,
                      sampleSize);
    painter->drawRect(option->rect.x() + samplePadding,
                      option->rect.bottom() - buttonHeight - 60 - sampleSize,
                      sampleSize,
                      sampleSize);
}
