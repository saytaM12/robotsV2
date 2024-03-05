#ifndef SAMPLEROBOT
#define SAMPLEROBOT

#include "robot.h"

class SampleRobot : public Robot {

public:
  /*
   * Constructor for SampleRobot. creates a new SampleRobot.
   * @param QrectF rect: Rectangle in which the robot is placed.
   * @param int angle: The angle the robot is facing.
   * @param bool player: Whether the robot is a player or not.
   * @param Robot *parent: The parent of this object.
   */
  SampleRobot(int x, int y, int angle, bool player, Robot *parent = nullptr);

  /*
   * Constuctor to create a new SampleRobot from an existing Robot.
   * @param Robot *robot: The robot to be copied.
   * @param Robot *parent: The parent of this object.
   */
  SampleRobot(SampleRobot *robot, Robot *parent = nullptr);
};

#endif // SAMPLEROBOT
