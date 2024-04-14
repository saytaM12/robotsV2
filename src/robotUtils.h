#pragma once

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QWidget>
#include <cmath>

#define ROBOTSIZE 80

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

class RobotContextMenu : public QMenu {

    Q_OBJECT

  public:
    RobotContextMenu(QString name, QWidget *parent = nullptr);

  signals:
    void changePlayer();
    void rotate();
    void changeIcon();
    void setSpeed();
    void setDetectionRange();
    void setDetectionAngle();
    void setTurningDirection();
};
