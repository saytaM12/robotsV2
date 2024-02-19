#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QWidget>
#include <Qt>

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

        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
