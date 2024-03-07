#pragma once

#include <QFileDialog>
#include <QObject>
#include <fstream>
#include <iostream>

#include "json.hpp"

#include "myScene.h"
#include "robot.h"
#include "wall.h"

using json = nlohmann::json;

class Data : public QObject {

  Q_OBJECT

private:
  MyScene *scene;

public slots:
  /* When this slot is called all robots and walls in the scene are savad to a
   * json file.
   * @return: void
   */
  void saveData();

  /* When this slot is called the scene is populated with robots and walls form
   * a file.
   * @return: void
   */
  void loadData();

public:
  /* Constructor for the Data object.
   * @param MyScene *scene: The scene to and from which the data is saved and
   * loaded.
   */
  Data(MyScene *scene);
};
