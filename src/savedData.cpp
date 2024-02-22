#include "savedData.h"

int loadData(QGraphicsScene *scene) {
    std::ifstream f("examples/test.json");
    json data;

    try {
        data = json::parse(f);
    } catch (json::parse_error& ex) {
        std::cerr << "JSON file has wrong format\n";
        f.close();
        return -1;
    }

    f.close();

    if (data["players"]["len"] < 0 ||
        data["robots"]["len"] < 0 ||
        data["walls"]["len"] < 0) {
        std::cerr << "in JSON file: \"len\" cannot be less than 0\n";
        return -1;
    }

    for (int i = 0; i < data["players"]["len"]; i++) {

        int x = data["players"]["list"][i]["x"];
        int y = data["players"]["list"][i]["y"];
        if (x < 0 || y < 0) {
            std::cerr << "in JSON file: player.\"x\"/\"y\" cannot be less than 0\n";
            return -1;
        }

        int angle = data["players"]["list"][i]["angle"];
        if (angle < 0 || angle >= 360) {
            std::cerr << "in JSON file: player.\"angle\" must be between 0 (included) and 360 (excluded)\n";
            return -1;
        }

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
        if (x < 0 || y < 0) {
            std::cerr << "in JSON file: robot.\"x\"/\"y\" cannot be less than 0\n";
            return -1;
        }

        int angle = data["robots"]["list"][i]["angle"];
        if (angle < 0 || angle >= 360) {
            std::cerr << "in JSON file: robot.\"angle\" must be between 0 (included) and 360 (excluded)\n";
            return -1;
        }

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
        if (x < 0 || y < 0) {
            std::cerr << "in JSON file: wall.\"x\"/\"y\" cannot be less than 0\n";
            return -1;
        }

        int size = data["walls"]["list"][i]["size"];
        if (size <= 0) {
            std::cerr << "in JSON file: wall.\"size\" cannot be less than or equal to 0\n";
            return -1;
        }

        QRectF rect(x, y, size, size);
        Wall *wall = new Wall;
        wall->setRect(rect);
        wall->setSize(size);
        scene->addItem(wall);
        QObject::connect(scene, &QGraphicsScene::selectionChanged, wall, &Wall::selectionChanged);
    }

    return 0;
}

int saveData(QGraphicsScene *scene) {
    return 0;
}
