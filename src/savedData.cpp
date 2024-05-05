/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 */
#include "savedData.h"

Data::Data(MyScene *scene) : scene(scene) {
    QObject::connect(scene->getMenu(), &Menu::savePressed, this, &Data::saveData);
    QObject::connect(scene->getMenu(), &Menu::loadPressed, this, &Data::loadData);
}

void Data::saveData() {
    QFileDialog dlg(nullptr, tr("Save File"), "examples/", tr("JSON (*.json)"));
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setDefaultSuffix(tr(".json"));
    QString fileName = dlg.getSaveFileName();
    if (fileName.isEmpty()) {
        return;
    }

    std::ofstream f(qPrintable(fileName));
    json data;

    for (MyItem *item : scene->items()) {
        json itemData;
        itemData["x"] = item->MyItem::x();
        itemData["y"] = item->MyItem::y();

        if (item->isWall()) {
            Wall *wall = static_cast<Wall *>(item);
            json wallData = itemData;
            wallData["width"] = wall->rect().width();
            wallData["height"] = wall->rect().height();
            data["walls"].push_back(wallData);

        } else {
            Robot *robot = static_cast<Robot *>(item);
            json robotData = itemData;
            robotData["speed"] = robot->getSpeed();
            robotData["angle"] = robot->getAngle();
            robotData["player"] = robot->getPlayer();
            robotData["clockwise"] = robot->isClockwise();
            robotData["detectionAngle"] = robot->getDetectionAngle();
            robotData["detectionRange"] = robot->getDetectionRange();
            data["robots"].push_back(robotData);
        }
    }

    f << data.dump(4) << std::endl;
}

/* This method validates the robot data inside the json data structure.
 * @param `type too long to write here` robotData: The robot data to be
 * validated.
 * @param qreal *x: Pointer to variable in which to store the x coordinate.
 * @param qreal *y: Pointer to variable in which to store the y coordinate.
 * @param int *speed: Pointer to variable in which to store the robot's speed.
 * @param qreal *angle: Pointer to variable in which to store the angle.
 * @param bool *player: Pointer to variable in which to store the player status
 * @param bool *clockwise: Pointer to variable in which to store the turning direction
 * @param int *detectionAngle: Pointer to variable in which to store the detection angle
 * @param int *detectionRange: Pointer to variable in which to store the detection range
 * @param qreal sceneWidth: Width of the scene.
 * @param qreal sceneHeight: Height of the scene.
 * @param QString fileName: File from which the data was read. (for printing
 * in error messages).
 * @return: void
 */
int validateRobotData(
    const nlohmann::json_abi_v3_11_3::detail::iteration_proxy_value<
        nlohmann::json_abi_v3_11_3::detail::iter_impl<nlohmann::json_abi_v3_11_3::basic_json<>>>
        robotData,
    qreal *x, qreal *y, int *speed, qreal *angle, int *player, bool *clockwise, int *detectionAngle,
    int *detectionRange, qreal sceneWidth, qreal sceneHeight, QString fileName) {
    try {
        *x = robotData.value()["x"];
        *y = robotData.value()["y"];
        *speed = robotData.value()["speed"];
        *angle = robotData.value()["angle"];
        *player = robotData.value()["player"];
        *clockwise = robotData.value()["clockwise"];
        *detectionAngle = robotData.value()["detectionAngle"];
        *detectionRange = robotData.value()["detectionRange"];
    } catch (json::type_error &ex) {
        std::cerr << "in file " << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
                  << ": a robot is missing a value or a value was entered with "
                     "incorrect type\nskipping this robot\n"
                  << std::endl;
        return -1;
    }

    if (*x < 0 || *y < 0) {
        std::cerr << "in file " << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
                  << ": \"robot.x/y\" cannot be less than 0\nsetting value to 0\n"
                  << std::endl;
        *x = *x < 0 ? 0 : *x;
        *y = *y < 0 ? 0 : *y;
    }

    int xLimit = sceneWidth - ROBOTSIZE - 4;
    int yLimit = sceneHeight - ROBOTSIZE - 4;
    if (*x > xLimit || *y > yLimit) {
        std::cerr << "in file " << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
                  << ": \"robot.x/y\" cannot be more than screen size\n"
                     "setting value to maximum possible\n"
                  << std::endl;
        *x = *x > xLimit ? xLimit : *x;
        *y = *y > yLimit ? yLimit : *y;
    }

    if (*speed < 0) {
        std::cerr << "in file " << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
                  << ": \"robot.speed\" cannot be less than zero\nsetting value to 0\n"
                  << std::endl;
        *speed = 0;
    }

    if (*angle < 0 || *angle > 360) {
        std::cerr << "in file " << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
                  << ": \"robot.angle\" cannot be outside interval <0, 360)\n"
                     "setting value to 0\n"
                  << std::endl;
        *angle = 0;
    }

    if (*detectionAngle < 0 || *detectionAngle > 360) {
        std::cerr << "in file " << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
                  << ": \"robot.detectionAngle\" cannot be outside interval <0, 360)\n"
                     "setting value to 0\n"
                  << std::endl;
        *detectionAngle = 0;
    }

    if (*detectionRange < 0) {
        std::cerr << "in file " << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
                  << ": \"robot.detectionRange\" cannot be less than zero\n"
                     "setting value to 0\n"
                  << std::endl;
        *detectionRange = 0;
    }

    if (*player < 0 || *player > 2) {
        std::cerr << "in file " << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
                  << ": \"robot.player\" can only be 0, 1 or 2\nsetting value to 0\n"
                  << std::endl;
        *player = 0;
    }

    return 0;
}

