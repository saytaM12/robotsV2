#include <QGraphicsScene>
#include <iostream>
#include <fstream>

#include "json.hpp"

#include "wall.h"
#include "robot.h"

using json = nlohmann::json;

int loadData(QGraphicsScene *scene);

int saveData(QGraphicsScene *scene);
