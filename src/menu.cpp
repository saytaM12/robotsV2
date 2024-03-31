#include "menu.h"

Menu::Menu(int menuWidth, int menuHeight, QGraphicsScene *scene)
    : QGraphicsRectItem(), saveButton(new QPushButton("Save")), loadButton(new QPushButton("Load")),
      sampleWall(new SampleWall(SAMPLE_WALL_RECT(menuWidth, menuHeight), this)),
      sampleRobot(new SampleRobot(SAMPLE_ROBOT_TOPLEFT(menuWidth, menuHeight), 0, false, this)) {

    setRect(0, 0, menuWidth, menuHeight);
    QGraphicsRectItem::setX(0);
    QGraphicsRectItem::setY(0);
    QGraphicsRectItem::setZValue(-1);
    QGraphicsRectItem::setVisible(false);
    QGraphicsRectItem::setAcceptHoverEvents(true);

    saveButton->setGeometry(RIGHT_BUTTON_RECT(menuWidth, menuHeight));
    loadButton->setGeometry(LEFT_BUTTON_RECT(menuWidth, menuHeight));
    saveButton->hide();
    loadButton->hide();

    QObject::connect(saveButton, &QPushButton::clicked, this, &Menu::savePressed);
    QObject::connect(loadButton, &QPushButton::clicked, this, &Menu::loadPressed);

    scene->addItem(this);
    scene->addWidget(saveButton);
    scene->addWidget(loadButton);
}

void Menu::toggle() {
    if (QGraphicsRectItem::isVisible()) {
        saveButton->hide();
        loadButton->hide();
        QGraphicsRectItem::setVisible(false);
        QGraphicsRectItem::update();

        return;
    }

    saveButton->show();
    loadButton->show();
    QGraphicsRectItem::setVisible(true);
    QGraphicsRectItem::update();
}

void Menu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(QImage("imgs/textures/menu.png"));
    painter->drawRect(option->rect);

    QImage image("imgs/textures/launchPad.png");
    painter->drawImage(TOP_SAMPLE_BACKGROUND_RECT(option->rect.width(), option->rect.height()), image);
    painter->drawImage(BOT_SAMPLE_BACKGROUND_RECT(option->rect.width(), option->rect.height()), image);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 6));
    painter->drawLine(option->rect.right(), 0, option->rect.right(), option->rect.bottom());
}
