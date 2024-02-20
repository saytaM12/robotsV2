#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>
#include <QWidget>
#include <Qt>

class Wall : public QObject, public QGraphicsRectItem{

    Q_OBJECT

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

    public slots:
        void selectionChanged();
};
