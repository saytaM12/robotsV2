#ifndef MENUICON
#define MENUICON

#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>
#include <QWidget>
#include <cmath>

class MenuIcon : public QObject, public QGraphicsRectItem {

    Q_OBJECT

    private:
        bool clicked;

    public:
        MenuIcon(QGraphicsRectItem *parent = nullptr);

        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    signals:
        void menuToggled();

};

#endif // MENUICON
