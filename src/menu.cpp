/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 *
 * This module contains the implementation of the Menu class.
 */
#include "menu.h"

Menu::Menu(int menuWidth, int menuHeight, QGraphicsScene *scene)
    : QGraphicsRectItem(), helpButton(new QPushButton("?")), saveButton(new MyPushButton("Save", this)),
      loadButton(new MyPushButton("Load", this)), simulationButton(new MyPushButton("Start Simulation", this)),
      sampleWall(new SampleWall(this)), sampleRobot(new SampleRobot(this)) {

    setRect(0, 0, menuWidth, menuHeight);
    QGraphicsRectItem::setX(0);
    QGraphicsRectItem::setY(0);
    QGraphicsRectItem::setZValue(-1);
    QGraphicsRectItem::setVisible(false);
    QGraphicsRectItem::setAcceptHoverEvents(true);

    helpButton->setMinimumSize(1, 1);
    helpButton->setGeometry(menuWidth - 90, 40, 50, 50);
    helpButton->setFont(QFont("Comic Sans", 30, 100, false));
    scene->addWidget(helpButton);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical, this);
    layout->setContentsMargins(0, menuHeight / 3.5, 0, 0);

    QGraphicsLinearLayout *robotLayout = new QGraphicsLinearLayout();
    robotLayout->addItem(sampleRobot);
    robotLayout->setContentsMargins(menuWidth / 2.0 - ROBOTSIZE / 2.0, 0, 0, 0);
    layout->addItem(robotLayout);
    layout->setItemSpacing(0, 200);

    QGraphicsLinearLayout *wallLayout = new QGraphicsLinearLayout();
    wallLayout->addItem(sampleWall);
    wallLayout->setContentsMargins(menuWidth / 2.0 - sampleWall->boundingRect().width() / 2.0, 0, 0, 0);
    layout->addItem(wallLayout);
    layout->setItemSpacing(1, 145);

    QGraphicsLinearLayout *buttonLayout = new QGraphicsLinearLayout(Qt::Vertical);

    QGraphicsLinearLayout *dataButtonLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    dataButtonLayout->addItem(saveButton);
    dataButtonLayout->setItemSpacing(0, 50);
    dataButtonLayout->addItem(loadButton);
    buttonLayout->addItem(dataButtonLayout);

    buttonLayout->addItem(simulationButton);

    buttonLayout->setContentsMargins(24, 0, 0, 0);

    layout->addItem(buttonLayout);

    helpButton->hide();
    saveButton->hide();
    loadButton->hide();
    simulationButton->hide();

    QObject::connect(helpButton, &QPushButton::clicked, this, &Menu::displayHelp);
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
        helpButton->hide();
        saveButton->hide();
        loadButton->hide();
        simulationButton->hide();
        QGraphicsRectItem::setVisible(false);
        QGraphicsRectItem::update();

        return;
    }

    helpButton->show();
    saveButton->show();
    loadButton->show();
    simulationButton->show();
    QGraphicsRectItem::setVisible(true);
    QGraphicsRectItem::update();
}

void Menu::displayHelp() {
    QDialog dialog;
    QGridLayout layout(&dialog);

    QFile f("README.md");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&f);

    QTextEdit text;
    text.setMarkdown(stream.readAll());
    text.setReadOnly(true);
    text.setMinimumSize(800, 600);
    layout.addWidget(&text);

    QPointer<QPushButton> button = new QPushButton();
    button->setText("OK");
    layout.addWidget(button);

    QObject::connect(button, &QPushButton::clicked, [&dialog]() { dialog.accept(); });

    dialog.exec();
}

void Menu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(QImage("imgs/textures/menu.png"));
    painter->drawRect(option->rect);

    QImage image("imgs/textures/launchPad.png");
    QRectF rect;
    rect.setWidth(QGraphicsRectItem::rect().width() / 1.1);
    rect.setHeight(rect.width());
    rect.moveTo((QGraphicsRectItem::rect().width() - rect.width()) / 2.0,
                sampleRobot->MyItem::y() + sampleRobot->boundingRect().height() / 2.0 - rect.height() / 2.0);

    painter->drawImage(rect, image);

    rect.moveTo((QGraphicsRectItem::rect().width() - rect.width()) / 2.0,
                sampleWall->MyItem::y() + sampleWall->boundingRect().height() / 2.0 - rect.height() / 2.0);

    painter->drawImage(rect, image);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 6));
    painter->drawLine(option->rect.right(), 0, option->rect.right(), option->rect.bottom());
}
