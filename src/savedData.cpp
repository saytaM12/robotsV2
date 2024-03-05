#include "savedData.h"

Data::Data(MyScene *scene) {
  this->scene = scene;

  QObject::connect(scene->getMenu(), &Menu::savePressed, this, &Data::saveData);
  QObject::connect(scene->getMenu(), &Menu::loadPressed, this, &Data::loadData);
}

void Data::saveData() {
  QFileDialog dialog(nullptr, tr("Save File"), "examples/",
                     tr("JSON (*.json)"));
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setDefaultSuffix(tr(".json"));
  QString fileName = dialog.getSaveFileName();
  if (fileName.isEmpty())
    return;

  std::ofstream f(qPrintable(fileName));

  json data;

  for (MyItem *item : this->scene->getItems()) {
    json itemData;
    itemData["x"] = item->MyItem::pos().x();
    itemData["y"] = item->MyItem::pos().y();

    if (item->isWall()) {
      Wall *wall = static_cast<Wall *>(item);
      json wallData = itemData;
      wallData["size"] = wall->getSize();
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

void Data::loadData() {
  QString fileWithPath = QFileDialog::getOpenFileName(
      nullptr, tr("Open File"), "examples/", tr("JSON (*.json)"));
  if (fileWithPath.isEmpty())
    return;
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
