#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QWidget>
#include <Qt>

#include <iostream>

class Wall : public QGraphicsRectItem {

    private:
        Qt::GlobalColor color;
        int size;

    public:
        Wall(QGraphicsRectItem *parent = nullptr);

        Qt::GlobalColor getColor();

        int getSize();

        void setColor(Qt::GlobalColor color);

        void setSize(int size);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};
