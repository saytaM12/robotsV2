#pragma once

#include <QAbstractGraphicsShapeItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>

class MyItem : public QObject, public QAbstractGraphicsShapeItem {

  Q_OBJECT

private:
  bool selectedFromHover;

public:
  /* This constructor is used to create a new item
   * @param qreal x: The x position of the item
   * @param qreal y: The y position of the item
   * @param QAbstractGraphicsShapeItem *parent: The parent of this object.
   */
  MyItem(qreal x, qreal y, QGraphicsItem *parent = nullptr);

  /* This virtual method must be implemented by the subclasses to return if the
   * item is a wall
   */
  virtual bool isWall() const = 0;

  /* This method is called when the mouse enters the item
   * If the item wasn't selected, it will become selected and the fact that it
   * was selected from mouse hover will be stored. This is so that the item
   * cannot be unselected be hoverLeaveEvent if it was selevted by group
   * selection.
   * @param QGraphicsSceneHoverEvent *event: The event that triggered this
   * @return: void
   */
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  /* This method is called when the mouse leaves the item
   * If the item was selected from hover, it will be unselected.
   * @param QGraphicsSceneHoverEvent *event: The event that triggered this
   * @return: void
   */
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

  /* This method is called when the user presses the mouse button
   * Changes the cursor, and puts the item on top of all of the other items (for
   * painting purposes).
   * @param QGraphicsSceneMouseEvent *event: The event that triggered this
   * @return: void
   */
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /* This method is called when the user releases the mouse button
   * Changes the cursor and puts the item back the bottom layer (for painting
   * purposes). This method also emits the mouseReleased signal.
   * @parem QGraphicsSceneMouseEvent *event: The event that triggered this
   * @return: void
   */
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

  /* This method is called when the item is changes in any way
   * Here it is used to check if the item is being moved out of the scene.
   * If so, it will be stopped from going further.
   * @param QGraphicsItem::GraphicsItemChange change: The type of change
   * @param const QVariant &value: The value of the change
   * @return: QVariant
   */
  QVariant itemChange(QGraphicsItem::GraphicsItemChange change,
                      const QVariant &value);

signals:
  void mouseReleased(MyItem *item);
};
