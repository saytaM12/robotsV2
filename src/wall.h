#ifndef WALL
#define WALL

#include <QGraphicsRectItem>
#include <QPainter>
#include <QPointer>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include "myItem.h"
#include "wallResize.h"

class WallResize;

class Wall : public MyItem, public QGraphicsRectItem {

  Q_OBJECT

private:
  int size;

public:
  /*
   * Constructor for the Wall object.
   * @param QRectF rect: The rectangle in which the wall is to be placed.
   * @param int size: The size of the wall. default is 100.
   * @param MyItem *parent: The parent of the wall.
   */
  Wall(int x, int y, int size = 100, MyItem *parent = nullptr);

  /*
   * Constructor for the Wall object. Creates a new Wall based on an existing
   * Wall.
   * @param Wall *wall: The wall to be copied.
   * @param MyItem *parent: The parent of the wall.
   */
  Wall(Wall *wall, MyItem *parent = nullptr);

  /*
   * This method returns whether the item is a wall. Always returns true.
   * @return: bool true
   */
  bool isWall() const;

  /*
   * This method returns the size of the wall.
   * @return: int
   */
  int getSize();

  /*
   * This method sets the size of the wall.
   * @param int size: The new size of the wall.
   * @return: void
   */
  void setSize(int size);

  /*
   * Method to return the bounding rectangle of the wall.
   * This method must be implemented, otherwise the program breaks. This is
   * due to inheritance sheananigans.
   * @return: QRectF
   */
  QRectF boundingRect() const;

  /*
   * This method is used to paint the wall.
   * @param QPainter *painter: The painter object.
   * @param QStyleOptionGraphicsItem *option: The style options.
   * @param QWidget *widget: The widget on which the painting is done. Omit for
   * global painting.
   * @return: void
   */
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr);
};

#endif // WALL
