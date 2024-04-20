#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QPointer>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QtGlobal>

#include "darkenImage.h"
#include "myItem.h"

class Wall : public MyItem, public QGraphicsRectItem {

    Q_OBJECT

  private:
    const qreal WALL_RESIZE_SIZE = 10;
    const qreal MIN_WALL_SIZE = 2 * WALL_RESIZE_SIZE;
    /* This vatiable simply stores whether the wall has just been created by
     * dragging the sample wall. It is used to prevent the sample wall from being
     * resized.
     */
    bool justCreated;
    /* This variable stores the direction in which the wall would be resied on
     * drag and drop event. It is stored in binaty and multiple directions can
     * be combined. Directions are stored like this: 0b1000 (left), 0b0100
     * (bottom), 0b0010 (top), 0b0001 (right).
     */
    unsigned char binaryResizeSelector;

  protected:
    /* This method is used to check if the wall should be resied based on mouse
     * position.
     * @param QGraphicsSceneHoverEvent *event: The hover event.
     * @return: void
     */
    virtual void myResizeEvent(QGraphicsSceneHoverEvent *event);

  public:
    /* Constructor for the Wall object.
     * @param QRectF rect: The rectangle in which the wall is to be placed.
     * @param int size: The size of the wall. default is 100.
     * @param MyItem *parent: The parent of the wall.
     */
    Wall(int x, int y, int width, int height, QGraphicsItem *parent = nullptr);

    /* Constructor for the Wall object. Creates a new wall based off of another
     * @param Wall *wall: The wall that this wall is based off of.
     * @param MyItem *parent: The parent of the wall.
     */
    Wall(Wall *wall, QGraphicsItem *parent = nullptr)
        : Wall(wall->MyItem::x(), wall->MyItem::y(), wall->rect().width(), wall->rect().height(), parent) {
        justCreated = true;
    }

    /* This method returns whether the item is a wall. Always returns true.
     * @return: bool true
     */
    inline bool isWall() const { return true; }

    /* Method to return the bounding rectangle of the wall.
     * This method must be implemented, otherwise the program breaks. This is
     * due to inheritance sheananigans.
     * @return: QRectF
     */
    QRectF boundingRect() const { return rect(); }

    /* This method is called when the mouse enters the wall.
     * It calls the myResizeEvent method.
     * @param QGraphicsSceneHoverEvent *event: The hover event.
     * @return: void
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    /* This method is called when the mouse moves within the wall.
     * It calls the myResizeEvent method.
     * @param QGraphicsSceneHoverEvent *event: The hover event.
     * @return: void
     */
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

    /* This method acts as a drag and drop event for the wall
     * it checks if the wall should be resized and in that case it resizes instead
     * of the drag and drop.
     * @param QGraphicsSceneMouseEvent *event: The mouse event.
     * @return: void
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /* This method prevents the sample wall from being resized.
     * Unfortunately I haven't found a better way to do this.
     * @param QGraphicsSceneMouseEvent *event: The mouse event.
     * @return: void
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
        justCreated = false;
        MyItem::mouseReleaseEvent(event);
    }

    /* This method is used to paint the wall.
     * @param QPainter *painter: The painter object.
     * @param QStyleOptionGraphicsItem *option: The style options.
     * @param QWidget *widget: The widget on which the painting is done. Omit for
     * global painting.
     * @return: void
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};
