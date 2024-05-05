/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 *
 * This module contains the declaration of the Wall class.
 */
#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QPointer>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QtGlobal>

#include "myItem.h"

/**
 * @brief The Wall class represents a wall object in the scene.
 *
 * It inherits from MyItem and QGraphicsRectItem.
 */
class Wall : public MyItem, public QGraphicsRectItem {

    Q_OBJECT

  private:
    const qreal WALL_RESIZE_SIZE = 10;                /**< The size of wall resize area. */
    const qreal MIN_WALL_SIZE = 2 * WALL_RESIZE_SIZE; /**< The minimum size of the wall. */
    bool justCreated; /**< Flag to indicate if the wall has just been created (before first drop). */
    unsigned char binaryResizeSelector; /**< Variable to store the direction for wall resizing. */

  protected:
    /**
     * @brief This method is used to check if the wall should be resized based on mouse position.
     *
     * @param event The hover event.
     */
    virtual void myResizeEvent(QGraphicsSceneHoverEvent *event);

  public:
    /**
     * @brief Constructor for the Wall object.
     *
     * @param x The x-coordinate of the wall.
     * @param y The y-coordinate of the wall.
     * @param width The width of the wall.
     * @param height The height of the wall.
     * @param parent The parent of the wall.
     */
    Wall(int x, int y, int width, int height, QGraphicsItem *parent = nullptr);

    /**
     * @brief Constructor for the Wall object. Creates a new wall based off of another wall.
     *
     * @param wall The wall that this wall is based off of.
     * @param parent The parent of the wall.
     */
    Wall(Wall *wall, QGraphicsItem *parent = nullptr)
        : Wall(wall->MyItem::x(), wall->MyItem::y(), wall->rect().width(), wall->rect().height(), parent) {
        justCreated = true;
    }

    /**
     * @brief Method to return whether the item is a wall.
     * Since this object is a wall, it always returns true
     *
     * @return bool true.
     */
    inline bool isWall() const { return true; }

    /**
     * @brief Method to return the bounding rectangle of the wall.
     *
     * @return QRectF The bounding rectangle of the wall.
     */
    QRectF boundingRect() const { return rect(); }

    /**
     * @brief This method is called when the mouse enters the wall.
     *
     * It calls the myResizeEvent method.
     *
     * @param event The hover event.
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    /**
     * @brief This method is called when the mouse moves within the wall.
     *
     * It calls the myResizeEvent method.
     *
     * @param event The hover event.
     */
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

    /**
     * @brief This method acts as a drag and drop event for the wall.
     *
     * It checks if the wall should be resized and in that case it resizes instead
     * of the drag and drop.
     *
     * @param event The mouse event.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief This method prevents the sample wall from being resized.
     *
     * Unfortunately, I haven't found a better way to do this.
     *
     * @param event The mouse event.
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
        justCreated = false;
        MyItem::mouseReleaseEvent(event);
    }

    /**
     * @brief This method is used to paint the wall.
     *
     * @param painter The painter object.
     * @param option The style options.
     * @param widget The widget on which the painting is done. Omit for global painting.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};
