#ifndef ROBOT
#define ROBOT

#include <QStyleOptionGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QObject>
#include <QWidget>

#define ROBOTSIZE 60

class Robot : public QObject, public QGraphicsEllipseItem {

    Q_OBJECT

    private:
        int angle;
        bool player;
        bool moving;
        bool selectedFromHover;

    public:
        Robot(QGraphicsEllipseItem *parent = nullptr);

        Robot(QRectF rect, int angle, bool player, QGraphicsEllipseItem *parent = nullptr);

        int getAngle();

        bool isPlayer();

        bool getMoving();

        void setAngle(int angle);

        void setPlayer(bool player);
        
        void setMoving(bool moving);

        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

        //void mousePressEvent(QGraphicsSceneMouseEvent *event);

        //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    public slots:
        void selectionChanged();
};

//class AngleSlider : public QObject, public QGraphicskk

#endif // ROBOT
