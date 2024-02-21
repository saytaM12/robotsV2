#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>
#include <QWidget>
#include <cmath>

class MenuIcon : public QObject, public QGraphicsRectItem {

    Q_OBJECT

    private:
        int pos;
        int size;

    public:
        MenuIcon(QGraphicsRectItem *parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};
