#pragma once

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QWidget>
#include <cmath>

#define ROBOTSIZE 80

/**
 * @brief Macro to set parameters with a dialog.
 * 
 * This macro creates a QDialog with input fields for setting parameters.
 * 
 * @param inputLabelText The label text for the input field.
 * @param descriptionText The description text for the parameter.
 * @param limitMin The minimum limit for the parameter.
 * @param limitMax The maximum limit for the parameter. If set to 0, there is no maximum limit.
 * @param parameter The parameter to be set.
 */
#define setParametersWithDialog(inputLabelText, descriptionText, limitMin, limitMax, parameter)               \
    QDialog dialog;                                                                                           \
    QGridLayout layout(&dialog);                                                                              \
                                                                                                              \
    QLabel inputLabel((inputLabelText));                                                                      \
                                                                                                              \
    QLineEdit lineEdit;                                                                                       \
    if (limitMax == 0) {                                                                                      \
        lineEdit.setValidator(new QIntValidator(limitMin));                                                   \
    } else {                                                                                                  \
        lineEdit.setValidator(new QIntValidator(limitMin, limitMax));                                         \
    }                                                                                                         \
    lineEdit.setPlaceholderText(QString("current value: %2").arg((parameter)));                               \
                                                                                                              \
    QLabel description((descriptionText));                                                                    \
                                                                                                              \
    QPushButton okButton("OK");                                                                               \
    QPushButton cancelButton("Cancel");                                                                       \
                                                                                                              \
    layout.addWidget(&inputLabel, 0, 0);                                                                      \
    layout.addWidget(&lineEdit, 0, 1);                                                                        \
    layout.addWidget(&description, 1, 0, 1, 2);                                                               \
    layout.addWidget(&okButton, 2, 0);                                                                        \
    layout.addWidget(&cancelButton, 2, 1);                                                                    \
                                                                                                              \
    QObject::connect(&okButton, &QPushButton::clicked, [&dialog, &lineEdit, this]() {                         \
        dialog.accept();                                                                                      \
        (parameter) = atoi(qPrintable(lineEdit.text()));                                                      \
    });                                                                                                       \
    QObject::connect(&cancelButton, &QPushButton::clicked, [&dialog]() { dialog.reject(); });                 \
                                                                                                              \
    dialog.exec();

typedef enum TRobotDirections { turnLeft, moveBack, moveForward, turnRight } Direction;

/**
 * @brief The RobotContextMenu class represents a context menu for a robot.
 * 
 * It inherits from QMenu.
 */
class RobotContextMenu : public QMenu {

    Q_OBJECT

  public:
    /**
     * @brief Constructor for the RobotContextMenu class.
     * 
     * @param name The name of the context menu.
     * @param parent The parent widget.
     */
    RobotContextMenu(QString name, QWidget *parent = nullptr);

  signals:
    /**
     * @brief Signal emitted when the player is changed.
     */
    void changePlayer();

    /**
     * @brief Signal emitted when the robot is rotated.
     */
    void rotate();

    /**
     * @brief Signal emitted when the robot icon is changed.
     */
    void changeIcon();

    /**
     * @brief Signal emitted when the robot speed is set.
     */
    void setSpeed();

    /**
     * @brief Signal emitted when the detection range is set.
     */
    void setDetectionRange();

    /**
     * @brief Signal emitted when the detection angle is set.
     */
    void setDetectionAngle();

    /**
     * @brief Signal emitted when the turning direction is set.
     */
    void setTurningDirection();
};
