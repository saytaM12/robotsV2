#ifndef SAMPLEROBOT
#define SAMPLEROBOT

#include "robot.h"

class SampleRobot : public Robot {

    Q_OBJECT

    public:
        SampleRobot(QRectF r, int a, bool p, QGraphicsEllipseItem *parent = nullptr);

        SampleRobot(SampleRobot *robot, QGraphicsEllipseItem *parent = nullptr);

        //void mousePressEvent(QGraphicsSceneMouseEvent *event);

        //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SAMPLEROBOT
