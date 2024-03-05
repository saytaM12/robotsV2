#ifndef MENU
#define MENU

#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QObject>
#include <QPainter>
#include <QPointer>
#include <QStyleOptionGraphicsItem>

#include "myButton.h"
#include "sampleRobot.h"
#include "sampleWall.h"

#define POS 0
#define SCALER (9.0 / 10.0)

class Menu : public QWidget, public QGraphicsRectItem {

  Q_OBJECT

private:
  QPointer<MyButton> saveButton;
  QPointer<MyButton> loadButton;
  QPointer<SampleWall> sampleWall;
  QPointer<SampleRobot> sampleRobot;

public:
  /*
   * This constructor creates a new menu
   * @param QGraphicsRectItem *parent: The parent of this object.
   */
  Menu(QGraphicsRectItem *parent = nullptr);

  /*
   * This method returns the sample robot
   * @return: SampleRobot*
   */
  SampleRobot *getSampleRobot();

  /*
   * This method returns the sample wall
   * @return: SampleWall*
   */
  SampleWall *getSampleWall();

  /*
   * This method is called to paint the menu
   * @param QPainter *painter: The painter to be used
   * @param const QStyleOptionGraphicsItem *option: The option to be used
   * @param QWidget *widget: The widget that is painted on. Omit for global
   * painting.
   * @return: void
   */
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr);

public slots:
  /*
   * When this slot is called the menu is toggled
   * It toggles the visibility of the menu.
   * @return: void
   */
  void toggle();

signals:
  void savePressed();
  void loadPressed();
};

#endif // MENU
