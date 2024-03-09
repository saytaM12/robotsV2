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

  for (MyItem *item : this->scene->getItems()) {
    json itemData;
    itemData["x"] = item->MyItem::x();
    itemData["y"] = item->MyItem::y();

    if (item->isWall()) {
      Wall *wall = static_cast<Wall *>(item);
      json wallData = itemData;
      wallData["width"] = wall->rect().width();
      wallData["height"] = wall->rect().height();
      data["walls"]["list"].push_back(wallData);

    } else {
      Robot *robot = static_cast<Robot *>(item);
      json robotData = itemData;
      robotData["angle"] = robot->getAngle();
      robotData["player"] = robot->isPlayer();
      data["robots"]["list"].push_back(robotData);
    }
  }

  f << data.dump(4) << std::endl;
}

/* This method validates the robot data inside the json data structure.
 * @param `type too long to write here` robotData: The robot data to be
 * validated.
 * @param qreal *x: Pointer to variable in which to store the x coordinate.
 * @param qreal *y: Pointer to variable in which to store the y coordinate.
 * @param qreal *angle: Pointer to variable in which to store the angle.
 * @param bool *player: Pointer to variable in which to store whether the
 * robot is a player.
 * @param QString fileName: File from which the data was read. (for printing
 * in error messages).
 * @return: void
 */
int validateRobotData(
    const nlohmann::json_abi_v3_11_3::detail::iteration_proxy_value<
        nlohmann::json_abi_v3_11_3::detail::iter_impl<
            nlohmann::json_abi_v3_11_3::basic_json<>>>
        robotData,
    qreal *x, qreal *y, qreal *angle, bool *player, qreal sceneWidth,
    qreal sceneHeight, QString fileName) {
  try {
    *x = robotData.value()["x"];
    *y = robotData.value()["y"];
    *angle = robotData.value()["angle"];
    *player = robotData.value()["player"];
  } catch (json::type_error &ex) {
    std::cerr << "in file "
              << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
              << ": a robot is missing a value or a value was entered with "
                 "incorrect type\nskipping this robot\n"
              << std::endl;
    return -1;
  }

  if (*x < 0 || *y < 0) {
    std::cerr << "in file "
              << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
              << ": \"robot.x/y\" cannot be less than 0\nsetting value to 0\n"
              << std::endl;
    *x = *x < 0 ? 0 : *x;
    *y = *y < 0 ? 0 : *y;
  }

  int xLimit = sceneWidth - ROBOTSIZE - 4;
  int yLimit = sceneHeight - ROBOTSIZE - 4;
  if (*x > xLimit || *y > yLimit) {
    std::cerr << "in file "
              << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
              << ": \"robot.x/y\" cannot be more than screen size\nsetting "
                 "value to maximum possible\n"
              << std::endl;
    *x = *x > xLimit ? xLimit : *x;
    *y = *y > yLimit ? yLimit : *y;
  }

  if (*angle < 0 || *angle >= 360) {
    std::cerr << "in file "
              << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
              << ": \"robot.angle\" cannot be outside interval <0, "
                 "360)\nsetting value to 0\n"
              << std::endl;
    *angle = 0;
  }

  return 0;
}

/* This method validates the wall data inside the json data structure.
 * @param json wallData: The wall data to be
 * validated.
 * @param qreal *x: Pointer to variable in which to store the x coordinate.
 * @param qreal *y: Pointer to variable in which to store the y coordinate.
 * @param int *size: Pointer to variable in which to store the size of the
 * wall.
 * @param QString fileName: File from which the data was read. (for printing
 * in error messages).
 * @return: void
 */
int validateWallData(
    const nlohmann::json_abi_v3_11_3::detail::iteration_proxy_value<
        nlohmann::json_abi_v3_11_3::detail::iter_impl<
            nlohmann::json_abi_v3_11_3::basic_json<>>>
        wallData,
    qreal *x, qreal *y, int *width, int *height, qreal sceneWidth,
    qreal sceneHeight, QString fileName) {
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
  QString fileWithPath = QFileDialog::getOpenFileName(
      nullptr, tr("Open File"), "examples/", tr("JSON (*.json)"));
  if (fileWithPath.isEmpty()) {
    return;
  }

  std::ifstream f(qPrintable(fileWithPath));

  QString fileName = fileWithPath.remove(0, fileWithPath.lastIndexOf('/') + 1);
  json data;

  try {
    data = json::parse(f);
  } catch (json::parse_error &ex) {
    std::cerr << "file " << qPrintable(fileName) << "has wrong format"
              << std::endl;
    f.close();
    return;
  }

  f.close();

  this->scene->clear();

  for (auto &robotData : data["robots"]["list"].items()) {

    qreal x;
    qreal y;
    qreal angle;
    bool player;

    validateRobotData(robotData, &x, &y, &angle, &player, fileName);

    QPointer<Robot> robot = new Robot(x, y, angle, player);
    scene->addItem(robot);
  }

  for (auto &wallData : data["walls"]["list"].items()) {

    qreal x;
    qreal y;
    int size;

    validateWallData(wallData, &x, &y, &size, fileName);

    QPointer<Wall> wall = new Wall(x, y, size);
    scene->addItem(wall);
  }
}

