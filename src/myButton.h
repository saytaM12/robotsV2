#ifndef MYBUTTON
#define MYBUTTON

#include <QGraphicsRectItem>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class MyButton : public QObject, public QGraphicsRectItem {

  Q_OBJECT

private:
  bool clicked;
  QString string;

public:
  /*
   * This constructor is used to create a new MyButton object.
   * @param QString string: The string to be displayed on the button.
   * @param QGraphicsRectItem *parent: The parent of this object.
   */
  MyButton(QString string, QGraphicsRectItem *parent = nullptr);

  /*
   * This method is called when the mouse is pressed on the button.
   * It stores the fact that the button was clicked on the button. This is
   * needed so the user cannot just release the mouse on the button and tigger
   * the event.
   * @param QGraphicsSceneMouseEvent *event: The event that was triggered.
   * @return: void
   */
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /*
   * This method is called when the mouse, which was pressed on the button, is
   * released.
   * If the mouse was pressed on the button it emits a signal (pressed) to
   * trigger the evnt.
   * @param QGraphicsSceneMouseEvent *event: The event that was triggered.
   * @return: void
   */
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

  /*
   * This method is called to paint the button.
   * @param QPainter *painter: The painter to be used.
   * @param const QStyleOptionGraphicsItem *option: The option to be used.
   * @param QWidget *widget: The widget on which the painting will be done.
   * Omit for global painting.
   * @return: void
   */
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr);

signals:
  void pressed();
};

#endif // MYBUTTON
