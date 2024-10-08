/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 *
 * This module contains the implementation of the MyItem class.
 */
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
        emit mouseReleased();
    }
}

// Enable checking for rectangles as well as ellipses
template <class T> void collisionCheck(MyScene *scene, MyItem *item, T *testItem, QPointF *pos) {
    scene->QGraphicsScene::addItem(testItem);
    QList<QGraphicsItem *> colItems = testItem->collidingItems();
    scene->removeItem(testItem);

    colItems.removeAll(item);

    bool collision = false;
    for (QGraphicsItem *colItem : colItems) {
        if (scene->items().contains(static_cast<MyItem *>(colItem))) {
            collision = true;
        }
    }

    if (collision) {
        *pos = item->pos();
    }
}

QVariant MyItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        MyScene *myscene = static_cast<MyScene *>(scene());
        QRectF sceneRect = myscene->sceneRect();

        // Out of bounds check
        newPos.setX(qBound((qreal)0, newPos.x(), sceneRect.right() - boundingRect().width()));
        newPos.setY(qBound((qreal)0, newPos.y(), sceneRect.bottom() - boundingRect().height()));

        // Collision check
        if (isWall()) {
            QGraphicsRectItem *testItem =
                new QGraphicsRectItem(newPos.x(), newPos.y(), boundingRect().width(), boundingRect().height());
            collisionCheck(myscene, this, testItem, &newPos);
            delete testItem;
        } else {
            QGraphicsEllipseItem *testItem = new QGraphicsEllipseItem(
                newPos.x(), newPos.y(), boundingRect().width(), boundingRect().height());
            collisionCheck(myscene, this, testItem, &newPos);
            delete testItem;
        }

        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}
