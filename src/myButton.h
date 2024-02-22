#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>

class MyButton : public QObject, public QGraphicsRectItem {

    Q_OBJECT

    private:
        bool clicked;
        QString string;

    public:
        MyButton(QString string, QGraphicsRectItem *parent = nullptr);

        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    signals:
        void pressed();
};