/* This method validates the wall data inside the json data structure.
 * @param json wallData: The wall data to be
 * validated.
 * @param qreal *x: Pointer to variable in which to store the x coordinate.
 * @param qreal *y: Pointer to variable in which to store the y coordinate.
 * @param int *width: Pointer to variable in which to store the width
 * @param int *height: Pointer to variable in which to store the height
 * @param qreal sceneWidth: Width of the scene.
 * @param qreal sceneHeight: Height of the scene.
 * @param QString fileName: File from which the data was read. (for printing
 * in error messages).
 * @return: void
 */
int validateWallData(
    const nlohmann::json_abi_v3_11_3::detail::iteration_proxy_value<
        nlohmann::json_abi_v3_11_3::detail::iter_impl<nlohmann::json_abi_v3_11_3::basic_json<>>>
        wallData,
    qreal *x, qreal *y, int *width, int *height, qreal sceneWidth, qreal sceneHeight, QString fileName) {
    try {
        *x = wallData.value()["x"];
        *y = wallData.value()["y"];
        *width = wallData.value()["width"];
        *height = wallData.value()["height"];
    } catch (json::type_error &ex) {
        std::cerr << "in file " << qPrintable(fileName)
                  << ": a wall is missing a value or a value was entered with "
                     "incorrect type\nskipping this wall\n"
                  << std::endl;
        return -1;
    }

    if (*x < 0 || *y < 0) {
        std::cerr << "in file " << qPrintable(fileName)
                  << ": \"wall.x/y\" cannot be less than 0\nsetting value to 0\n"
                  << std::endl;
        *x = *x < 0 ? 0 : *x;
        *y = *y < 0 ? 0 : *y;
    }

    if (*width <= 0 || *height <= 0) {
        std::cerr << "in file " << qPrintable(fileName)
                  << ": \"wall.width / wall.height\" cannot be less than or equal "
                     "to zero "
                     "\nsetting value to 10\n"
                  << std::endl;
        *width = *width <= 0 ? 10 : *width;
        *height = *height <= 0 ? 10 : *height;
    }

    int xLimit = sceneWidth - *width - 4;
    int yLimit = sceneHeight - *height - 4;
    if (*x > xLimit || *y > yLimit) {
        std::cerr << "in file " << qPrintable(fileName)
                  << ": \"wall.x/y\" cannot be more than screen size\nsetting "
                     "value to maximum possible\n"
                  << std::endl;
        *x = *x > xLimit ? xLimit : *x;
        *y = *y > yLimit ? yLimit : *y;
    }

    return 0;
}

void Data::loadData() {
    QString fileWithPath =
        QFileDialog::getOpenFileName(nullptr, tr("Open File"), "examples/", tr("JSON (*.json);All Files (*)"));
    if (fileWithPath.isEmpty()) {
        return;
    }

    std::ifstream f(qPrintable(fileWithPath));

    QString fileName = fileWithPath.remove(0, fileWithPath.lastIndexOf('/') + 1);
    json data;

    try {
        data = json::parse(f);
    } catch (json::parse_error &ex) {
        std::cerr << "file " << qPrintable(fileName) << "has wrong format" << std::endl;
        f.close();
        return;
    }

    f.close();

    scene->clear();

    for (auto &robotData : data["robots"].items()) {

        qreal x;
        qreal y;
        int speed;
        qreal angle;
        int player;
        bool clockwise;
        int detectionAngle;
        int detectionRange;

        if (validateRobotData(robotData, &x, &y, &speed, &angle, &player, &clockwise, &detectionAngle,
                              &detectionRange, scene->getWidth(), scene->getHeight(), fileName)) {
            continue;
        }

        QPointer<Robot> robot =
            new Robot(x, y, speed, angle, player, clockwise, detectionAngle, detectionRange);
        scene->addItem(robot);
        QObject::connect(scene, &MyScene::gameTick, robot, &Robot::gameTick);
        QObject::connect(robot, &Robot::playerChanged, scene, &MyScene::ensureOnePlayer);
        QObject::connect(robot, &Robot::detectObjects, scene, &MyScene::detectObjects);
    }

    for (auto &wallData : data["walls"].items()) {

        qreal x;
        qreal y;
        int width;
        int height;

        if (validateWallData(wallData, &x, &y, &width, &height, scene->getWidth(), scene->getHeight(),
                             fileName)) {
            continue;
        }

        QPointer<Wall> wall = new Wall(x, y, width, height);
        scene->addItem(wall);
    }
}
