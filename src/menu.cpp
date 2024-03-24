#include "menu.h"

Menu::Menu(int menuWidth, int menuHeight, QGraphicsScene *scene)
    : QGraphicsRectItem(), saveButton(new QPushButton("Save")), loadButton(new QPushButton("Load")),
      sampleWall(new SampleWall(SAMPLE_WALL_RECT(menuWidth, menuHeight), this)),
      sampleRobot(new SampleRobot(SAMPLE_ROBOT_TOPLEFT(menuWidth, menuHeight), 0, false, this)) {
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);

    setX(0);
    setY(0);
    setRect(0, 0, menuWidth, menuHeight);
    setZValue(-1);

    scene->addItem(this);

    saveButton->setGeometry(RIGHT_BUTTON_RECT(menuWidth, menuHeight));
    loadButton->setGeometry(LEFT_BUTTON_RECT(menuWidth, menuHeight));
    saveButton->hide();
    loadButton->hide();

    scene->addWidget(saveButton);
    scene->addWidget(loadButton);

    QObject::connect(saveButton, &QPushButton::clicked, this, &Menu::savePressed);
    QObject::connect(loadButton, &QPushButton::clicked, this, &Menu::loadPressed);

    QGraphicsRectItem::setVisible(false);
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
    painter->setBrush(Qt::gray);
    painter->drawRect(option->rect);

    painter->setBrush(Qt::darkGray);
    painter->drawRect(TOP_SAMPLE_BACKGROUND_RECT(option->rect.width(), option->rect.height()));
    painter->drawRect(BOT_SAMPLE_BACKGROUND_RECT(option->rect.width(), option->rect.height()));
}
