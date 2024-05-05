/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 */
#include "menu.h"

Menu::Menu(int menuWidth, int menuHeight, QGraphicsScene *scene)
    : QGraphicsRectItem(), saveButton(new MyPushButton("Save", this)),
      loadButton(new MyPushButton("Load", this)), simulationButton(new MyPushButton("Start Simulation", this)),
      sampleWall(new SampleWall(this)), sampleRobot(new SampleRobot(this)) {

    setRect(0, 0, menuWidth, menuHeight);
    QGraphicsRectItem::setX(0);
    QGraphicsRectItem::setY(0);
    QGraphicsRectItem::setZValue(-1);
    QGraphicsRectItem::setVisible(false);
    QGraphicsRectItem::setAcceptHoverEvents(true);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical, this);
    layout->addItem(sampleWall);
    layout->setContentsMargins(0, menuHeight / 3.0, 0, 0);
    layout->setItemSpacing(0, 100);
    layout->setAlignment(sampleWall, Qt::AlignHCenter);
    layout->addItem(sampleRobot);
    layout->setItemSpacing(1, 100);

    QGraphicsLinearLayout *buttonLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    buttonLayout->addItem(saveButton);
    buttonLayout->addItem(loadButton);
    layout->addItem(buttonLayout);

    layout->addItem(simulationButton);

    saveButton->hide();
    loadButton->hide();
    simulationButton->hide();

    QObject::connect(saveButton, &QPushButton::clicked, this, &Menu::savePressed);
    QObject::connect(loadButton, &QPushButton::clicked, this, &Menu::loadPressed);
    QObject::connect(simulationButton, &QPushButton::clicked, this, &Menu::simulationPressed);
    QObject::connect(simulationButton, &QPushButton::clicked, this, [=]() {
        simulationButton->setText(simulationButton->text() == "Start Simulation" ? "Stop Simulation"
                                                                                 : "Start Simulation");
    });

    scene->addWidget(saveButton);
    scene->addWidget(loadButton);
    scene->addWidget(simulationButton);

    scene->addItem(static_cast<QGraphicsRectItem *>(this));
}

void Menu::toggle() {
    if (QGraphicsRectItem::isVisible()) {
        saveButton->hide();
        loadButton->hide();
        simulationButton->hide();
        QGraphicsRectItem::setVisible(false);
        QGraphicsRectItem::update();

        return;
    }

    saveButton->show();
    loadButton->show();
    simulationButton->show();
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
