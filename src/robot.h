#include <QStyleOptionGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QWidget>
#include <Qt>

#define ROBOTSIZE 30

class Robot : public QGraphicsEllipseItem {

    private:
        Qt::GlobalColor color;
        int angle;
        bool moving;

    public:
        Robot(QGraphicsEllipseItem *parent = nullptr);

        Qt::GlobalColor getColor();

        int getAngle();

        bool getMoving();

        void setColor(Qt::GlobalColor color);

        void setAngle(int angle);

        void setMoving(bool moving);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};
