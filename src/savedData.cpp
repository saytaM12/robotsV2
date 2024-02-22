#include "savedData.h"

Data::Data(MyScene *scene) {
    this->scene = scene;

    QObject::connect(scene->getMenu(), &Menu::savePressed, this, &Data::saveDataSlot);
    QObject::connect(scene->getMenu(), &Menu::loadPressed, this, &Data::loadDataSlot);
}

int Data::saveData() {
    QFileDialog dialog(nullptr, tr("Save File"), "examples/", tr("JSON (*.json)"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix(tr(".json"));
    QString fileName = dialog.getSaveFileName();
    if (fileName.isEmpty()) return 0;
    
    return 0;
}

int Data::loadData() {
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"), "examples/", tr("JSON (*.json)"));
    if (fileName.isEmpty()) return 0;

    std::ifstream f(qPrintable(fileName));
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

    this->scene->clear();

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
        Robot *player = new Robot(rect, angle, true);
        scene->newItem(player);
        QObject::connect(scene, &MyScene::selectionChanged, player, &Robot::selectionChanged);
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
        Robot *robot = new Robot(rect, angle, false);
        scene->newItem(robot);
        QObject::connect(scene, &MyScene::selectionChanged, robot, &Robot::selectionChanged);
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
        Wall *wall = new Wall(rect, size);
        scene->newItem(wall);
        QObject::connect(scene, &MyScene::selectionChanged, wall, &Wall::selectionChanged);
    }

    return 0;
}

void Data::saveDataSlot() {
    this->saveData();
}

void Data::loadDataSlot() {
    this->loadData();
}
