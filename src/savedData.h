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

/**
 * @brief The Data class manages saving and loading data to and from a JSON file.
 * 
 * It inherits from QObject.
 */
class Data : public QObject {

    Q_OBJECT

  private:
    MyScene *scene; /**< Pointer to the scene where data is saved and loaded. */

  public slots:
    /**
     * @brief Slot to save all robots and walls in the scene to a JSON file.
     */
    void saveData();

    /**
     * @brief Slot to populate the scene with robots and walls from a JSON file.
     */
    void loadData();

  public:
    /**
     * @brief Constructor for the Data object.
     * 
     * @param scene The scene to and from which the data is saved and loaded.
     */
    Data(MyScene *scene);
};
