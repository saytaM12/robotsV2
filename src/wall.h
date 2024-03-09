#pragma once

#include <QGraphicsRectItem>
#include <QPainter>
#include <QPointer>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include "myItem.h"

#define WALL_RESIZE_SIZE 10

class Wall;

enum Position { TOP, BOTTOM, LEFT, RIGHT };

class WallResize : public QObject, public QGraphicsRectItem {

  Q_OBJECT

public:
  WallResize(Wall *wall, Position pos);
};

class Wall : public MyItem, public QGraphicsRectItem {

  Q_OBJECT

private:
  QPointer<WallResize> topResize;
  QPointer<WallResize> bottomResize;
  QPointer<WallResize> leftResize;
  QPointer<WallResize> rightResize;

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
      : Wall(wall->rect().x(), wall->rect().y(), wall->rect().width(),
             wall->rect().height(), parent) {}

  /* This method returns whether the item is a wall. Always returns true.
   * @return: bool true
   */
  inline bool isWall() const { return true; }

  /* Method to return the bounding rectangle of the wall.
   * This method must be implemented, otherwise the program breaks. This is
   * due to inheritance sheananigans.
   * @return: QRectF
   */
  QRectF boundingRect() const { return this->rect(); }

  /* This method is used to paint the wall.
   * @param QPainter *painter: The painter object.
   * @param QStyleOptionGraphicsItem *option: The style options.
   * @param QWidget *widget: The widget on which the painting is done. Omit for
   * global painting.
   * @return: void
   */
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr);
};
