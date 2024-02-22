#ifndef MENU
#define MENU

#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QPainter>
#include <QObject>
#include <QWidget>

#include "wall.h"
#include "robot.h"

#define POS 70
#define SCALER (9.0/10.0)

extern QSize windowSize;

class Menu : public QWidget, public QGraphicsRectItem {

    Q_OBJECT

    private:
        QPushButton *saveButton;
        QPushButton *loadButton;
        Wall *sampleWall;
        Robot *sampleRobot;

    public:
        Menu(QGraphicsRectItem *parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    public slots:
        void toggle();
};

#endif // MENU
