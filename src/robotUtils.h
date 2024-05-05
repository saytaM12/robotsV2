/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 */
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

/**
 * @brief Direction of movement for player robots.
 */
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
     * @brief Signal emitted when the player change button is clicked.
     */
    void changePlayer();

    /**
     * @brief Signal emitted when the robot rotate button is clicked.
     */
    void rotate();

    /**
     * @brief Signal emitted when the robot icon change button is clicked.
     */
    void changeIcon();

    /**
     * @brief Signal emitted when the set speed button is clicked.
     */
    void setSpeed();

    /**
     * @brief Signal emitted when the set detection range detection button is clicked.
     */
    void setDetectionRange();

    /**
     * @brief Signal emitted when the set detection angle button is clicked.
     */
    void setDetectionAngle();

    /**
     * @brief Signal emitted when the set set turning direction button is clicked.
     */
    void setTurningDirection();
};
