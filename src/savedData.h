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
  /*
   * When this slot is called all robots and walls in the scene are savad to a
   * json file.
   * @return: void
   */
  void saveData();

  /*
   * When this slot is called the scene is populated with robots and walls form
   * a file.
   * @return: void
   */
  void loadData();

public:
  /*
   * Constructor for the Data object.
   * @param MyScene *scene: The scene to and from which the data is saved and
   * loaded.
   */
  Data(MyScene *scene);

  /*
   * This method validates the robot data inside the json data structure.
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
  void validateRobotData(
      const nlohmann::json_abi_v3_11_3::detail::iteration_proxy_value<
          nlohmann::json_abi_v3_11_3::detail::iter_impl<
              nlohmann::json_abi_v3_11_3::basic_json<>>>
          robotData,
      qreal *x, qreal *y, qreal *angle, bool *player, QString fileName);

  /*
   * This method validates the wall data inside the json data structure.
   * @param `type too long to write here` wallData: The wall data to be
   * validated.
   * @param qreal *x: Pointer to variable in which to store the x coordinate.
   * @param qreal *y: Pointer to variable in which to store the y coordinate.
   * @param int *size: Pointer to variable in which to store the size of the
   * wall.
   * @param QString fileName: File from which the data was read. (for printing
   * in error messages).
   * @return: void
   */
  void validateWallData(
      const nlohmann::json_abi_v3_11_3::detail::iteration_proxy_value<
          nlohmann::json_abi_v3_11_3::detail::iter_impl<
              nlohmann::json_abi_v3_11_3::basic_json<>>>
          wallData,
      qreal *x, qreal *y, int *size, QString fileName);
};
