#include "myItem.h"
#include "myScene.h"

MyItem::MyItem(qreal x, qreal y, QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent), selectedFromHover(false) {
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setCursor(Qt::OpenHandCursor);
    setAcceptHoverEvents(true);
    setX(x);
    setY(y);
    setZValue(-2);
}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::ClosedHandCursor);
        setZValue(0);
    }

    QGraphicsItem::mousePressEvent(event);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::OpenHandCursor);
        setZValue(-2);
    }

    QGraphicsItem::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton) {
        emit mouseReleased(this);
    }
}

QVariant MyItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        MyScene *myscene = static_cast<MyScene *>(scene());
        QRectF sceneRect = myscene->sceneRect();

        QGraphicsRectItem *testItem =
            new QGraphicsRectItem(newPos.x(), newPos.y(), boundingRect().width(), boundingRect().height());
        myscene->QGraphicsScene::addItem(testItem);

        QList<QGraphicsItem *> colItems = testItem->collidingItems();
        colItems.removeAll(this);

        bool collision = false;
        for (QGraphicsItem *item : colItems) {
            if (myscene->items().contains(static_cast<MyItem *>(item))) {
                collision = true;
            }
        }

        myscene->removeItem(testItem);
        delete testItem;

        if (collision) {
            newPos = pos();
        }

        if (!sceneRect.contains(QRectF(newPos, QSizeF(boundingRect().width(), boundingRect().height())))) {
            newPos.setX(qBound((qreal)0, newPos.x(), sceneRect.right() - boundingRect().width()));

            newPos.setY(qBound((qreal)0, newPos.y(), sceneRect.bottom() - boundingRect().height()));
        }

        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}
