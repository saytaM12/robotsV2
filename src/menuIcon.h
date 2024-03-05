#ifndef MENUICON
#define MENUICON

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <cmath>

class MenuIcon : public QObject, public QGraphicsRectItem {

  Q_OBJECT

private:
  bool clicked;

public:
  /*
   * This construcetor is used to create a new MenuIcon object.
   * @param QGraphicsRectItem *parent: The parent of this object.
   */
  MenuIcon(QGraphicsRectItem *parent = nullptr);

  /*
   * This method is called when the mouse is pressed on the menu icon.
   * It stores the fact that the mouse was pressed on the icon. This is needed
   * so the user cannot just release the  the mouse on the icon and trigger the
   * event.
   * @param QGraphicsSceneMouseEvent *event: The event that was triggered.
   * @return: void
   */
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /*
   * This methos is called when the mouse, which was pressed on the menu icon,
   * is released.
   * If the mouse was pressed on the icon and then released on the icon, a
   * signal (menuToggled) will be emitted to toggle the menu.
   * @param QGraphicsSceneMouseEvent *event: The event that was triggered.
   * @return: void
   */
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

  /*
   * This method is called to paint the menu icon.
   * @param QPainter *painter: The painter to be used.
   * @param const QStyleOptionGraphicsItem *option: The option to be used.
   * @param QWidget *widget: The widget on which the painting will be done.
   * Omit for global painting.
   * @return: void
   */
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr);

signals:
  void menuToggled();
};

#endif // MENUICON
