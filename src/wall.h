#ifndef WALL
#define WALL

#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>
#include <QWidget>

#define CL 0.2      // Corner Length
#define CW 0.03     // Corner Width

class Wall : public QObject, public QGraphicsRectItem {

    Q_OBJECT

    private:
        int size;
        bool selectedFromHover;

    public:
        Wall(QGraphicsRectItem *parent = nullptr);

        Wall(QRectF rect, int size, QGraphicsRectItem *parent = nullptr);

        int getSize();

        void setSize(int size);

        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

        //void mousePressEvent(QGraphicsSceneMouseEvent *event);

        //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    public slots:
        void selectionChanged();
};

#endif // WALL
