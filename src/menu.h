#ifndef MENU
#define MENU

#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QPainter>
#include <QObject>

#include "myButton.h"
#include "wall.h"
#include "robot.h"

#define POS 0
#define SCALER (9.0/10.0)

extern QSize windowSize;

class Menu : public QWidget, public QGraphicsRectItem {

    Q_OBJECT

    private:
        MyButton *saveButton;
        MyButton *loadButton;
        Wall *sampleWall;
        Robot *sampleRobot;

    public:
        Menu(QGraphicsRectItem *parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    public slots:
        void toggle();

    signals:
        void savePressed();
        void loadPressed();
};

#endif // MENU
