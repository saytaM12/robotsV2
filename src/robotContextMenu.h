#pragma once

#include <QMenu>
#include <QWidget>

class RobotContextMenu : public QMenu {

    Q_OBJECT

  public:
    RobotContextMenu(QString name, QWidget *parent = nullptr);

  signals:
    void rotate();
    void changeIcon();
    void setSpeed();
    void setDetectionRange();
    void setDetectionAngle();
    void setTurningDirection();
};