void Data::validateRobotData(
    const nlohmann::json_abi_v3_11_3::detail::iteration_proxy_value<
        nlohmann::json_abi_v3_11_3::detail::iter_impl<
            nlohmann::json_abi_v3_11_3::basic_json<>>>
        robotData,
    qreal *x, qreal *y, qreal *angle, bool *player, QString fileName) {
  try {
    *x = robotData.value()["x"];
    *y = robotData.value()["y"];
    *angle = robotData.value()["angle"];
    *player = robotData.value()["player"];
  } catch (json::type_error &ex) {
    std::cerr << "in file "
              << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
              << ": a robot is missing a value or a value was entered with "
                 "incorrect type\nskipping this robot\n"
              << std::endl;
    return;
  }

  if (*x < 0 || *y < 0) {
    std::cerr << "in file "
              << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
              << ": \"robot.x/y\" cannot be less than 0\nsetting value to 0\n"
              << std::endl;
    *x = *x < 0 ? 0 : *x;
    *y = *y < 0 ? 0 : *y;
  }

  int xLimit = this->scene->getSize().width() - ROBOTSIZE - 4;
  int yLimit = this->scene->getSize().height() - ROBOTSIZE - 4;
  if (*x > xLimit || *y > yLimit) {
    std::cerr << "in file "
              << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
              << ": \"robot.x/y\" cannot be more than screen size\nsetting "
                 "value to maximum possible\n"
              << std::endl;
    *x = *x > xLimit ? xLimit : *x;
    *y = *y > yLimit ? yLimit : *y;
  }

  if (*angle < 0 || *angle >= 360) {
    std::cerr << "in file "
              << qPrintable(fileName.remove(0, fileName.lastIndexOf('/') + 1))
              << ": \"robot.angle\" cannot be outside interval <0, "
                 "360)\nsetting value to 0\n"
              << std::endl;
    *angle = 0;
  }
}

void Data::validateWallData(
    const nlohmann::json_abi_v3_11_3::detail::iteration_proxy_value<
        nlohmann::json_abi_v3_11_3::detail::iter_impl<
            nlohmann::json_abi_v3_11_3::basic_json<>>>
        wallData,
    qreal *x, qreal *y, int *size, QString fileName) {
  try {
    *x = wallData.value()["x"];
    *y = wallData.value()["y"];
    *size = wallData.value()["size"];
  } catch (json::type_error &ex) {
    std::cerr << "in file " << qPrintable(fileName)
              << ": a wall is missing a value or a value was entered with "
                 "incorrect type\nskipping this wall\n"
              << std::endl;
    return;
  }

  if (*x < 0 || *y < 0) {
    std::cerr << "in file " << qPrintable(fileName)
              << ": \"wall.x/y\" cannot be less than 0\nsetting value to 0\n"
              << std::endl;
    *x = *x < 0 ? 0 : *x;
    *y = *y < 0 ? 0 : *y;
  }

  if (*size <= 0) {
    std::cerr << "in file " << qPrintable(fileName)
              << ": \"wall.size\" cannot be less than or equal to zero "
                 "\nsetting value to 1\n"
              << std::endl;
    *size = 1;
  }

  int xLimit = this->scene->getSize().width() - *size - 4;
  int yLimit = this->scene->getSize().height() - *size - 4;
  if (*x > xLimit || *y > yLimit) {
    std::cerr << "in file " << qPrintable(fileName)
              << ": \"wall.x/y\" cannot be more than screen size\nsetting "
                 "value to maximum possible\n"
              << std::endl;
    *x = *x > xLimit ? xLimit : *x;
    *y = *y > yLimit ? yLimit : *y;
  }
}
