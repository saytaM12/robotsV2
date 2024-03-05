#ifndef SAMPLEWALL
#define SAMPLEWALL

#include "wall.h"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMouseEvent>

class SampleWall : public Wall {

public:
  /*
   * Constructor for SampleWall. creates a new SampleWall.
   * @param QrectF rect: Rectangle in which the wall is placed.
   * @param int size: The size of the wall.
   * @param Wall *parent: The parent of this object.
   */
  SampleWall(int x, int y, int size, Wall *parent = nullptr);

  /*
   * Constuctor to create a new SampleWall from an existing Wall.
   * @param Wall *wall: The wall to be copied.
   * @param Wall *parent: The parent of this object.
   */
  SampleWall(SampleWall *wall, Wall *parent = nullptr);
};

#endif // SAMPLEWALL
