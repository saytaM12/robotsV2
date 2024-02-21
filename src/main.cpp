#include <iostream>
#include <fstream>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "json.hpp"

#include "editPanel.h"
#include "robot.h"
#include "wall.h"

using json = nlohmann::json;

void loadData(QGraphicsScene *scene);

int main(int argc, char **argv) {

    QApplication app (argc, argv);

    QGraphicsScene scene;
    loadData(&scene);
    MenuIcon *menuIcon = new MenuIcon;
    scene.addItem(menuIcon);

    QGraphicsView view(&scene);
    view.setDragMode(QGraphicsView::RubberBandDrag);
    view.show();

    return app.exec();
}

void loadData(QGraphicsScene *scene) {
    std::ifstream f("examples/test.json");
    json data = json::parse(f);
    f.close();
    for (int i = 0; i < data["players"]["len"]; i++) {
        int x = data["players"]["list"][i]["x"];
        int y = data["players"]["list"][i]["y"];
        int angle = data["players"]["list"][i]["angle"];
        QRectF rect(x, y, ROBOTSIZE, ROBOTSIZE);
        Robot *player = new Robot;
        player->setRect(rect);
        player->setAngle(angle);
        player->setPlayer(true);
        scene->addItem(player);
        QObject::connect(scene, &QGraphicsScene::selectionChanged, player, &Robot::selectionChanged);
    }

    for (int i = 0; i < data["robots"]["len"]; i++) {
        int x = data["robots"]["list"][i]["x"];
        int y = data["robots"]["list"][i]["y"];
        int angle = data["robots"]["list"][i]["angle"];
        QRectF rect(x, y, ROBOTSIZE, ROBOTSIZE);
        Robot *robot = new Robot;
        robot->setRect(rect);
        robot->setAngle(angle);
        robot->setPlayer(false);
        scene->addItem(robot);
        QObject::connect(scene, &QGraphicsScene::selectionChanged, robot, &Robot::selectionChanged);
    }

    for (int i = 0; i < data["walls"]["len"]; i++) {
        int x = data["walls"]["list"][i]["x"];
        int y = data["walls"]["list"][i]["y"];
        int size = data["walls"]["list"][i]["size"];
        QRectF rect(x, y, size, size);
        Wall *wall = new Wall;
        wall->setSize(size);
        wall->setRect(rect);
        scene->addItem(wall);
        QObject::connect(scene, &QGraphicsScene::selectionChanged, wall, &Wall::selectionChanged);
    }
}
